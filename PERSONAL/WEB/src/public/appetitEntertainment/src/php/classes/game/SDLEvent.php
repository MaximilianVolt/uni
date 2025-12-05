<?php

  declare(strict_types=1);

  namespace SDL\Classes\Game;



  const FLAG_EVENT_ACTIVE = 0;
  const FLAG_EVENT_FATAL = 1;

  /*
   * Manages data for a single event (characters, effects applied, deaths, etc.)
   */

  class SDLEvent
  {
    private static int $global_id = 0;
    private int $id;
    private \SDL\Classes\Game\SDLEventPool $pool;

    use \SDL\Classes\Core\SDLBitField;



    private function __construct(
      private string $template,
      private array $effect_ids,
      private int $min_charcount,
      private int $max_charcount,
      private int $chance,
      private int $flags
    ) {
      $this->id = static::$global_id++;
    }



    /*
     */

    public static function create(string $template, ?array $effect_ids = [], int $min_charcount = 1, int $max_charcount = 1, int $chance = 1, int $flags = 0): static
    {
      if ($max_charcount < $min_charcount) {
        throw new \InvalidArgumentException("INVALID CHARACTER RANGE SPECIFIED");
      }

      if ($chance <= 0) {
        throw new \InvalidArgumentException("INVALID CHANCE SPECIFIED");
      }

      return new static($template, $effect_ids, $min_charcount, $max_charcount, $chance, $flags);
    }



    /*
     */

    public function getTemplate(): string {
      return $this->template;
    }



    /*
     */

    public function getEffectIds(): array {
      return array_map(fn($e) => $e->getId(), $this->effect_ids);
    }



    /*
     */
    public function getCharRange(): array {
      return [$this->min_charcount, $this->max_charcount];
    }



    /*
     */

    public function getChance(): int {
      return $this->chance;
    }



    /*
     */

    public function getPool(): \SDL\Classes\Game\SDLEventPool {
      return $this->pool;
    }



    /*
     */

    public function setPool(\SDL\Classes\Game\SDLEventPool $pool): void {
      $this->pool = $pool;
    }



    /*
     */

    public function appliesToCharacters(array $characters): bool
    {
      $alive = array_filter($characters, fn($c) => $c->getData()/*->isAlive()*/);
      $alive_count = count($alive);

      return $alive_count >= $this->min_charcount && $alive <= $this->max_charcount;
    }



    /*
     */

    public function isActive(): bool {
      return $this->getFlag(FLAG_EVENT_ACTIVE);
    }



    /*
     */

    public function isFatal(): bool {
      return $this->getFlag(FLAG_EVENT_FATAL);
    }



    /*
     */
    
    public function isSurvival(): bool {
      return (bool) $this->getMaskRegionBut(FLAG_EVENT_FATAL + 1);
    }
  }
