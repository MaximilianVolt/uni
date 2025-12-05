#include <stdio.h>



#define se                if
#define altrimenti        else
#define compara           switch
#define mentre            while
#define fai               do
#define per               for
#define ritorna           return
#define caso              case
#define interrompi        break
#define continua          continue
#define costante          const
#define struttura         struct
#define unione            union
#define statico           static
#define esterno           extern
#define enumeratore       enum
#define dereferenzia(var) (*var)
#define indirizza(var)    (&var)
#define puntatore         *
#define nullo             NULL
#define stampa            printf
#define digita            scanf

#define __FMT_NUMERO__     "%ld"
#define __FMT_NUMERO_SS__  "%lu"
#define __FMT_DECIMALE__   "%.3lf"
#define __FMT_CARATTERE__  "%c"
#define __FMT_STRINGA__    "%s"
#define __FMT_PUNTATORE__  "%p"



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



typedef i80    numero;
typedef f128   decimale;
typedef c8     carattere;
typedef i8     vero_falso;
typedef i8     interruttore;
typedef void   vuoto;
typedef string stringa;



#define programma numero main
#define ripeti(tot_volte) per (numero contatore = 1; contatore <= tot_volte; ++contatore)
#define falso 0
#define spento falso
#define vero 1
#define acceso vero

#define prende =
#define vale ==