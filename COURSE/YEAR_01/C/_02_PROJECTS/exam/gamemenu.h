#ifndef GAMEMENU_H

  #define GAMEMENU_H



  /// Libraries



  #include <stdio.h>
  #include <stdlib.h>
  #include "gametypes.h"



  /// Utils



  #define FROM                           0 +
  #define BUF_SAFE                       1 +
  #define BUF_INPUT_NUM_MAXLEN           7

  #define CHAR_IS_DIGIT(c)               ((c) - '0' < 10u)
  #define CHAR_IS_UPPERCASE(c)           ((c) - 'A' < 26u)
  #define CHAR_IS_LOWERCASE(c)           ((c) - 'a' < 26u)
  #define CHAR_IS_LETTER(c)              (((c) | 0x20) - 'a' < 26u)
  #define CHAR_TO_UPPERCASE(c)           ((c) ^ CHAR_IS_LOWERCASE(c) << 5)
  #define CHAR_TO_LOWERCASE(c)           ((c) | CHAR_IS_UPPERCASE(c) << 5)
  #define CHAR_TO_SHIFTCASE(c)           ((c) ^ (CHAR_IS_LETTER(c)) << 5)
  #define CHAR_IS_ALLOWED(c)             (CHAR_IS_LETTER(c) || CHAR_IS_DIGIT(c) || ((c) == '_'))



  /// Console text



  #define __EOL__                        "\n"
  #define __FMT_U8__                     "%hu"
  #define __FMT_PTR__                    "%p"
  #define __FMT_L__                      "<-- "
  #define __FMT_R__                      " -->"
  #define __ANSI_COLOR_RED__             "\x1b[31m"
  #define __ANSI_COLOR_GREEN__           "\x1b[32m"
  #define __ANSI_COLOR_YELLOW__          "\x1b[33m"
  #define __ANSI_COLOR_BLUE__            "\x1b[34m"
  #define __ANSI_COLOR_MAGENTA__         "\x1b[35m"
  #define __ANSI_COLOR_CYAN__            "\x1b[36m"
  #define __ANSI_COLOR_RESET__           "\x1b[0m"
  #define __CONSOLE_CLEAR__              "\e[1;1H\e[2J"



  /// Console macros



  #define scan                           sscanf
  #define print                          printf
  #define console_print(msg)             print("%s", msg)
  #define console_set_color(col)         console_print(col)
  #define console_reset_color()          console_print(__ANSI_COLOR_RESET__)
  #define console_print_color(msg, col)  print(col "%s" __ANSI_COLOR_RESET__, msg)
  #define console_print_header(msg, col) print(col __EOL__  __FMT_L__ "%s" __FMT_R__ __EOL__ __ANSI_COLOR_RESET__, msg)



  /// Error messages



  #define __ERR_INVALID_INPUT__  			   "Invalid input provided"
  #define __ERR_INVALID_CHARACTERS__     "Input produced empty result: invalid character combination"



  /// Function declarations



  u16    string_length                        (string str);
  u8     string_includes_char                 (string str   , c8 ch);
  string string_uppercase                     (string str);
  string string_lowercase                     (string str);
  string string_shiftcase                     (string str);
  string string_copy                          (string dest  , string src   , u16 dest_size);
  u8     string_includes_substring            (string str   , string substr);
  u8     string_includes_substring_ignorecase (string str   , string substr);
  u8     string_equals                        (string str1  , string str2);
  u8     string_equals_ignorecase             (string str1  , string str2);
  i8     string_compare                       (string str1  , string str2);
  i8     string_compare_ignorecase            (string str1  , string str2);
  u8     menu                                 (string header, string* items, u80 conditions, u8 count, u8 offset, string msg, string err, string fmt, u8* var);
  void   menu_print                           (string header, string* items, u80 conditions, u8 count, u8 offset);
  u8     menu_input_number                    (string msg   , string err   , string fmt    , u8* var , u8 count , u8 offset);
  u8     menu_input_string                    (string buf   , u8 size);
  u8     menu_input_filter_string             (string str);
  void   menu_input_buffer_clear              ();

#endif