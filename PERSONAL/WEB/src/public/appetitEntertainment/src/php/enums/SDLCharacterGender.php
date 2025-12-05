<?php

  declare(strict_types=1);

  namespace SDL\Enums;



  /*
   * Responsible for character pronouns.
   */

  enum SDLCharacterGender : string
  {
    case M  = 'M';
    case F  = 'F';
    case NB = 'NB';



    public static function getPronouns(SDLCharacterGender $p) {
      return [
        SDLCharacterGender::M->value  => ['he'  , 'him' , 'his'  , 'his'   ],
        SDLCharacterGender::F->value  => ['she' , 'her' , 'her'  , 'hers'  ],
        SDLCharacterGender::NB->value => ['they', 'them', 'their', 'theirs']
      ][
        $p->value
      ];
    }
  }
