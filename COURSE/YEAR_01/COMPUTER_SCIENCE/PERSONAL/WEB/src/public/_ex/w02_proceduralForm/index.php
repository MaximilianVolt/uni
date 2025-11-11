<?php

  /**
  * Exercise 2: Create a contact form (HTML + PHP) that validates user input (name, email, message).
  * Use procedural PHP to validate required fields and email format.
  * If valid, simulate a message send (no real email needed).
  */

  /*
    +: Fix email text alignment on output div
  */

  declare(strict_types=1);

  require_once __DIR__ . '/../../../vendor/autoload.php';



  $header         = 'Contact form';
  $output_types   = ['failure', 'success'];
  $output_type    = $output_types[0];
  $message_sent   = false;
  $message_error  = "";

  $message_sender       = "";
  $message_sender_email = "";
  $message_content      = "";



  if ($_SERVER['REQUEST_METHOD'] === 'POST')
  {
    // Get data
    $message_sender       = $_POST['name'] ?? "";
    $message_content      = $_POST['message'] ?? "";
    $message_sender_email = $_POST['email'] ?? "";

    // Validate data
    $message_sent = validate([
      [$message_sender, FILTER_UNSAFE_RAW],
      [$message_content, FILTER_UNSAFE_RAW],
      [$message_sender_email, FILTER_VALIDATE_EMAIL],
    ]);

    // Send response back
    if ($message_sent)
      $output_type = $output_types[1];
    else
      $message_error = 'Unable to send message';
  }



  function validate(array $data): bool
  {
    foreach ($data as [$item, $flag])
      if (filter_var($item, $flag) === false)
        return false;

    return true;
  }
?>
<!DOCTYPE html>
  <html lang="en">
  <head>
    <meta charset="UTF-8">
    <title><?= $header ?></title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link href="./style.css" rel="stylesheet" type="text/css">
  </head>
  <body>
    <h1><?= $header ?></h1>
    <form action="<?= pathinfo(__FILE__)['basename'] ?>" method="post">
      <fieldset>
        <legend>Contact form</legend>
        <!-- Name input field -->
        <div>
          <label for="name">Name:</label>
          <br>
          <input autocomplete="off" type="text" id="name" name="name" pattern="(\w *)+">
        </div>
        <!-- Email input field -->
        <div>
          <label for="email">E-mail:</label>
          <br>
          <input autocomplete="off" type="email" id="email" name="email">
        </div>
        <!-- Message input field -->
        <div>
          <label for="message">Message:</label>
          <br>
          <textarea name="message" id="message" placeholder="Enter your message..."></textarea>
        </div>
        <!-- Submit button -->
        <div class="submit">
          <input type="submit" value="Send">
        </div>
      </fieldset>
    </form>
    <!-- Colored box to show action result -->
    <?php if ($message_sent || $message_error): ?>
      <hr>
      <output aria-live="polite">
        <div class="output <?= $output_type ?>">
          <?php if ($message_error): ?>
            <div class="error">
              <?= htmlspecialchars($message_error) ?>
            </div>
          <?php else: ?>
            <!-- Simulated message div -->
            <div class="message-container">
              <div class="message-header">
                <header>
                  <?= htmlspecialchars($message_sender) ?>
                </header>
                <p>
                  <?= \App\Functions::autowbr(htmlspecialchars($message_sender_email)) ?>
                </p>
              </div>
              <div class="message-content">
                <p>
                  <?= htmlspecialchars($message_content) ?>
                </p>
              </div>
            </div>
          <?php endif ?>
        </div>
      </output>
    <?php endif ?>
  </body>
</html>