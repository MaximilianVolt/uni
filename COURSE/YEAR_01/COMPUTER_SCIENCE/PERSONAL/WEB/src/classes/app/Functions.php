<?php

declare(strict_types=1);



namespace App;



/**
 * Wraps a string inside a <pre> HTML tag.
 * @param string $str The string to enclose.
 * @return string
 */



class Functions
{
  public static function pre(string $str): string
  {
    return "<pre>$str</pre>";
  }

  public static function autowbr(string $str, bool $add_dash = false): string
  {
    return implode(
      ($add_dash ? '&shy;' : '') . '<wbr>',
      preg_split('/(?=[A-Z]|\_|\.|\/|\@)/', $str)
    );
  }
}
