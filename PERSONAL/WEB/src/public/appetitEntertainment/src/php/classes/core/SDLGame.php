<?php

  declare(strict_types=1);

  namespace SDL\Classes\Core;



  /*
   * Responsible for game functions.
   */

  class SDLGame
  {
    private static array $teams;



    /*
     */

    public static function create(array $teams) {
      static::$teams = $teams;
    }



    /*
     */

    public static function getTeams(): array {
      return static::$teams;
    }



    /*
     */

    public static function getCharacter(int $character_id): ?\SDL\Classes\Game\SDLCharacter {
      foreach (static::$teams as $t) {
        if ($c = $t->get($character_id)) {
          return $c;
        }
      }

      return null;
    }
  }
