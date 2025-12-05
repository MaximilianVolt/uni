#include "gamemenu.h"



/**
 * @brief Returns the length of a string.
 * @param str The string to check.
 * @return The length of the string.
 */

u16 string_length(string str)
{
  u16 len = -1;

  while (str[++len]);

  return len;
}



/**
 * @brief Checks if a string includes a character.
 * @param str The string to check in.
 * @param ch The character to search for.
 * @return 1 if the string contains the character, 0 otherwise.
 */

u8 string_includes_char(string str, c8 ch)
{
  u8 res = *str == ch;

  while (*str && !res)
    res |= *++str == ch;

  return res;
}



/**
 * Transforms a string into its uppercase version.
 * @param str The string to transform.
 * @returns The modified string.
 */

string string_uppercase(string str)
{
  u16 i = -1;

  while (str[++i])
    str[i] = CHAR_TO_UPPERCASE(str[i]);

  return str;
}



/**
 * Transforms a string into its lowercase version.
 * @param str The string to transform.
 * @returns The modified string.
 */

string string_lowercase(string str)
{
  u16 i = -1;

  while (str[++i])
    str[i] = CHAR_TO_LOWERCASE(str[i]);

  return str;
}



/**
 * Transforms a string into its shiftcase version.
 * @param str The string to transform.
 * @returns The modified string.
 */

string string_shiftcase(string str)
{
  u16 i = -1;

  while (str[++i])
    str[i] = CHAR_TO_SHIFTCASE(str[i]);

  return str;
}



/**
 * @brief Copies a source string into a destination one.
 * @param dest The string to replace.
 * @param src The string to copy.
 * @return The replaced string.
 */

string string_copy(string dest, string src, u16 dest_size)
{
  u16 len = string_length(src);

  if (len > dest_size)
    len = dest_size;

  if (!len)
    return NULL;

  dest[len] = '\0';

  while (len--)
    dest[len] = src[len];

  return dest;
}



/**
 * @brief Checks if a string includes a substring.
 * @param str The string to check in.
 * @param substr The string to search for.
 * @return 1 if the string contains the substring, 0 otherwise.
 */

u8 string_includes_substring(string str, string substr)
{
  u16 substrlen = string_length(substr);

  if (!substrlen)
    return 1;

  u16 matched = *str == *substr;

  for (u16 i = 1; str[i] && matched < substrlen; ++i)
    matched = str[i] == substr[matched]
      ? matched + 1
      : str[i] == substr[0]
    ;

  return matched == substrlen;
}



/**
 * @brief Checks if a string includes a substring, without caring for casing.
 * @param str The string to check in.
 * @param substr The string to search for.
 * @return 1 if the string contains the substring, 0 otherwise.
 */

u8 string_includes_substring_ignorecase(string str, string substr)
{
  u16 substrlen = string_length(substr);

  if (!substrlen)
    return 1;

  u16 matched = CHAR_TO_LOWERCASE(*str) == CHAR_TO_LOWERCASE(*substr);

  for (u16 i = 1; str[i] && matched < substrlen; ++i)
    matched = CHAR_TO_LOWERCASE(str[i]) == CHAR_TO_LOWERCASE(substr[matched])
      ? matched + 1
      : CHAR_TO_LOWERCASE(str[i]) == CHAR_TO_LOWERCASE(substr[0])
    ;

  return matched == substrlen;
}



/**
 * @brief Checks if two strings are equal.
 * @param str1 The first string to compare.
 * @param str2 The second string to compare.
 * @return 1 if the strings are equal, 0 otherwise.
 */

u8 string_equals(string str1, string str2)
{
  u8 res = 1;
  u16 i = -1;

  while (res && str1[++i])
    res &= str1[i] == str2[i];

  return res && !str2[i];
}



/**
 * @brief Checks if two strings are equal, without caring for casing.
 * @param str1 The first string to compare.
 * @param str2 The second string to compare.
 * @return 1 if the strings are equal, 0 otherwise.
 */

u8 string_equals_ignorecase(string str1, string str2)
{
  u8 res = 1;
  u16 i = -1;

  while (res && str1[++i])
    res &= CHAR_TO_LOWERCASE(str1[i]) == CHAR_TO_LOWERCASE(str2[i]);

  return res && !str2[i];
}



/**
 * @brief Compares two strings lexicographically.
 * @param str1 The string to compare.
 * @param str2 The string to compare with.
 * @return The ASCII difference of the first mismatching character. 
 */

i8 string_compare(string str1, string str2)
{
  u16 i = 0;
  u8 res = *str1 - *str2;

  while (!res && str1[++i])
    res = str1[i] - str2[i];

  return str1[i] - str2[i];
}



