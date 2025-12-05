<?php

declare(strict_types=1);

namespace W00\T06;



class App
{
  public static \W00\T06\DB $db;



  public function __construct(\W00\T06\DBConfig $dbconfig)
  {
    static::$db = new \W00\T06\DB($dbconfig);
  }



  public function db(): \W00\T06\DB
  {
    return static::$db;
  } 
}
