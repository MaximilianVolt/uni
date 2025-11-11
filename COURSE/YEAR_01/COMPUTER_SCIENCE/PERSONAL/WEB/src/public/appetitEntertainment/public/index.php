<?php
  /*
   * App entry point
   * > Scannerizza le cartelle per leggere ottenere i dati di personaggi e pool di eventi
   * > Mostra il menù del setup
   * > All'avviare della partita genera tutti gli eventi di tutta la partita dentro un solo file json
   */

  declare(strict_types=1);

  namespace SDL;

  use SDL\SDL;

  const TITLE = "SVAGHI DEL LANGUORINO";
  include_once "../src/php/SDL.php";
?>
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link href="./css/style.css" rel="stylesheet" type="text/css">
    <title><?= TITLE ?></title>
  </head>
  <body>
    <h1><?= TITLE ?></h1>
    <pre>
    <?php

      $team = SDL::team([
        /* 0 */ SDL::character("M_E.S.O..png"),
        /* 2 */ SDL::character("M_Ezidriel.png"),
        /* 1 */ SDL::character("F_Drenneth.png"),
        /* 3 */ SDL::character("NB_Ventilatore_della_Honeywell.png"),
        /* 4 */ SDL::character("F_Vilette.png"),
        /* 5 */ SDL::character("M_Bartok Modulus.png"),
        /* 6 */ SDL::character("M_Negabyte.png"),
      ]);

      Classes\Core\SDLGame::create([$team]);
      $chars = array_slice($team->getCharacters(), 0, 3);

      $effects = [
        SDL::effect("morte"),
        SDL::effect("veleno"),
        SDL::effect("ferita"),
        SDL::effect("paura"),
        SDL::effect("cecità"),
        SDL::effect("palestrato"),
        SDL::effect("shock"),
      ];

      $str = "{(0)>0>(1,2)} unknowingly eats a steroid-charged biscuit-cat and angrily punches {(1)>1}. [1|0] falls onto {(2)>2}, killing [2|1].";
      // $str = "{(4)>1>(1,2,4)} prepares a bowl of spaghetti for {(1,2,4)>[2,4,6]}, but corrects it with Magnesium pieces and flint and steel. Magnesium sparks end up in {1}'s eyes, blinding [1|1].";
      // $str = "{(0,6)>4} tries to attack {(5)>2>(0,6)}, but did NOT expect [2|1] to become instantly buffed.";
      // $str = "While {[5,6]} walk together in a building, {(2)>3>(0)} falls from a hole in the ceiling on {(0)>5}, scaring off {(2,6)>6}, who gets caught in some rubble.";
      // $str = "{(1)>[..]} go have lunch to Gubbio's restaurant. {(0)>[..1]} shat themselves to oblivion while {[2..]} suffer from severe food poisoning.";
      // $str = "{(1,3,4,6)>1>(0)} eats a suspicious gum and becomes DeviantArt content, but while rolling [1|0] crashes {(0)>0} to death.";
      // $str = "{>0} realized [0|0] has always been british and becomes unbased.";

      $event = Classes\Game\SDLEvent::create($str, $effects);


      function printfx(Classes\Game\SDLEvent $e, array $characters, array $effects) {
        echo "<br>{$e->getTemplate()}<br>";
        $a = Classes\Core\SDLEventParser::resolve($e, $characters);

        foreach ($a['effects'] as $char_idx => $e) {
          $char = $characters[$char_idx];
          // print($char_id);
          $char->applyEffects($e);
        }

        print_r($a);
      }

      function dirname_ext(string $path, int $levels = 1)
      {
        if ($levels >= 1)
          return dirname($path, $levels);

        return implode(DIRECTORY_SEPARATOR, array_slice(explode(DIRECTORY_SEPARATOR, rtrim($path, DIRECTORY_SEPARATOR)), $levels));
      }

      printfx($event, $chars, $effects);

      // foreach ($team->getCharacters() as $c) {
      //   print_r($c->getData()->getFrequencies());
      // }
    ?>
    <p>El slider</p>
    <input type="range" min="0" max="10" step="1">
    </pre>
  </body>
</html>