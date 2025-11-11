<?php

  declare(strict_types=1);

  const PH_SCALE_MIN = 0;
  const PH_SCALE_MAX = 14;
  const PH_SCALE_NEUTRAL = 7;

  // pH scale builder
  $title = 'pH Scale Builder';



  function get_ph_scale_class(int $level): string
  {
    $levels = [
      'acid',
      'neutral',
      'basic'
    ];

    return $levels[
      1 + ($level > PH_SCALE_NEUTRAL) - ($level < PH_SCALE_NEUTRAL)
    ];
  }
?>
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link href="./style.css" type="text/css" rel="stylesheet">
    <script src="./script.js" defer></script>
    <title><?= $title ?></title>
  </head>
  <body>
    <h1><?= $title ?></h1>
    <main class="content">
      <?php for ($level = PH_SCALE_MIN; $level <= PH_SCALE_MAX; ++$level): ?>
        <div class="ph-level <?= get_ph_scale_class(PH_SCALE_MAX - $level) ?>">
          <p><?= 'pH ' . PH_SCALE_MAX - $level ?></p>
        </div>
      <?php endfor ?>
    </main>
  </body>
</html>