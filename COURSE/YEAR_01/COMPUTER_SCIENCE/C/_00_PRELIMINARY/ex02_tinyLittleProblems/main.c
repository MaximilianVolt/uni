/**
 * @desc
 * Write a C program with functions that transform a string to its uppercase,
 * lowercase and case-shifted version.
 */



#include <stdio.h>



#define LENGTH 32
#define CHAR_IS_UPPERCASE(c) (c - 'A' < 0x19u)
#define CHAR_IS_LOWERCASE(c) (c - 'a' < 0x19u)



char * string_uppercase(char string[]);
char * string_lowercase(char string[]);
char * string_shiftcase(char string[]);



int main(void)
{
  char string[LENGTH] = "I'm @ C[]nvertible String!";

  printf_s("Shiftcase: \"%s\"\n", string_shiftcase(string));
  printf_s("Uppercase: \"%s\"\n", string_uppercase(string));
  printf_s("Lowercase: \"%s\"\n", string_lowercase(string));

  return 0;
}



/**
 * Transforms a string into its uppercase version.
 * @param {char[]} string The string to transform.
 * @returns {char *}
 */

char * string_uppercase(char string[])
{
  int i = -1;

  while (string[++i] != '\0')
  {
    string[i] -= CHAR_IS_LOWERCASE(string[i]) << 5;
  }

  return string;
}



/**
 * Transforms a string into its lower version.
 * @param {char[]} string The string to transform.
 * @returns {char *}
 */

char * string_lowercase(char string[])
{
  int i = -1;

  while (string[++i] != '\0')
  {
    string[i] += CHAR_IS_UPPERCASE(string[i]) << 5;
  }

  return string;
}



/**
 * Transforms a string into its shift-case version.
 * @param {char[]} string The string to transform.
 * @returns {char *}
 */

char * string_shiftcase(char string[])
{
  int i = -1;

  while (string[++i] != '\0')
  {
    char * c = &string[i];
    *c += (CHAR_IS_UPPERCASE(*c) - CHAR_IS_LOWERCASE(*c)) << 5;

    /*
     * Man, coding in C's so fun, how did I not realize it sooner
     * Let me tell ya, if you do this:
     * 
     * if (*c >= 'A' && *c <= 'Z')
     *   *c += 32;
     * else if (*c >= 'a' && *c <= 'z')
     *   *c -= 32;
     * 
     * YOU SUCK! HAHA!
    */
  }

  return string;
}
