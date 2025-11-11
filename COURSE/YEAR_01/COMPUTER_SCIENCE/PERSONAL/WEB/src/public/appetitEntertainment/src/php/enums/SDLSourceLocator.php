<?php

  declare(strict_types=1);

  namespace SDL\Enums;



  /*
   */

  enum SDLSourceLocator : string
  {
    case CSS  = SDL_ROOT . "css" . DIRECTORY_SEPARATOR;
    case JS   = SDL_ROOT . "js" . DIRECTORY_SEPARATOR;
    case DATA = SDL_SRC . "data" . DIRECTORY_SEPARATOR;
    case SESH = SDL_DATA . "sesh" . DIRECTORY_SEPARATOR;
    case IMG  = SDL_DATA . "img" . DIRECTORY_SEPARATOR;
  }
