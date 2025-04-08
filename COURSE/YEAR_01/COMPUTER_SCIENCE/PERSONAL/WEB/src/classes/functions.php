<?php

declare(strict_types=1);



/**
 * Wraps a string inside a <pre> HTML tag.
 * @param string $str The string to enclose.
 * @return string
 */

function pre(string $str): string
{
  return "<pre>$str</pre>";
}
