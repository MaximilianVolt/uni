<?php require_once __DIR__ . DIRECTORY_SEPARATOR . "../vendor/autoload.php"; ?>
    <footer>
      <h3>
        <?=
          \App\Functions::pre(
            \App\TestStaticClass::override(
              "CHOOSE YOUR NEXT CHALLENGE"
            )
            ::string()
          )
        ?>
      </h3>
    </footer>
  </body>
</html>