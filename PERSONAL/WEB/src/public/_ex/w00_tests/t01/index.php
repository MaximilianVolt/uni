<?php

  #region

  require "./class/classes.php";

  $article = new Article(0, "A", "B", "C", date("Y-m-d"), new Image(
    "file.png", "Alt text"
  ));

  $is_admin = true;
  $variable_page = "home.php";
  $css_rainbow_class = "text";

  if ($is_admin)
    $variable_page = "admin.php";

  #endregion



  class Link
  {
    private static string $folder;

    private static int $global_id = 0;

    private int $id;

    public function __construct(
      private string $filename,
      private string $description,
    ) {
      $this->id = self::$global_id++;
    }

    public function get_file_path(): string
    {
      return $_SERVER['DOCUMENT_ROOT'] . DIRECTORY_SEPARATOR . $this->filename;
    }

    public function get_description(): string
    {
      return $this->description;
    }
  }



  $linked_pages = [
    new Link("work-with-us.php", "Work with us"),
    new Link("partners.php", "Our partners"),
    new Link("mission.php", "Our mission"),
    new Link("about.php", "About us")
  ];
?>
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <script src="./script.js" defer></script>
    <link href="./style.css" type="text/css" rel="stylesheet">
    <title><?= $article->format_header() ?></title>
  </head>
  <body>
    <nav>
      <?php if ($is_admin): ?>
        <a href="<?= $variable_page ?>">Home page</a>
      <?php endif ?>
    </nav>
    <?php for ($i = 0; $i < 5; ++$i): ?>
      <p id="paragraph-<?= $i ?>">
        Ciao, io sono il <?= $i + 1 ?>&deg; paragrafo.<br>
      </p>
    <?php endfor ?>
    <p id="<?= true ? $css_rainbow_class : '' ?>">ID: "text"</p>
    <!-- <img src="<?= ""/* $article->img->get_path() */ ?>"> -->
  </body>
  <noscript>Error: JavaScript is disabled.</noscript>
</html>
