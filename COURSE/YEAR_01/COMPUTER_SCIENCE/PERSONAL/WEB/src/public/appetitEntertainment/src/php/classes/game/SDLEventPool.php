<?php

  declare(strict_types=1);

  namespace SDL\Classes\Game;



  /*
   * Manages a pool of events (toggling, etc.).
   */

  class SDLEventPool
  {
    private static int $global_id = 0;
    private int $id;



    private function __construct(
      private array $events
    ) {
      $this->id = static::$global_id++;

      foreach ($events as $e) {
        $e->setPool($this);
      }
    }



    /*
     */

    public static function create(array $events): static {
      if (empty($events))
        throw new \InvalidArgumentException("EVENT POOLS MUST CONTAIN 1 OR MORE EVENTS");

      return new static($events);
    }



    /*
     */

    public function getId(): int {
      return $this->id;
    }



    /*
     */

    public function get(int $id): ?\SDL\Classes\Game\SDLEvent {
      return array_find($this->events, fn($e) => $e->getId() === $id);
    }



    /*
     */

    public function getAll(): array {
      return $this->events;
    }



    /*
     */

    public function toggle($id): bool {
      $e = $this->get($id);
      return $e->setFlag(FLAG_EVENT_ACTIVE, !$e->isActive());
    }



    /*
     */

    public static function getEventsWeightSum(array $events, callable $condition = fn($e) => $e->isActive()): int {
      return array_reduce($events, fn($sum, $e) => $sum + $e->getChance() * $condition($e), 0);
    }



    /*
     */

    public function pick(callable $filter = fn($e) => $e !== null): int
    {
      $events = array_filter($this->events, $filter);
      $n = random_int(0, static::getEventsWeightSum($events));

      foreach ($events as $i => $e) {
        if ($n < $e->getChance()) {
          return $i;
        }

        $n -= $e->getChance();
      }

      return 0;
    }
  }
