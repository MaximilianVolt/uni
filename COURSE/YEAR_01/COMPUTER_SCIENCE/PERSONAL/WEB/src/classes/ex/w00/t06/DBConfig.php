<?php

namespace W00\T06;

enum DBConfigKey: string
{
  case DRIVER = 'driver';
  case HOST = 'host';
  case DBNAME = 'dbname';
  case USER = 'user';
  case PW = 'pw';
}



class DBConfig
{
  protected array $config;

  public function __construct(array $env) {
    $this->config = [
      'db' => [
        DBConfigKey::DRIVER->value => $env['DB_DRIVER'] ?? 'mysql',
        DBConfigKey::HOST->value   => $env['DB_HOST'],
        DBConfigKey::DBNAME->value => $env['DB_NAME'],
        DBConfigKey::USER->value   => $env['DB_USER'],
        DBConfigKey::PW->value     => $env['DB_PW']
      ],
    ];
  }



  public function __get(string $name): array|null
  {
    return $this->config[$name] ?? null;
  }



  public function config(): array
  {
    return $this->config;
  }
}