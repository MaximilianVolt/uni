<?php

  declare(strict_types=1);

  namespace SDL\Classes\Game;



  /*
   * Responsible for managing team members and team data (banner, etc.).
   */

  class SDLTeam
  {
    private static int $global_id = 0;
    private int $id = 0;



    private function __construct(
      private array $characters,
      private ?\SDL\Classes\Core\SDLImage $banner = null
    ) {
      $this->id = static::$global_id++;

      foreach ($characters as $c) {
        $c->setTeam($this);
      }
    }



    public static function create(array $characters, ?\SDL\Classes\Core\SDLImage $banner = null): static {
      return new static($characters, $banner);
    }



    public function get(int $id): ?SDLCharacter {
      return array_find($this->characters, fn($c) => $c->getId() === $id);
    }



    public function getCharacters(): array {
      return $this->characters;
    }



    public function any(callable $fn): bool {
      return array_any($this->characters, $fn);
    }



    public function all(callable $fn): bool {
      return array_all($this->characters, $fn);
    }
  }
