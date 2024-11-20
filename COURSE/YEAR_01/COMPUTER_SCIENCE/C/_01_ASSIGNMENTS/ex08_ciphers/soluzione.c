#include <stdio.h>



#warning You must hit [ENTER] 2 times for the program to take your string inputs.

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

#define console_print(str, col) printf("%s%s" ANSI_COLOR_RESET, col, str)
#define console_reset_color()   printf(ANSI_COLOR_RESET)
#define console_set_color(col)  printf(col)
#define console_error(msg)      console_print("\n" msg "\n", ANSI_COLOR_RED)
#define console_success(msg)    console_print("\n" msg "\n", ANSI_COLOR_GREEN)



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
  i8 str[BUFFER_SAFE REAL_SIZE MAX_STRLEN];
  u8 opt = 0, invalid = 0;

  do
  {
    const char* menu[MENU_SIZE] = {
      "Quit",
      "Input new plaintext",
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

  console_success("<-- Program terminated successfully -->");

  return 0;
}



/**
 * @brief Prints the menu to the user.
 * @param menu The list of items to print.
 */

void console_menu_show(const i8** menu)
{
  console_print("\nA CIPHER'S WORLD - MAIN MENU\n\n", ANSI_COLOR_MAGENTA);

  for (u8 i = 0; i < MENU_SIZE; ++i)
    printf(
      ANSI_COLOR_CYAN "%d. "
        ANSI_COLOR_YELLOW "%s\n"
        ANSI_COLOR_RESET,
      i,
      menu[i]
    );

  printf("\n");
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

  printf("%s", message);
  invalid = !scanf(format, var) || *var >= MENU_SIZE;
  console_menu_input_buffer_clear();

  if (invalid)
    console_error("<-- Invalid input provided -->");

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
  console_print("\nType in your plaintext: ", ANSI_COLOR_CYAN);
  fgets(str, BUFFER_SAFE REAL_SIZE MAX_STRLEN, stdin);
  //scanf(__fmt_str(MAX_STRLEN), str);
  console_menu_input_buffer_clear();

  cipher_sanitize_plaintext(str);
  printf(
    ANSI_COLOR_CYAN "Filtered input: " ANSI_COLOR_YELLOW "%s\n" ANSI_COLOR_RESET,
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

void cipher_encode_vigenere(i8* str)
{
  if (*str == '\0')
  {
    console_error("<-- You must provide a non-empty plaintext -->");
    return;
  }

  i8 key[BUFFER_SAFE REAL_SIZE MAX_KEY_STRLEN]
    , encoded[BUFFER_SAFE REAL_SIZE MAX_STRLEN]
    , str_len = 0
    , key_len = 0;

  console_print("\n<-- Vigenere encoding selected -->\n", ANSI_COLOR_MAGENTA);

  console_print("\nType in the key: ", ANSI_COLOR_CYAN);
  fgets(key, BUFFER_SAFE MAX_KEY_STRLEN, stdin);
  console_menu_input_buffer_clear();
  cipher_sanitize_plaintext(key);

  printf(
    ANSI_COLOR_CYAN "\nFiltered input: " ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET,
    key
  );

  if (!*key)
  {
    console_error("<-- You must provide a non-empty plaintext -->");
    return;
  }

  while (str[++str_len]);
  while (key[++key_len]);

  #define __adapt - 194

  for (u8 i = 0; str[i]; ++i)
    encoded[i] = (str[i] + key[i % key_len] __adapt) % 26 + 'a';

  encoded[str_len] = '\0';

  printf(ANSI_COLOR_CYAN "\nEncoded word: " ANSI_COLOR_YELLOW "%s\n", encoded);
}



/**
 * @brief Encodes the user's input using the Playfair cypher.
 * @param str The plaintext to encode.
 */

void cipher_encode_playfair(i8* str)
{
  if (!*str)
  {
    console_error("<-- You must provide a non-empty plaintext -->");
    return;
  }

  console_print("\n\n<-- Playfair encoding selected -->\n\n", ANSI_COLOR_MAGENTA);

  i8 str_len = 0
    , key_len = 0
    , skipped_letter = 'j'
    , key[BUFFER_SAFE REAL_SIZE MAX_KEY_STRLEN]
  ;

  while (str[++str_len]);

  if (str_len & 1)
  {
    str[str_len++] = 'x';
    str[str_len] = '\0';
  }

  /* Input key and sanitize it */

  #define MAT_SIZE 5

  i32 used_chars = 1 << skipped_letter - 'a';
  i8 mat[MAT_SIZE][MAT_SIZE]
    , fill = 0
  ;

  while (key[++key_len]);

  for (u8 i = 0; i < key_len; ++i)
    if ((used_chars >> key[i] - 'a' & 1) == 0)
      mat[fill / MAT_SIZE][fill % MAT_SIZE] = key[i];

  for (u8 ch = 0; ch < 26; ++ch)
    if ((used_chars >> ch & 1) == 0)
      mat[fill / MAT_SIZE][fill % MAT_SIZE] = ch + 'a';
}
