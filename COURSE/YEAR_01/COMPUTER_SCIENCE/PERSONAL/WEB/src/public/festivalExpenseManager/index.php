<?php



  // !:
  // !: MUST FIX AUTOLOADER SINCE ROOT FOLDER HAS BEEN MOVED
  // !:
 


  declare(strict_types=1);

  const TITLE = "Festival expense manager";

  require_once __DIR__ . '/../../../../vendor/autoload.php';

  
  $app = new \W00\T06\App(
    new \W00\T06\DBConfig([
      'DB_DRIVER' => 'mysql',
      'DB_HOST'   => 'db',
      'DB_NAME'   => 'ProlocoGaicheFontana',
      'DB_USER'   => 'root',
      'DB_PW'     => 'root'
    ])
  );
?>
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="style.css" type="text/css">
    <title><?= TITLE ?></title>
  </head>
  <body>
<pre>
<?php
var_dump($app);

$stmt = $app->db()::$connection->prepare("SELECT * FROM UnitaProdotto");
$stmt->execute();

$arr = $stmt->fetchAll();

foreach ($arr as $item)
  var_dump($item);
?>
</pre>
  </body>
</html>