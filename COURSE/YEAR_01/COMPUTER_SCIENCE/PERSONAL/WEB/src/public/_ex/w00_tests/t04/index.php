<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>OwO What's This????</title>
  </head>
  <body>
    <h1>heheheheh <?= __DIR__ ?></h1> 
    <p><br>&gt;:33333333
    <br><b>AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA but in bold</b>
    <br> Ooooooooo <i><b>bold and italicsssssss</b></i>
    <br><i>aaaaaaaaaaaaaaaaaaaaa but in italics</i>
    <hr>
    <br><strong>eeyruyieeiiryiyeri</strong>
    <br><em>Owooo</em>
    <br><q>Be the manic pixie dream girl that you fuckin' oughta be!</q>
    <br><blockquote>Be the manic pixie dream girl that you fuckin' oughta be!</blockquote>
    <br><abbr title="Negabyte">NB</abbr> - <cite>Our epic visual novel heheheh</cite>
    <br><dfn>skibidi</dfn>
    <br><address>
      <p>123 Ohio Street</p>
      <p>name@example.com</p>
    </address>
    <br><ins>there's no way a bee should be able to fly! Because it can't get its fat little body off the ground</ins>
    <br><del>aaaaacording to all known laws of aviation</del>
    <br><s>adjhskdfhlkjdflkjhsl</s>
    <br>Is this a.....<sub>subtitle🤔</sub><sup>OHHHHHHHHHHHHHHHHHHHHH ITS A SUBSCRIPTTTTTT</sup>
    </p>
    <style>
      @import url('https://fonts.googleapis.com/css2?family=VT323&display=swap');
      body {
        font-family: "VT323";
      }
    </style>
    <?php for($i = 0; $i < 3; ++$i): ?>
      <p>Hi! I am a paragraph no.<?=$i?></p><br>
    <?php endfor;?>
    <dl>
      <dt>01</dt>
      <dd>01</dd>

      <dt>02</dt>
      <dd>02</dd>

      <dt>03</dt>
      <dd>03</dd>
    </dl>
    <style>
      dt {
        text-decoration: underline;
        font-weight: bold;
      }

      dd {
        font-style: oblique;
      }
    </style>
  </body>
</html>