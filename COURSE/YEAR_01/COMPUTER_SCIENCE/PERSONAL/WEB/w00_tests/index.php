<?php
  $article_data = [
    "id"      => 1234,
    "genre"   => "News",
    "header"  => "New article",
    "content" => "Hi I'm an article.",
    "date"    => date("Y-m-d"),
    "image"   => "[img.png]"
  ];

  /*
    gino/
      index.php
      src/
        [img.png]
  */

?>
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
  </head>
  <body>
    <table>
      <?php foreach ($article_data as $key => $value): ?>
        <tr>
          <td><?= $key ?></td>
          <td><?= $value ?></td>
        </tr>
      <?php endforeach ?>
    </table>
    <!--
      1. Crea una pagina per l'articolo
      2. Crea una tabella che mostri le informazioni dell'articolo
    -->
    <?php include "footer.php" ?>
  </body>
</html>



<!-- footer.php -->
<footer>
  <h3>Title</h3>
  <a href=""></a>
  <a href=""></a>
</footer>