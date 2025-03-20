<?php

  #region

  require "./class/classes.php";

  $article = new Article(0, "A", "B", "C", date("Y-m-d"), new Image(
    "file.png", "Alt text"
  ));

  $is_admin = true;
  $variable_page = "home.php";

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
    <p id="text-1">Ciao, io sono un paragrafo.</p>
    <p id="text-2">Ciao, io sono un paragrafo.</p>
    <p id="text-3">Ciao, io sono un paragrafo.</p>
    <p id="text-4">Ciao, io sono un paragrafo.</p>
    <p id="text-5">Ciao, io sono un paragrafo.</p>
    <!-- <img src="<?= ""/* $article->img->get_path() */ ?>"> -->
  </body>
</html>








<!DOCTYPE html>
<html>
  <header>
    <!-- -->
  </header>

<?php require_once "header.php" ?>
  <main></main>
<?php require_once "footer.php" ?>


<!DOCTYPE html>
<html lang="en">
<head>
  <title>Document</title>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>
<a>
  div>ul>li*17#$$
  a+b
  a>b
  main>(div>h2)*2
  main.class
  main#id
  main{CIAO}
  div#$$*6
</a>
</html>





<?php

	class DB
	{
		private static $conn = null;

		public static function connect(string $dsn): void
		{
			DB::$conn = new PDO("...");
		}

		public static function query(string $query): void
		{
			try
			{
				// ...
			}
			catch (PDOException $ex)
			{
				// ...
			}
		}
	}




  $pdo = new PDO("...");

  try
  {
    // ...
  }
  catch (PDOException $ex)
  {
    // ...
  }

  $pdo = null;