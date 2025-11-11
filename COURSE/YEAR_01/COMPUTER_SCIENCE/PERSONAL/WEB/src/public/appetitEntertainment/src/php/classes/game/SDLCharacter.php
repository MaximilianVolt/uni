<?php

  declare(strict_types=1);

  namespace SDL\Classes\Game;



  /*
   * Responsible for character info.
   */

  class SDLCharacter
  {
    private static int $global_id = 0;
    private int $id;
    private \SDL\Classes\Game\SDLTeam $team;
    private \SDL\Classes\Game\SDLCharacterData $data;



    private function __construct(
      private string $name,
      private \SDL\Enums\SDLCharacterGender $gender,
      private ?\SDL\Classes\Core\SDLImage $img
    ) {
      $this->id = static::$global_id++;
      $this->data = \SDL\Classes\Game\SDLCharacterData::init([]);
    }



    /*
     */

    public static function create(\SDL\Classes\Core\SDLImage $img): static {
      $data = $img->getFilenameCharacterInfo();
      return new static($data[0], \SDL\Enums\SDLCharacterGender::tryFrom($data[1]), $img);
    }



    /*
     */

    public function getId(): int {
      return $this->id;
    }



    /*
     */

    public function getName(): string {
      return $this->name;
    }



    /*
     */

    public function getGender(): \SDL\Enums\SDLCharacterGender {
      return $this->gender;
    }



    public function getPronouns(): array {
      return \SDL\Enums\SDLCharacterGender::getPronouns($this->getGender());
    }



    /*
     */

    public function getImg(): \SDL\Classes\Core\SDLImage {
      return $this->img;
    }



    /*
     */

    public function getData(): \SDL\Classes\Game\SDLCharacterData {
      return $this->data;
    }



    /*
     */

    public function getTeam(): \SDL\Classes\Game\SDLTeam {
      return $this->team;
    }



    /*
     */

    public function setTeam(SDLTeam $team): void {
      $this->team = $team;
    }



    /*
     */

    public function isAlive(): bool {
      return !$this->data->getFlag(FLAG_CHARACTER_IS_DEAD);
    }



    /*
     */

    public function sameTeam(\SDL\Classes\Game\SDLCharacter $c): bool {
      return $this->team === $c->getTeam();
    }



    /*
     */

    public function applyEffects(array $effects): void {
      $this->data->apply($effects);
    }
  }