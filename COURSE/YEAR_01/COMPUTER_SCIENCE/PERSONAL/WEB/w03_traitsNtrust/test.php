Es. 1

<?php
  $year = date("Y");
?>
<footer>
  Copyright <em>&copy;<?= $year ?></em>
</footer>



Es. 2

<?php
  $current_date = date("d/m/Y");
?>
<h1>Oggi &egrave; il 
  <span id="current-date"><?= $current_date ?></span>
</h1>



Es. 3

<?php
  $a = 3;
  $b = 5;

  swap($a, $b);

  function swap(float &$a, float &$b): void
  {
    $_ = $a;
    $a = $b;
    $b = $_;
  }
?>
