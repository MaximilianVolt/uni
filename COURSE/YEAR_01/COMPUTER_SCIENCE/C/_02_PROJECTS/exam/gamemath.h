/// Libraries

#ifndef GAMEMATH_H

  #define GAMEMATH_H

  #include <time.h>
  #include <stdlib.h>
  #include <stdarg.h>
  #include "gametypes.h"



  /// Macros



  #define GAME_RAND_MOD 0x45



  /// Function declarations



  f64 absv                    (f64 x);
  i8  sign                    (f64 x);
  f64 min                     (u8 count , ...);
  f64 max                     (u8 count , ...);
  f64 clamp                   (f64 val  , f64 min_v, f64 max_v);
  u16 irandom                 (u16 max_v);
  u16 irandom_inclusive       (u16 max_v);
  u16 irandom_range           (u16 min_v, u16 max_v);
  u16 irandom_range_inclusive (u16 min_v, u16 max_v);
  f64 array_sum               (f64* arr , u16 len);
  i16 chance_weighted         (f64* arr , u16 len);
  u8  chance                  (f64 e);

#endif