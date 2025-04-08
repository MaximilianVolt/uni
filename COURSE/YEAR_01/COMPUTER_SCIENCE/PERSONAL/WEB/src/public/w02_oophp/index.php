<?php
  require 'i1.php';
  require 'c1.php';
  require 'c2.php';
?>
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link href="./style.css" rel="stylesheet" type="text/css">
    <title>Document</title>
  </head>
  <br>
    <?= "C1 Class name: " . Oop\C1::printClass() ?><br>
    <?= "C2 Class name: " . Oop\C2::printClass() ?><hr>

    <details>
      <summary>About me</summary>
      <p>Here are a couple cool things about me.</p>
    </details>
    <br>
    Press <kbd>[A]</kbd> to continue.
    <br><br>
    <mark>Highlighted</mark> text!
    <br><br>
    <u>Underlined text</u>
    <br><br>
    <pre>Preformatted text</pre>

    <p>Normal text</p>
    <small>Small text</small>
    <hr>
    <var>x</var> = 12
    <br><br>
    <p id="long">
      When you have extremely long words, consider using the <samp>&lt;wbr&gt;</samp> tag to divide it in sylla&shy;<wbr>blessssssss!
    </p>

    <hr>

    <samp>This is a sample text</samp>
    <time datetime="2025-04-08 09:24:20">April 8th, 09:24am</time>

    <ruby>
      &sum; <rp>(</rp><rt>Sigma</rt><rp>)</rp>
    </ruby>
    <br>

    <hr>

    <template>This is non-rendered page content that can be worked on using JavaScript</template>

    <menu>
      <li>Action 1</li>
      <li>Action 2</li>
    </menu>

    <hr>
    <meter id="meter" min="0" max="1000" value="0" low="250" high="750" optimum="900">Text</meter>
    <progress id="progress" min="0" value="0" max="1000">Text</progress>
    <hr>

    <script>
      fn = async (e) => {
        e.value = (e.value + 1) % parseInt(e.getAttribute("max"));
        setTimeout(fn, 1, e);
      };

      fn(document.getElementById("meter"));
      fn(document.getElementById("progress"));
    </script>
  </body>
</html>