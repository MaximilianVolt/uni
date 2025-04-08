<?php

  $array = [];

  if ($_SERVER['REQUEST_METHOD'] == "POST")
  {
    $p_iva = $_POST["p-iva"];

    $db = "test";
    $host = "localhost";
    $username = "root";
    $password = "";

    $pdo = new PDO("mysql:host=$host;dbname=$db", $username, $password, [
      PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
      PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION,
    ]);

    // $conn = new SQLite3("db.db");
    // $ris = $conn->query("");
    // $ris->fetchArray()

    //$stmt = $pdo->prepare("SELECT ... WHERE piva = $p_iva");
    //$stmt->execute([":piva" => $p_iva]);

    $array = [
      [ "a" => 1, "b" => 2 ],
      [ "a" => 3, "b" => 4 ],
      [ "a" => 5, "b" => 6 ],
      [ "a" => 7, "b" => 8 ],
      [ "a" => 7, "b" => 8 ],
      [ "a" => 7, "b" => 8 ],
      [ "a" => 7, "b" => 8 ],
    ];

    echo $p_iva;
  }
?>

<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
  </head>
  <body>
    <form action="index.php" method="POST">
      <p>Inserisci una partita IVA</p>
      <input name="p-iva" type="text" pattern="^[0-9]{6}" placeholder="Inserisci una partita IVA"/>
      <input type="submit"/>
    </form>
    <table>
      <tr>
        <td>NOME COLONNA</td>
        <td>VALORE COLONNA</td>
      </tr>
      <?php foreach ($array as $riga): ?>
        <tr>
          <td><?= $riga["a"] ?></td>
          <td><?= $riga["b"] ?></td>
        </tr>
      <?php endforeach ?>

      <?php if (1 === 0): ?>
        <p>1 vale 1</p>
      <?php endif ; ?>
    </table>
  </body>
</html>