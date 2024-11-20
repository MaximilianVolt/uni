#include <stdio.h>



#warning If the program output is unexpected, it's not the programmer's fault.

#define REAL_SIZE 1 +
#define BUFFER_SAFE 1 +

#define MENU_SIZE 4
#define MAX_STRLEN 23
#define MAX_KEY_STRLEN 7
#define CHAR_IS_LETTER(c) (((c) | 0x20) - 'a' < 26u)

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

u32 cipher_get_text(i8*, u32);
void cipher_get_plaintext(i8*);
u32 cipher_sanitize_text(i8*);
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

  console_success("<-- Program terminated successfully -->\n");

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
 * @brief Gets the user-inputted plaintext string and sanitizes it.
 * @param str The string to save
 */

void cipher_get_plaintext(i8* str)
{
  console_print("\nType in your plaintext: ", ANSI_COLOR_CYAN);
  cipher_get_text(str, BUFFER_SAFE REAL_SIZE MAX_STRLEN);
}



/**
 * @brief Gets the user-inputted string and sanitizes it. Returns the string length.
 * @param str The string to save.
 * @param size The size of the string.
 */

u32 cipher_get_text(i8* str, u32 size)
{
  if (fgets(str, size, stdin))
  {
    #include <string.h>
    i8* p = strchr(str, '\n');

    if (p)
      *p = 0;
    else
      scanf("%*[^\n]"), scanf("%*c");
  }

  u8 str_len = cipher_sanitize_text(str);

  if (!str_len)
  {
    console_error("<-- String must contain alphabetic characters -->");
    return 0;
  }

  printf(
    ANSI_COLOR_CYAN "Filtered input: " ANSI_COLOR_YELLOW "%s (%d)\n" ANSI_COLOR_RESET,
    str, str_len
  );

  return str_len;
}



/**
 * @brief Filters all the alphabetic characters in a string and sets them to lowercase. It returns the character count.
 * @param str The string to filter.
 */

u32 cipher_sanitize_text(i8* str)
{
  u32 r = 0, w = 0;

  while (str[r])
    if (CHAR_IS_LETTER(str[r++]))
      str[w++] = str[r - 1] | 0x20;

  str[w] = '\0';

  return w;
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

  console_print("\n<-- Vigenere encoding selected -->\n", ANSI_COLOR_MAGENTA);
  console_print("\nType in the key: ", ANSI_COLOR_CYAN);

  i8 key[BUFFER_SAFE REAL_SIZE MAX_KEY_STRLEN]
    , encoded[BUFFER_SAFE REAL_SIZE MAX_STRLEN]
    , key_len = cipher_get_text(key, BUFFER_SAFE REAL_SIZE MAX_KEY_STRLEN)
    , str_len = 0
  ;

  if (!key_len)
    return;

  while (str[++str_len]);

  #define __adapt - 194

  for (u8 i = 0; str[i]; ++i)
    encoded[i] = (str[i] + key[i % key_len] __adapt) % 26 + 'a';

  encoded[str_len] = '\0';

  printf(ANSI_COLOR_CYAN "Encoded word: " ANSI_COLOR_YELLOW "%s\n", encoded);
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
  console_print("\nType in the key: ", ANSI_COLOR_CYAN);

  i8 key[BUFFER_SAFE REAL_SIZE MAX_KEY_STRLEN]
    , key_len = cipher_get_text(key, BUFFER_SAFE REAL_SIZE MAX_KEY_STRLEN)
  ;

  #define LETTER_SKIPPED 'j'
  #define LETTER_PLACEHOLDER 'x'

  if (!key_len)
    return;

  if (key_len & 1)
  {
    str[key_len++] = LETTER_PLACEHOLDER;
    str[key_len] = '\0';
  }

  i8 str_len = 0;

  while (str[++str_len]);

  if (str_len & 1)
  {
    str[str_len++] = LETTER_PLACEHOLDER;
    str[str_len] = '\0';
  }

  #define MAT_SIZE 5

  u8 fill = 0;
  u32 used_chars = 1 << (LETTER_SKIPPED - 'a');
  i8 mat[MAT_SIZE][MAT_SIZE]
    , encoded[BUFFER_SAFE REAL_SIZE MAX_STRLEN]
  ;

  for (u8 i = 0; i < key_len; ++i)
  {
    u8 ch_bit = key[i] - 'a';

    if (!(used_chars >> ch_bit & 1))
    {
      mat[fill / MAT_SIZE][fill % MAT_SIZE] = key[i];
      used_chars |= 1 << ch_bit;
      fill++;
    }
  }

  console_print("Adapted input: ", ANSI_COLOR_CYAN);
  console_set_color(ANSI_COLOR_YELLOW);
  
  for (u8 i = 0; i < fill; ++i)
    printf("%c", mat[i / MAT_SIZE][i % MAT_SIZE]);

  printf(" (%d)\n", fill);
  console_reset_color();

  for (u8 ch = 0; ch < 26; ++ch)
  {
    if (!(used_chars >> ch & 1))
    {
      mat[fill / MAT_SIZE][fill % MAT_SIZE] = ch + 'a';
      used_chars |= 1 << ch;
      fill++;
    }
  }



  /* Encode word */

  printf(ANSI_COLOR_CYAN "Encoded word: " ANSI_COLOR_YELLOW "%s\n", encoded);
}
