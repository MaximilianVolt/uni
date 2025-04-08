<?php

  declare(strict_types=1);

  namespace Src\Classes;



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


  class TestStaticClass
  {
    private static string $property = "";



    /**
     * Changes the $property property to the user-given value.
     * @param string $property The new property to set.
     * @return string
     */

    public static function override(string $property): string
    {
      return static::$property = $property;
    }



    /**
     * Gets the property value of the class.
     * @return string
     */

    public static function string(): string
    {
      return "<| " . static::$property . " |>";
    }
  }
