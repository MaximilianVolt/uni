<?php

  declare(strict_types=1);

  namespace App;



  class TestClass
  {
    public private(set) string $prop
    {
      get => "$this->prop - Gotten from property hook";

      set(string $prop) {
        $this->prop = strtoupper($prop);
      }
    }

    public function __construct(string $prop)
    {
      $this->prop = $prop;
    }
  }
