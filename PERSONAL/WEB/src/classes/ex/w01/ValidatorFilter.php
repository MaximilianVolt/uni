<?php

  declare(strict_types=1);



  namespace W01;



  enum ValidatorFilter: string
  {
    case VALIDATE_INT = 'int';
    case VALIDATE_FLOAT = 'float';
    case VALIDATE_STRING = 'string';
    case VALIDATE_EMAIL = 'email';
    case VALIDATE_URL = 'url';
    case VALIDATE_INT_ARR = 'int[]';
    case VALIDATE_FLOAT_ARR = 'float[]';
    case VALIDATE_STRING_ARR = 'string[]';
  }
