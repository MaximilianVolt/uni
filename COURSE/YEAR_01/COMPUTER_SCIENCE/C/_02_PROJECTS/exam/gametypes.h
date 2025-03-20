/// Libraries



#include <stdlib.h>



/// Tokenizers



#define __str(x)                         #x
#define __concat(a, b)                   a ## b
#define __xstr(x)                        __str(x)
#define __xconcat(a, b)                  __concat(a, b)



/// Utils



#define until(cond)                      while (!(cond))
#define array_length(arr)                (sizeof arr / sizeof arr[0])
#define deallocate(p)                    ((p) = (p) ? (free((p)), NULL) : NULL)
#define flag_is_set(field, flag)         ((field) >> (flag) & 1)
#define flag_set(field, flag)            ((field) |= 1 << (flag))
#define flag_toggle(field, flag)         ((field) ^= 1 << flag)
#define flag_clear(field, flag)          ((field) &= ~(1 << flag))
#define flag_set_cond(field, flag, cond) ((field) = ((field) & ~(1 << (flag))) | (cond) << (flag))



/// Types



typedef unsigned long long int u80;
typedef unsigned long int      u64;
typedef unsigned int           u32;
typedef unsigned short int     u16;
typedef unsigned char           u8;

typedef signed long long int   i80;
typedef signed long int        i64;
typedef signed int             i32;
typedef signed short int       i16;
typedef signed char             i8;
typedef char                    c8;

typedef long double           f128;
typedef double                 f64;
typedef float                  f32;

typedef void                   v64;
typedef c8*                 string;
