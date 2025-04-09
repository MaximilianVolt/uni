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

  public static function insertWbr(string $str): string
  {
    return str_replace(
      ['.', '/', '_'],
      ['<wbr>.', '<wbr>/', '<wbr>_'],
      $str
    );
  }
}
