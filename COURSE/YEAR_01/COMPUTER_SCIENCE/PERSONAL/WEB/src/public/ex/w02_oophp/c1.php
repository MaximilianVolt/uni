<?php

declare(strict_types=1);

namespace W02;

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
