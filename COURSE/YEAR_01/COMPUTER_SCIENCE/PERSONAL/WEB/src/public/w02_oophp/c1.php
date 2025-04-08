<?php

declare(strict_types=1);

namespace Oop;

class C1
{
  public static function printClass(): string
  {
    return static::class;
  }

  public function __construct()
  {

  }
}
