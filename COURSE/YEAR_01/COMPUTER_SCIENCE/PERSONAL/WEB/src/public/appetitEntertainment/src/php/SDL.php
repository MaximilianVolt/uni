<?php

  /*
   * IDEE HUNGER GAMES QUELLI BELLI 👌
   *
   * Salvare gli eventi geneici (tipo database) su un file JSON
   * Team a dimensione variabile anziché distretti a dimensione fissa
   * Opzione per permettere fuoco amico
   * Aggiungere stati per i personaggi come opzione (Survival Mode) come fame, sete, ecc.
   * Ogni giorno vengono scelti randomicamente eventi fintanto che ci sono personaggi disponibili
   * Form per la creazione personaggi, drag n' drop per immagine
   * File json con collegamento immagini, l'immagine ha il nome del PG
   * Eventi di morte con probabilità ponderata (Death Rate)
   * Slider per ogni status che determina probabilità evento e stato
   * Personaggio con cornice personalizzato e sfondo personalizzato (tipo banner)
   * Eventi arena sia di giorno che di notte
   * Icona stile orologio di Minecraft per giorno / notte
   * Recap riepilogo partita: Posizionamento (Giocatore e Team), Kill, Attacchi subiti e fatti, volte in cui ha subito uno stato (survival only), possibilità di riordinare i giocatori in base a cose
   * Possibilità di randomizzare i team
   * Temi (due file sass, uno personalizzabile con i colori e uno che li applica)
   * Una guida (TBA)
   * Possibilità di scegliere immagine di sfondo / colore
   * Gambling (possibilità di piazzare scommesse su un personaggio)
   * Pronomi salvati col personaggio
  */

  declare(strict_types=1);

  namespace SDL;



  define("SDL_ROOT", dirname(__DIR__, 2) . DIRECTORY_SEPARATOR);
  define("SDL_SRC" , SDL_ROOT . "src" . DIRECTORY_SEPARATOR);
  define("SDL_DATA", SDL_SRC . "data" . DIRECTORY_SEPARATOR);
  define("SDL_PHP", SDL_SRC . "php" . DIRECTORY_SEPARATOR);



  // PSR-4 stans are going to kill me
  spl_autoload_register(function($class) {
    $path = explode("\\", $class);
    array_shift($path);

    for ($i = count($path) - 2; $i >= 0; --$i) {
      $path[$i] = strtolower($path[$i]);
    }

    $path = implode("/", $path);

    require_once SDL_PHP . $path . ".php";
  });



  /*
   * Responsible of global initialization and utility functions.
   */

  class SDL
  {
    public static function character(string $img): \SDL\Classes\Game\SDLCharacter {
      return \SDL\Classes\Game\SDLCharacter::create(
        \SDL\Classes\Core\SDLImage::create($img)
      );
    }

    public static function team(array $characters): \SDL\Classes\Game\SDLTeam {
      return \SDL\Classes\Game\SDLTeam::create($characters);
    }

    public static function effect(string $name, ?\SDL\Classes\Core\SDLImage $img = null): \SDL\Classes\Game\SDLEffect {
      return \SDL\Classes\Game\SDLEffect::create($name, $img);
    }
  }
