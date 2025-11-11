<?php

  declare(strict_types=1);

  namespace SDL\Enums;



  /*
   */

  enum SDLCharacterPronoun : int
  {
    case PERSONAL_SUBJ = 0;
    case PERSONAL_OBJ = 1;
    case POSSESSIVE = 2;
    case POSSESSIVE_REFL = 3;
  }
