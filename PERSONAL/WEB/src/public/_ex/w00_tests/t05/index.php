<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>OwO What's This????</title>
  </head>
  <img>
    <h1>heheheheh <?= __DIR__ ?></h1>
    <a href="#def-list">Def List</a>
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
      html {
        scroll-behavior: smooth;
      }
      
      body {
        font-family: "VT323";
      }

      *::marker {
        color: red;
      }
    </style>
    <?php for ($i = 0; $i < 3; ++$i): ?>
      <p>Hi! I am a paragraph no.<?= $i ?></p><br>
    <?php endfor; ?>
    <br><br><br><br><br>
    3 types of lists:
    - Ordered lists
    - Unordered lists
    - Definition lists

    <p>Ordered list</p>
    <ol>
      <li>BBB
        <ul>
          <li>B1
            <ol>
              <li>(Sub B) 1</li>
              <li>(Sub B) 2</li>
              <li>(Sub B) 3</li>
            </ol>
          </li>
          <li>B2</li>
          <li>B3</li>
        </ul>
      </li>
      <li>AAA</li>
      <li>CCC</li>
    </ol>

    <p>Unordered list</p>
    <ul>
      <li>AAA</li>
      <li>BBB</li>
      <li>CCC</li>
    </ul>

    <p id="def-list">Definition lists</p>
    <dl>
      <?php for ($i = 0; $i < 5; ++$i): ?>
        <dt>Term <?= $i + 1 ?></dt>
        <dd>Definition of the term no.<?= $i + 1 ?></dd>
      <?php endfor; ?>
    </dl>

      <!--
        . (current folder)
        .. (parent folder)
        / (folder separator, if 1st character, it means access to the root folder)
        name (child element)

        w00_tests/
        \ t04/
        \ \ index.php <-- We want to target this file
        \
        \ t05/
        \ \ index.php <-- We are here

        f2/
        \ t06/
        \ \ ...
      -->
    <a href="/ex/styles/common.css" target="_blank">This is a link!</a>

    <figure>
      <img src="https://static1.e621.net/data/d0/f2/d0f2bc35b1b20866484341905b883d80.gif"
        alt="Porn.gif (these guys are having sex)" loading="lazy"
        title="Guys having sex"
  
        width="80px"
      >
      <figcaption>
        Sex is truly one of the nicest things to have ever&shy; <wbr>
        existed on this planet.
      </figcaption>
    </figure>

    <picture>
      <source media="(min-width:500px)" srcset="https://static1.e621.net/data/d0/f2/d0f2bc35b1b20866484341905b883d80.gif">
      <source media="(min-width:380px)" srcset="https://cdn.discordapp.com/attachments/1347571880554664007/1393112611788165170/SPOILER_20250610_195408.jpg?ex=68851a79&is=6883c8f9&hm=277b425e7d24025aea59f5a95b92236136962c74e18a0d09a28677dd1aa8264e&">
      <img src="https://static1.e621.net/data/d0/f2/d0f2bc35b1b20866484341905b883d80.gif" width="100px">
    </picture>

    <style>
      img {
        vertical-align: middle;
      }
    </style>
  </body>
</html>