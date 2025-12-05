<?php

  declare(strict_types=1);

  namespace SDL\Classes\Game;



  /*
   * Effects applied to characters in-game.
   */

  class SDLEffect
  {
    private static int $global_id = 0;
    private int $id;



    private function __construct(
      private string $name,
      private ?\SDL\Classes\Core\SDLImage $img = null,
    ) {
      $this->id = static::$global_id++;
    }



    public static function create(string $name, ?\SDL\Classes\Core\SDLImage $img = null): static {
      return new static($name ?? $img?->getFilenameStatusName(), $img);
    }



    public function getId(): int {
      return $this->id;
    }



    public function getName(): string {
      return $this->name;
    }



    public function getImg(): \SDL\Classes\Core\SDLImage {
      return $this->img;
    }
  }
