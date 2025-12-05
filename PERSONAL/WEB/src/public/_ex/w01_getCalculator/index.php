<?php

  /**
  * Exercise 1: Build a simple calculator in procedural PHP.
  * The script should take two numbers and an operation (+, -, *, /) via GET parameters
  * and return the result. Handle division by zero.
  */

  declare(strict_types=1);

  const ERR_UNRECOGNISED_OPERATION = 'Unrecognised operation';
  const ERR_INVALID_OPERAND = 'Invalid operand provided';
  const RES_UNDEFINED = 'Undefined';
  const RES_INFINITY = 'Infinity';

  require_once __DIR__ . '/../../../vendor/autoload.php';



  $title = '$_GET Calculator';
  $result = 'Submit the form';
  $highlight = 'success';
  $epsilon = 1e-10;
  $operations = [
    '+', '-', '*', '/', '**',
  ];

  if ($_SERVER['REQUEST_METHOD'] === 'GET')
  {
    // [$operand_1, $operand_2, $operation] = array_values(
    //   \W01\Validator::validate([
    //       'operand_1' => $_GET['operand_1'] ?? 0,
    //       'operand_2' => $_GET['operand_2'] ?? 0,
    //       'operation' => $_GET['operation'] ?? $operations[0]
    //     ], [
    //       'operand_1' => \W01\ValidatorFilter::VALIDATE_FLOAT,
    //       'operand_2' => \W01\ValidatorFilter::VALIDATE_FLOAT,
    //       'operation' => \W01\ValidatorFilter::VALIDATE_STRING
    //     ]
    //   )
    // );

    $operand_1 = get_data('operand_1', false, FILTER_VALIDATE_FLOAT) ?? 0;
    $operand_2 = get_data('operand_2', false, FILTER_VALIDATE_FLOAT) ?? 0;
    $operation = get_data('operation', '') ?? $operations[0];

    $result = $operand_1 !== false && $operand_2 !== false
      ? calculate($operand_1, $operand_2, $operation)
      : ERR_INVALID_OPERAND
    ;

    if (
      $result === ERR_INVALID_OPERAND
      || $result === ERR_UNRECOGNISED_OPERATION
    )
      $highlight = 'failure';
    elseif (is_float($result))
      $result = number_format($result, 10 * ($result - floor($result) !== 0.0), '.', '\'');
  }



  function get_data(string $name, mixed $default = null, int $filter = FILTER_DEFAULT): mixed
  {
    return isset($_GET[$name])
      ? filter_var($_GET[$name], $filter)
      : (
        empty($_GET[$name])
          ? null
          : $default
      )
    ;
  }



  function calculate(float $a, float $b, string $op): float|string
  {
    return match ($op)
    {
      default => ERR_UNRECOGNISED_OPERATION,
      '+' => $a + $b,
      '-' => $a - $b,
      '*' => $a * $b,
      '**' => (
        $a === 0.0 && $b === 0.0
          ? RES_UNDEFINED
          : $a ** $b
      ),
      '/' => (
        $b !== 0.0
          ? $a / $b
          : (
            $a === 0.0
              ? RES_UNDEFINED
              : RES_INFINITY
          )
      )
    };
  }
?>
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title><?= $title ?></title>
    <link href="./style.css" rel="stylesheet" type="text/css">
  </head>
  <body>
    <h1><?= $title ?></h1>
    <form action="<?= pathinfo(__FILE__)['basename'] ?>" method="get">
      <fieldset>
        <legend>Input your operation:</legend>
        <div class="row">
          <input class="operand" autocomplete="off" type="number" step="<?= $epsilon ?>" name="operand_1" value="<?= htmlspecialchars((string) $operand_1) ?>">
          <select class="operator" name="operation">
            <?php foreach ($operations as $op): ?>
              <option value="<?= $op ?>" <?= htmlspecialchars((string) $operation) === $op ? 'selected' : '' ?>>
                <?= $op ?>
              </option>
            <?php endforeach ?>
          </select>
        </div>
        <div class="row">
          <input class="operand" autocomplete="off" type="number" step="<?= $epsilon ?>" name="operand_2" value="<?= htmlspecialchars((string) $operand_2) ?>">
          <input class="operator" type="submit" value="=">
        </div>
      </fieldset>
        <output class="result <?= $highlight ?>" aria-live="polite">
          <span>Result: </span><?= htmlspecialchars((string) $result) ?>
        </output>
    </form>
  </body>
</html>
