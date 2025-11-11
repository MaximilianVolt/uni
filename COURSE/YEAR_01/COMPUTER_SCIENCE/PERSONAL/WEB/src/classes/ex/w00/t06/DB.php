<?php

declare(strict_types=1);

namespace W00\T06;

class DB
{
  public static \PDO $connection;



  /**
   * Summary of __construct
   */

  public function __construct(DBConfig $config)
  {
    try {
      $defaults = [
        \PDO::ATTR_DEFAULT_FETCH_MODE => \PDO::FETCH_ASSOC,
        \PDO::ATTR_ERRMODE => \PDO::ERRMODE_EXCEPTION,
        \PDO::ATTR_EMULATE_PREPARES => false
      ];

      static::$connection = new \PDO(
        static::dsn($config->db),
        $config->db[\W00\T06\DBConfigKey::USER->value],
        $config->db[\W00\T06\DBConfigKey::PW->value],
        $config->options ?? $defaults
      );
    }
    catch (\PDOException $e) {
      throw new \PDOException($e->getMessage(), (int) $e->getCode());
    }
  }



  private static function dsn(array $config): string
  {
    return $config[\W00\T06\DBConfigKey::DRIVER->value] . ":host=" . $config[\W00\T06\DBConfigKey::HOST->value] . ";dbname=" . $config[\W00\T06\DBConfigKey::DBNAME->value] . ";";
  }



  /**
   * 
   * @return void
   */

  public static function pdo(): \PDO
  {
    return static::$connection;
  }



  public function __call($method, $args)
  {
    return call_user_func_array([$this->connection, $method], $args);
  }



  // Query methods...
}
