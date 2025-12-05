<?php

declare(strict_types=1);

namespace App;




class TestStaticClass
{
  private static string $property = "";



  /**
   * Changes the $property property to the user-given value.
   * @param string $property The new property to set.
   * @return static
   */

  public static function override(string $property): string
  {
    static::$property = $property;

    return static::class;
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