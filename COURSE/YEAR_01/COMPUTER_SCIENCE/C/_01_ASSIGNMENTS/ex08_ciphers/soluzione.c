#pragma region Definitions

#include <stdio.h>
#include <string.h>



#warning No warnings found.



#define SIZE_REAL 1 +
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



//    Core functions

u32   cipher_get_text(i8*, u32);
u32   cipher_sanitize_text(i8*);



//    Interface functions

void  cipher_get_plaintext(i8*);
void  cipher_encode_vigenere(i8*);
void  cipher_encode_playfair(i8*);
void  console_menu_show(const i8**);
void  console_menu_input_buffer_clear();
u8    console_menu_get_input(const i8*, const i8*, u8*);

#pragma endregion



i32 main()
{
  i8 str[BUFFER_SAFE SIZE_REAL MAX_STRLEN];
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
  console_print("\n\n<-- Plaintext input selected -->\n\n", ANSI_COLOR_MAGENTA);
  console_print("\nNew plaintext: ", ANSI_COLOR_CYAN);
  cipher_get_text(str, BUFFER_SAFE SIZE_REAL MAX_STRLEN);
  printf("\n");
}



/**
 * @brief Gets the user-inputted string and sanitizes it. Returns the string length.
 * @param str The string to save.
 * @param size The size of the string.
 */

