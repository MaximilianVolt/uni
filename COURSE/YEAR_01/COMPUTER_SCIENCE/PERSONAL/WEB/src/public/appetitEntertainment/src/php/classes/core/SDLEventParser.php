<?php

  declare(strict_types=1);

  namespace SDL\Classes\Core;



  /*
   * Responsible for interpreting events' strings.
   */

  class SDLEventParser
  {
    final public static $INFLICTER_TOKEN = ">";
    final public static $RECEIVER_TOKEN = ">";



    /*
     */

    public static function resolve(\SDL\Classes\Game\SDLEvent $event, array $characters): array
    {
      $text = "";
      $ledger = [];

      $tokens = static::tokenize($event->getTemplate(), count($characters), count($event->getEffectIds()));
      $chars = fn($c, $i) => array_intersect_key($c, array_flip($i));
      $resolve_effect_ids = fn($e) => $event->getEffectIds()[$e];
      $boundaries = static::detectSentenceBoundaries($tokens);
      $capitalize_next = false;
      // $resolve_char_ids = fn($c) => $characters[$c];

      foreach ($tokens as $i => $t)
      {
        $text .= match ($t['type']) {
          'text' => $capitalize_next ? ucfirst($t['value']) : $t['value'],
          'name' => SDLEventParser::charNameList($chars($characters, $t['chars'])),
          'pronoun' => SDLEventParser::charPronounList($chars($characters, $t['chars']), \SDL\Enums\SDLCharacterPronoun::tryFrom((int) $t['pronoun']), $capitalize_next),
          default => "",
        };

        $capitalize_next = in_array($i, $boundaries);

        if ($t['type'] !== 'effect') {
          continue;
        }

        foreach ($t['chars'] as $cid) {
          $ledger[$cid] ??= ['inflicted' => [], 'received' => []];
          $ledger[$cid]['inflicted'] = array_unique(array_merge($ledger[$cid]['inflicted'], array_map($resolve_effect_ids, $t['inflicted'])));
          $ledger[$cid]['received']  = array_unique(array_merge($ledger[$cid]['received'], array_map($resolve_effect_ids, $t['received'])));
        }
      }

      return [
        'text' => $text,
        'effects' => $ledger
      ];
    }



    /*
     */

    public static function tokenize(string $template, int $character_count, int $fx_count): array
    {
      $single = "(?:\d+)";
      $list = "(?:\d+(?:, *\d+)*)";
      $range = "(?:\d*\.\.\d*)";
      $effect_receiver = "(?:(?:\(((?:$single|$list|$range))\))?" . static::$INFLICTER_TOKEN . ")?";
      $effect_inflicter = "(?:" . static::$RECEIVER_TOKEN . "(?:\(((?:$single|$list|$range))\))?)?";

      $pattern = [
        "name"    => "\{($effect_receiver)(?:($single)|\[($list)\]|\[($range)\])($effect_inflicter)\}",
        "pronoun" => "\[($effect_receiver)(?:($single)|\[($list)\]|\[($range)\])\|($single)($effect_inflicter)\]",
      ];

      $regex = "/{$pattern['name']}|{$pattern['pronoun']}/x";

      preg_match_all($regex, $template, $matches, PREG_OFFSET_CAPTURE | PREG_SET_ORDER);

      $tokens = [];
      $parse_index = 0;

      foreach ($matches as $m)
      {
        $pos = $m[0][1];

        if ($pos > $parse_index)
          $tokens[] = [ 'type' => 'text', 'value' => substr($template, $parse_index, $pos - $parse_index) ];

        foreach (static::classify($m, $character_count, $fx_count) as $c)
          $tokens[] = $c;

        $parse_index = $pos + strlen($m[0][0]);
      }

      if ($parse_index < strlen($template))
        $tokens[] = [ 'type' => 'text', 'value' => substr($template, $parse_index) ];

      return $tokens;
    }



    /*
     */

    public static function classify(array $match, int $character_count, int $fx_count): array
    {
      $NAME_SINGLE = 3;
      $NAME_LIST = $NAME_SINGLE + 1;
      $NAME_RANGE = $NAME_LIST + 1;
      $PRONOUN_SINGLE = 10;
      $PRONOUN_LIST = $PRONOUN_SINGLE + 1;
      $PRONOUN_RANGE = $PRONOUN_LIST + 1;
      $PRONOUN_TYPE = $PRONOUN_RANGE + 1;

      $match_groups = [];

      // Saves the array of all the matched groups
      foreach ($match as $k => $g)
        if ($k && $g[0] !== "")
          $match_groups[] = $k;

      if ($match_groups === [])
        throw new \InvalidArgumentException("INVALID TOKEN PROVIDED.");

      $matched = fn($m, $i) => isset($m[$i]) && $m[$i][0] !== ""; 

      $regex_is_name    = $matched($match, $NAME_SINGLE) || $matched($match, $NAME_LIST) || $matched($match, $NAME_RANGE);
      $regex_is_pronoun = $matched($match, $PRONOUN_SINGLE) || $matched($match, $PRONOUN_LIST) || $matched($match, $PRONOUN_RANGE);
      $character_range  = array_merge(range($NAME_SINGLE, $NAME_RANGE), range($PRONOUN_SINGLE, $PRONOUN_TYPE));
      $character_ids    = [];
      $ret              = [];

      // Saves character ids only once
      foreach ($character_range as $i) {
        if ($matched($match, $i)) {
          $character_ids = static::resolveIds($match[$i][0], $character_count - 1);
          break;
        }
      }

      foreach ($match_groups as $g)
      {
        // Else it would duplicate a pronoun token
        if ($g === $PRONOUN_TYPE)
          continue;

        // Checks capture groups
        $match_is_fx_inf = match ($g) { 6, 14, 7, 15 => true, default => false };
        $match_is_fx_rec = match ($g) { 1, 8, 2, 9 => true, default => false };
        $match_is_effect = $match_is_fx_inf || $match_is_fx_rec;
        $match_is_character = in_array($g, $character_range);

        $count = $match_is_character ? $character_count : ($match_is_effect ? $fx_count : 0);

        // Adjusts capture groups to the content only, since groups are "(>(content)>)"
        if ($match_is_fx_inf)
          $g = $regex_is_name ? 7 : 15;
        elseif ($match_is_fx_rec)
          $g = $regex_is_name ? 2 : 9;

        $id_list = static::resolveIds($match[$g][0] ?? "", $count - 1);

        $ret[] = [
          'type' => $match_is_character ? ($regex_is_name ? 'name' : 'pronoun') : 'effect',
          'chars' => $character_ids,
          'pronoun' => $regex_is_pronoun ? $match[$PRONOUN_TYPE][0] : null,
          'inflicted' => $match_is_fx_inf ? $id_list : [],
          'received' => $match_is_fx_rec ? $id_list : [],
          'template' => $match[0][0],
        ];
      }

      return $ret;
    }



    /*
     */

    public static function resolveIds(string $expression, int $max_index): array
    {
      if ($expression === "") {
        return range(0, $max_index);
      }

      if (str_contains($expression, '..')) {
        [$start, $end] = explode('..', $expression);
        $end = $end !== '' ? (int) $end : $max_index;
        return range((int) $start, $end);
      }

      if (str_contains($expression, ',')) {
        return array_map('intval', explode(',', $expression));
      }

      return [(int) $expression];
    }



    /*
     */

    public static function detectSentenceBoundaries(array $tokens): array
    {
      $boundaries = [];

      foreach ($tokens as $i => $t)
      {
        if ($t['type'] !== 'text') {
          continue;
        }

        // Look for ., ?, !
        if (preg_match_all('/[.?!]\s+/', $t['value'], $matches, PREG_OFFSET_CAPTURE)) {
          $boundaries[] = $i;
        }
      }

      return $boundaries;
    }



    /*
     */

    public static function join(array $items, callable $callback, bool $capitalize): string
    {
      $item_count = count($items);

      if ($item_count === 0)
        return "";

      $resolved = array_values(array_map($callback, $items));

      if ($capitalize)
        $resolved[0] = ucfirst($resolved[0]);

      return match ($item_count) {
        1 => $resolved[0],
        2 => "{$resolved[0]} and {$resolved[1]}",
        default => implode(", ", array_slice($resolved, 0, -1)) . " and " . end($resolved)
      };
    }



    /*
     */

    public static function charNameList(array $characters): string {
      return static::join($characters, fn($c) => "<b>{$c->getName()}</b>", false);
    }



    /*
     */

    public static function charPronounList(array $characters, \SDL\Enums\SDLCharacterPronoun $pronoun_type, bool $capitalize = false): string {
      return static::join($characters, fn($c) => $c->getPronouns()[$pronoun_type->value], $capitalize);
    }
  }
