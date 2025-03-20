<?php

  class C2 extends C1 implements I1
  {
    public function test(int $a): void
    {
      echo $a;
    }
  }