/**
 * @brief Compares two strings lexicographically, without care for casing.
 * @param str1 The string to compare.
 * @param str2 The string to compare with.
 * @return The ASCII difference of the first mismatching character. 
 */

i8 string_compare_ignorecase(string str1, string str2)
{
  u16 i = 0;
  u8 res = CHAR_TO_LOWERCASE(*str1) - CHAR_TO_LOWERCASE(*str2);

  while (!res && str1[++i])
    res = CHAR_TO_LOWERCASE(str1[i]) - CHAR_TO_LOWERCASE(str2[i]);

  return CHAR_TO_LOWERCASE(str1[i]) - CHAR_TO_LOWERCASE(str2[i]);
}



/**
 * @brief Prints the menu list and then awaits for numerical input.
 * @param header The menu header.
 * @param items The item list.
 * @param conditions A bitfield to specify (in reverse order) which options to print as "unavailable".
 * @param count The number of menu items.
 * @param offset The starting index number.
 * @param msg The message to print to the user.
 * @param err The custom error message to print to the user.
 * @param fmt The user input format.
 * @param var The variable to assign the numeric input to.
 */

u8 menu(string header, string* items, u80 conditions, u8 count, u8 offset, string msg, string err, string fmt, u8* var)
{
  menu_print(header, items, conditions, count, offset);
  return menu_input_number(msg, err, fmt, var, count, offset);
}



/**
 * @brief Prints the list of items in the menu.
 * @param header The menu header.
 * @param items The item list.
 * @param conditions A bitfield to specify (in reverse order) which options to print as "unavailable".
 * @param count The number of menu items.
 * @param offset The starting index number.
 */

void menu_print(string header, string* items, u80 conditions, u8 count, u8 offset)
{
  console_print_header(header, __ANSI_COLOR_MAGENTA__);
  print(__EOL__);

  for (u8 i = 0; i < count; ++i)
    if (*items[i])
      print(
        flag_is_set(conditions, i)
          ? __ANSI_COLOR_CYAN__ __FMT_U8__ ". " __ANSI_COLOR_YELLOW__ "%s" __EOL__
          : __ANSI_COLOR_RED__ __FMT_U8__ ". %s" __EOL__,
        i + offset,
        items[i]
      );

  print(__EOL__);
}



/**
 * @brief Manages keyboard numeric inputs.
 * @param msg The message to print to the user.
 * @param err The custom error message to print to the user.
 * @param fmt The user input format.
 * @param var The variable to assign the numeric input to.
 * @param count The number of selectable items in the menu.
 * @param offset The minimum value to input.
 * @return 0 if successful, 1 if not.
 */

u8 menu_input_number(string msg, string err, string fmt, u8* var, u8 count, u8 offset)
{
  c8 line[BUF_SAFE BUF_INPUT_NUM_MAXLEN];
  console_print_color(msg, __ANSI_COLOR_CYAN__);

  console_set_color(__ANSI_COLOR_YELLOW__);
  u8 invalid = !menu_input_string(line, BUF_SAFE BUF_INPUT_NUM_MAXLEN) || !scan(line, fmt, var);
  console_reset_color();

  if (invalid)
  {
    console_print_header(__ERR_INVALID_INPUT__, __ANSI_COLOR_RED__);
    return 1;
  }

  if ((invalid = (*var -= offset) >= count))
    console_print_header(err, __ANSI_COLOR_RED__);

  return invalid;
}



/**
 * @brief Manages keyboard string inputs.
 * @param buf The string buffer.
 * @param size The size of the buffer.
 * @return The length of the read and filtered string.
 */

u8 menu_input_string(string buf, u8 size)
{
  if (fgets(buf, size, stdin) && !string_includes_char(buf, '\n'))
    menu_input_buffer_clear();

  u8 len = menu_input_filter_string(buf);

  if (!len)
    console_print_header(__ERR_INVALID_CHARACTERS__, __ANSI_COLOR_RED__);

  return len;
}



/**
 * @brief Gets the length of a sanitized string.
 * @param str The string to sanitize.
 * @return The length of the sanitized string.
 */

u8 menu_input_filter_string(string str)
{
  u8 r = -1, w = 0;

  while (str[++r])
    if (CHAR_IS_ALLOWED(str[r]))
      str[w++] = str[r];

  str[w] = '\0';

  return w;
}



/**
 * @brief Clears the input buffer.
 */

void menu_input_buffer_clear()
{
  c8 c;
  while ((c = getchar()) != '\n' && c != EOF);
}
