<?php
  /*
  "d": giorno (num)
  "m": mese (num)
  "Y": anno (num)
  */

  // Salva la stringa che contiene il formato della data
  $year = (string) date("Y");

  /*
    Shorthand di stampa: <?= espressione ?>
      --> <?= $year ?>

    Stringhe ad apice singolo: interpretano il contenuto alla lettera
      --> '$year'

    Stringhe ad apice doppio: interpretano il contenuto sostituendo i valori delle variabili
      --> "$year" --> "2024"

    ".": Operatore di concatenazione stringhe:
      --> "Ciao " . "mondo!"
  */
?>
<!DOCTYPE html>
<html lang="en">
  <head>
    <title>Sas</title>
    <!--
      Puntatori a cartelle:
      - ".": cartella attuale
      - "..": cartella padre
    -->
    <link rel="stylesheet" type="text/css" href="./style.css">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
  </head>
  <body>
    <h1 class="red">Ciau</h1>
    <h1 class="blue">Ciau 2</h1>
    <h1 id="rurro" class="blue">Ciau 3</h1>
    <p>Oggi &egrave; una bella giornata.</p>
    <footer>
      <h3>&copy;<?= "Ahia $year" ?></h3>
    </footer>
  </body>
</html>
