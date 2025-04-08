<?php
  declare(strict_types=1);

  use Src\Classes\TestClass;

  mail("massimilianovolturno@gmail.com", "Test", "Ciao, questo è un test");

  require_once '../config.php';

  \Src\Classes\TestStaticClass::override("Ciao!");
?>

<?php require INCLUDE_ROOT . 'header.php' ?>
<main>
  <div class="main">
    <table class="table">
      <thead>
        <?php for ($i = 0; $i < 3; ++$i): ?>
          <th><?= "Col $i" ?></th>
        <?php endfor ?>
      </thead>
      <tbody>
        <?php for ($i = 0; $i < 5; ++$i): ?>
          <tr>
            <?php for ($j = 0; $j < 3; ++$j): ?>
              <td><?= "Hi $j" ?></td>
            <?php endfor ?>
          </tr>
        <?php endfor ?>
      </tbody>
      <tfoot>
        <tr>
          <td colspan="3">Total: <?= rand(0, 100) ?></td>
        </tr>
      </tfoot>
    </table>
  </div>
  <?php
    $inst = new TestClass("ciaoaoao");
    echo $inst->prop;
  ?>
  <a href="./i2.php">Link</a>
</main>


<?php

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
  $links = directory_get_contents();

  function directory_get_contents(string $path = __DIR__): array
  {
		if (is_file($path))
			return [new IndexLink(pathinfo($path))];

		$files = array_diff(scandir($path), ['.', '..']);
		$outfiles = [];

		foreach ($files as $file)
      if (is_dir($file) || is_file($file))
        $outfiles = array_merge(
          $outfiles,
          directory_get_contents(
            $path . DIRECTORY_SEPARATOR . pathinfo($file)['basename']
          )
        );

		return $outfiles;
  }
?>

<div class="link-container">
  <?php foreach ($links as $link): ?>
    <a class="link" href="<?= $link->formatPath(__DIR__) ?>">
      <div class="link">
        <header>
          <span>
            <?= $link->getFolder() . DIRECTORY_SEPARATOR ?>
          </span>
          <?= $link->getFilename() ?>
        </header>
        <span class="link">
          <?= $link->formatPath() ?>
        </span>
      </div>
    </a>
  <?php endforeach ?>
</div>

<?php require INCLUDE_ROOT . 'footer.php' ?>