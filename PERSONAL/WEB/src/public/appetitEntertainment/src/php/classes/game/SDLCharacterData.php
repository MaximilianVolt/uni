<?php

  declare(strict_types=1);

  namespace SDL\Classes\Game;



  const FLAG_CHARACTER_IS_DEAD = 0;

  /*
   * Responsible for character in-game data.
   */

  class SDLCharacterData
  {
    private array $status_frequencies;
    private int $status;

    use \SDL\Classes\Core\SDLBitField;



    private function __construct(array $states)
    {
      $this->status = 0;
      $this->status_frequencies = ['inflicted' => [], 'received' => []];

      foreach ($states as $s) {
        $this->status_frequencies['inflicted'][$s->getId()] = 0;
        $this->status_frequencies['received'][$s->getId()] = 0;
      }
    }



    public static function init(array $states): static {
      return new static($states);
    }



    public function getFrequencies(): array {
      return $this->status_frequencies;
    }



    public function apply(array $effects): void
    {
      foreach ($effects['inflicted'] as $e) {
        $this->status_frequencies['inflicted'][$e] ??= 0;
        ++$this->status_frequencies['inflicted'][$e];
      }

      foreach ($effects['received'] as $e) {
        $this->status_frequencies['received'][$e] ??= 0;
        ++$this->status_frequencies['received'][$e];
      }
    }
  }
