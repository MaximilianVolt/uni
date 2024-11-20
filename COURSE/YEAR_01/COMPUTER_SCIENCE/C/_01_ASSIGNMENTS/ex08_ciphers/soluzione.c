#include <stdio.h>



#define __str(x) #x
#define __xstr(x) __str(x)
#define __fmt_str(f) "%"__xstr(f)"s"
#define REAL_SIZE 1 +
#define BUFFER_SAFE 1 +

#define MENU_SIZE 4
#define MAX_STRLEN 23
#define MAX_KEY_STRLEN 7
#define CHAR_IS_LETTER(c) ((c | 0x20) - 'a' < 26u)

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define console_print(str, col) printf_s("%s%s" ANSI_COLOR_RESET, col, str)
#define console_reset_color()   printf_s(ANSI_COLOR_RESET)
#define console_set_color(col)  printf_s(col)



typedef unsigned int u32;
typedef unsigned char u8;

typedef int i32;
typedef char i8;



// Core functions

void cipher_get_plaintext(i8*);
void cipher_sanitize_plaintext(i8*);
void cipher_encode_vigenere(i8*);
void cipher_encode_playfair(i8*);



// Interface functions

void console_menu_show(const i8**);
void console_menu_input_buffer_clear();
u8 console_menu_get_input(const i8*, const i8*, u8*);



i32 main()
{
  i8 str[BUFFER_SAFE REAL_SIZE MAX_STRLEN] = "attaccano";
  u8 opt = 0, invalid = 0;

  do
  {
    const char* menu[MENU_SIZE] = {
      "Quit",
      "Input new string",
      "Use Vigenere encoding",
      "Use Playfair encoding"
    };

    console_menu_show(menu);
    invalid = console_menu_get_input(
      ANSI_COLOR_CYAN "Choose an option: " ANSI_COLOR_RESET,
      "%d", &opt
    );

    if (invalid)
      continue;

    if (!opt)
      break;

    void (*menu_funcs[MENU_SIZE - 1])(i8*) = {
      cipher_get_plaintext,
      cipher_encode_vigenere,
      cipher_encode_playfair
    };

    menu_funcs[opt - 1](str);
  }
  while (opt || invalid);

  console_print("\v<-- Program terminated successfully -->\v\n", ANSI_COLOR_GREEN);

  return 0;
}



/**
 * @brief Prints the menu to the user.
 * @param menu The list of items to print.
 */

void console_menu_show(const i8** menu)
{
  printf_s("\v");

  for (u8 i = 0; i < MENU_SIZE; ++i)
    printf_s(
      ANSI_COLOR_CYAN "%d. "
        ANSI_COLOR_YELLOW "%s\n"
        ANSI_COLOR_RESET,
      i,
      menu[i]
    );

  printf_s("\v");
}



/**
 * @brief Gets the user input.
 * @param message The message to show to the user.
 * @param format The format of the input.
 * @param var The variable where to assign the user input.
 */

u8 console_menu_get_input(const i8* message, const i8* format, u8* var)
{
  u8 invalid = 1;

  printf_s("%s", message);
  invalid = !scanf_s(format, var) || *var >= MENU_SIZE;
  console_menu_input_buffer_clear();

  if (invalid)
    console_print("\v<-- Invalid input provided -->\v", ANSI_COLOR_RED);

  // console_menu_input_buffer_clear();

  return invalid;
}



/**
 * @brief Clears the input buffer.
 */

void console_menu_input_buffer_clear()
{
  i8 c;
  while ((c = getchar()) != '\n' && c != EOF);
}



/**
 * @brief Gets the user-inputted string and sanitizes it.
 * @param str The string to save.
 */

void cipher_get_plaintext(i8* str)
{
  console_print("\vType in your plaintext:\t", ANSI_COLOR_CYAN);
  scanf_s(__fmt_str(MAX_STRLEN), str);
  console_menu_input_buffer_clear();

  cipher_sanitize_plaintext(str);
  printf_s(
    ANSI_COLOR_CYAN "Filtered input:\t\t" ANSI_COLOR_YELLOW "%s\v" ANSI_COLOR_RESET,
    str
  );
}



/**
 * @brief Filters all the alphabetic characters in a string and sets them to lowercase.
 * @param str The string to filter.
 */

void cipher_sanitize_plaintext(i8* str)
{
  i8* ptr_w = str;

  while (*str)
    if (CHAR_IS_LETTER(*str++))
      *ptr_w++ = *(str - 1) | 0x20;

  *ptr_w = '\0';
}



/**
 * @brief Encodes the user's input using the Vigenere cypher.
 * @param str The plaintext to encode.
 */

void cipher_encode_vigenere(i8* str2)
{
  // if (*str == '\0')
  // {
  //   console_print("\v<-- You must provide a non-empty plaintext -->\v", ANSI_COLOR_RED);
  //   return;
  // }

  console_print("\v<-- Vigenere encoding selected -->\v", ANSI_COLOR_MAGENTA);

  i8 str[BUFFER_SAFE REAL_SIZE MAX_STRLEN] = "attaccano";
  i8 key[BUFFER_SAFE REAL_SIZE MAX_KEY_STRLEN] = "pane";
  // console_print("\vType in the key:\t", ANSI_COLOR_CYAN);
  // fgets(key, MAX_KEY_STRLEN + 1, stdin);
  // console_menu_input_buffer_clear();

  // cipher_sanitize_plaintext(key);
  printf_s(
    ANSI_COLOR_CYAN "Filtered input:\t" ANSI_COLOR_YELLOW "%s\v" ANSI_COLOR_RESET,
    key
  );

  i8 key_len = 0;
  while (key[++key_len]);

  #define __adapt - 194
  i8 encoded[BUFFER_SAFE REAL_SIZE MAX_STRLEN];

  for (u8 i = 0; str[i]; ++i)
    encoded[i] = (str[i] + key[i % key_len] __adapt) % 26 + 'a';

  printf_s(ANSI_COLOR_CYAN "Encoded word: " ANSI_COLOR_YELLOW "%s", encoded);
}



/**
 * @brief Encodes the user's input using the Playfair cypher.
 * @param str The plaintext to encode.
 */

void cipher_encode_playfair(i8* str)
{
  if (*str == '\0')
  {
    console_print("\v<-- You must provide a non-empty plaintext -->\v", ANSI_COLOR_RED);
    return;
  }

  console_print("\v<-- Playfair encoding selected -->\v", ANSI_COLOR_MAGENTA);
}
