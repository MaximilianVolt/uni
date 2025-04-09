<?php

  define('APP_ROOT', __DIR__ . DIRECTORY_SEPARATOR);
  define('CLASS_ROOT', APP_ROOT . 'classes' . DIRECTORY_SEPARATOR);
  define('PUBLIC_ROOT', APP_ROOT . 'public' . DIRECTORY_SEPARATOR);
  define('INCLUDE_ROOT', APP_ROOT . '../includes' . DIRECTORY_SEPARATOR);

  require_once APP_ROOT . "../vendor/autoload.php";



	class IndexLink
	{
		private string $folder;
		private string $filename;



		public function __construct(array $pathinfo)
		{
			$this->folder = $pathinfo['dirname'];
			$this->filename = $pathinfo['basename'];
		}



		public function formatPath(string $diff = ''): string
		{
			return str_replace($diff, '', $this->folder) . DIRECTORY_SEPARATOR . $this->filename;
		}



		public function getFilename(): string
		{
			return $this->filename;
		}



    public function getFolder(): string
		{
			return $this->folder == __DIR__
        ? '.'
        : basename($this->folder)
      ;
		}
	}



  $dir = '';
  $links = array_filter(directory_get_contents(), fn($link) => 
    $link->getFilename() === 'index.php'
  );

  function directory_get_contents(string $path = __DIR__): array
  {
		if (is_file($path))
			return [new IndexLink(pathinfo($path))];

		$files = array_diff(scandir($path), ['.', '..']);
		$outfiles = [];

		foreach ($files as $file)
      $outfiles = array_merge($outfiles, 
        directory_get_contents(
          $path . DIRECTORY_SEPARATOR . pathinfo($file)['basename']
        )
      );

		return $outfiles;
  }
?>

<?php include_once INCLUDE_ROOT . "header.php" ?>
<main>
  <div class="link-container">
    <?php foreach ($links as $link): ?>
      <a class="link" href="<?= $link->formatPath(__DIR__) ?>">
        <div class="link">
          <header>
            <span>
              <?= \App\Functions::insertWbr($link->getFolder() . DIRECTORY_SEPARATOR) ?>
            </span>
            <?= \App\Functions::insertWbr($link->getFilename()) ?>
          </header>
          <span class="link">
            <?= \App\Functions::insertWbr($link->formatPath()) ?>
          </span>
        </div>
      </a>
    <?php endforeach ?>
  </div>
</main>
<?php require INCLUDE_ROOT . 'footer.php' ?>