u32 cipher_get_text(i8* str, u32 size)
{
  if (
    fgets(str, size, stdin)
    && !strchr(str, '\n')
  ) {
    console_menu_input_buffer_clear();
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
  #pragma region Vigenere validation

  if (*str == '\0')
  {
    console_error("<-- You must provide a non-empty plaintext -->");
    return;
  }

  console_print("\n\n<-- Vigenere encoding selected -->\n\n", ANSI_COLOR_MAGENTA);
  console_print("\nType in the key: ", ANSI_COLOR_CYAN);

  i8 key[BUFFER_SAFE SIZE_REAL MAX_KEY_STRLEN]
    , encoded[BUFFER_SAFE SIZE_REAL MAX_STRLEN]
    , key_len = cipher_get_text(key, BUFFER_SAFE SIZE_REAL MAX_KEY_STRLEN)
    , str_len = 0
  ;

  if (!key_len)
    return;

  while (str[(i32) ++str_len]);

  #pragma endregion

  #define __adapt - 194

  for (u8 i = 0; str[i]; ++i)
    encoded[i] = (str[i] + key[i % key_len] __adapt) % 26 + 'a';

  encoded[(i32) str_len] = '\0';

  printf(ANSI_COLOR_CYAN "\nEncoded word: " ANSI_COLOR_YELLOW "%s\n\n", encoded);
}



/**
 * @brief Encodes the user's input using the Playfair cypher.
 * @param str The plaintext to encode.
 */

void cipher_encode_playfair(i8* str)
{
  #pragma region Playfair validation

  if (!*str)
  {
    console_error("<-- You must provide a non-empty plaintext -->");
    return;
  }

  console_print("\n\n<-- Playfair encoding selected -->\n\n", ANSI_COLOR_MAGENTA);
  console_print("\nType in the key: ", ANSI_COLOR_CYAN);

  i8 key[BUFFER_SAFE SIZE_REAL MAX_KEY_STRLEN]
    , key_len = cipher_get_text(key, BUFFER_SAFE SIZE_REAL MAX_KEY_STRLEN)
  ;

  if (!key_len)
    return;

  #define LETTER_SKIPPED 'j'
  #define LETTER_SUBSTITUTE 'i'
  #define LETTER_PLACEHOLDER 'x'

  u8 str_len = -1;
  i8 cstr[BUFFER_SAFE SIZE_REAL MAX_STRLEN], *c = cstr;

  while ((*c = str[(i32) ++str_len]))
    if (*c++ == LETTER_SKIPPED)
      *(c - 1) = LETTER_SUBSTITUTE;

  *c = '\0';

  #pragma endregion

  #pragma region Playfair setup

  #define MAT_SIZE 5
  #define MAT_AREA (MAT_SIZE * MAT_SIZE)
  #define __x(a) ((a) % MAT_SIZE)
  #define __y(a) ((a) / MAT_SIZE)

  u8 filled = 0;
  i8 mat[MAT_SIZE][MAT_SIZE]
    , map[BUFFER_SAFE MAT_AREA]
  ;
  u32 used_chars = 1 << (LETTER_SKIPPED - 'a');

  for (u8 i = 0; i < key_len && filled < MAT_AREA; ++i)
  {
    u8 ch_bit = key[i] - 'a';

    if (!(used_chars >> ch_bit & 1))
    {
      mat[__y(filled)][__x(filled)] = key[i];
      used_chars |= 1 << ch_bit;
      map[ch_bit] = filled++;
    }
  }

  console_print("Adapted input: ", ANSI_COLOR_CYAN);
  console_set_color(ANSI_COLOR_YELLOW);

  for (u8 i = 0; i < filled; ++i)
    printf("%c", mat[__y(i)][__x(i)]);

  printf(" (%d)\n", filled);
  console_reset_color();

  for (u8 ch = 0; filled < MAT_AREA; ++ch)
  {
    if (!(used_chars >> ch & 1))
    {
      mat[__y(filled)][__x(filled)] = ch + 'a';
      used_chars |= 1 << ch;
      map[ch] = filled++;
    }
  }

  u8 r = 0, w = 0;
  i8 formatted[BUFFER_SAFE ((SIZE_REAL MAX_STRLEN) << 1)];

  for (; r < str_len; r += 2)
  {
    formatted[w++] = cstr[r];
    formatted[w++] = cstr[r] == cstr[r + 1]
      ? (--r, LETTER_PLACEHOLDER)
      : cstr[r + 1]
    ;
  }

  if (!cstr[r - 1])
    formatted[w - 1] = LETTER_PLACEHOLDER;

  formatted[w] = '\0';

  #pragma endregion

  #pragma region Playfair encoding

  #define __same_col(a, b) (__x(a) == __x(b))
  #define __same_row(a, b) (__y(a) == __y(b))
  #define __coords(y, x) ((y) % MAT_SIZE * MAT_SIZE + (x) % MAT_SIZE)

  i8 encoded[BUFFER_SAFE ((SIZE_REAL MAX_STRLEN) << 1)];

  for (u8 i = 0, c1, c2, temp; i < w; i += 2)
  {
    c1 = map[formatted[(i32) i] - 'a'];
    c2 = map[formatted[i + 1] - 'a'];

    if (__same_row(c1, c2))
      c1 = __coords(__y(c1), __x(c1) + 1),
      c2 = __coords(__y(c2), __x(c2) + 1);

    else if (__same_col(c1, c2))
      c1 = __coords(__y(c1) + 1, __x(c1)),
      c2 = __coords(__y(c2) + 1, __x(c2));

    else
      c1 = __coords(__y(temp = c1), __x(c2)),
      c2 = __coords(__y(c2), __x(temp));

    encoded[i] = mat[__y(c1)][__x(c1)];
    encoded[i + 1] = mat[__y(c2)][__x(c2)];
  }

  encoded[w] = '\0';

  #pragma endregion

  console_print("\nAdapted word: ", ANSI_COLOR_CYAN);
  console_set_color(ANSI_COLOR_YELLOW);

  for (u8 i = 0; i < w; i += 2)
    printf("%c%c ", formatted[i], formatted[i + 1]);

  printf("(%d)\n" ANSI_COLOR_CYAN "Encoded word: " ANSI_COLOR_YELLOW, w);

  for (u8 i = 0; i < w; i += 2)
    printf("%c%c ", encoded[i], encoded[i + 1]);

  printf("(%d)\n\n" ANSI_COLOR_RESET, w);
}
