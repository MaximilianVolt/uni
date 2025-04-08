<?php

declare(strict_types=1);

namespace Oop;

class C2 extends C1 implements I1
{
  public static string $a;



  public static function test(): void
  {
    // echo static::$a;
  }

  public function __construct(int $a = 0)
  {
    static::$a = (string) $a;
    $this->test();
  }
}
