#include <stdio.h>



#define LEN 5



typedef unsigned int u32;
typedef unsigned char u8;



void swap(u32 *a, u32 *b);
void marks_get(u32 marks[]);
void marks_sort(u32 marks[]);
void marks_print(u32 marks[]);
void input(const char* msg, const char* format, void* var);



int main()
{
  u32 marks[LEN];

  marks_get(marks);

  printf_s("> Inserted marks: \n");
  marks_print(marks);

  marks_sort(marks);
  printf_s("\n\n> Sorted marks: \n");
  marks_print(marks);

  return 0;
}



/**
 * Gets the input from the user.
 * @param {const char*} msg - The message to print to the screen.
 * @param {const char*} format - The format for the assignment.
 * @param {void*} var - The variable to modify.
 */

void input(const char* msg, const char* format, void* var)
{
  int invalid = 1;

  while (invalid)
  {
    printf_s(msg);
    invalid = !scanf_s(format, var) || !var;
    fflush(stdin);
  }
}



/**
 * Assigns all the marks to the array.
 * @param {u32[]} marks - The array of marks to input.
 */

void marks_get(u32 marks[])
{
  for (u8 i = 0; i < LEN; ++i)
    input("\nInsert a mark: ", "%2u", &marks[i]);
}



/**
 * Sorts the marks in ascending order.
 * @param {u32[]} marks - The marks to sort.
 */

void marks_sort(u32 marks[])
{
  u8 posmin;

  for (u8 i = 0; i < LEN; ++i)
  {
    posmin = i;

    for (u8 j = i + 1; j < LEN; ++j)
      if (marks[j] < marks[posmin])
        posmin = j;
    
    if (posmin != i)
      swap(&marks[i], &marks[posmin]);
  }
}



/**
 * Prints all the marks.
 * @param {u32[]} marks - The marks to print.
 */

void marks_print(u32 marks[])
{
  for (u8 i = 0; i < LEN; i++)
    printf_s("\nMark n.%u: %u", i + 1, marks[i]);
}




/**
 * Swaps two values.
 * @param {u32} a - The first value.
 * @param {u32} b - The second value.
 */

void swap(u32 *a, u32 *b)
{
  *b += *a;
  *a = *b - *a;
  *b -= *a;
}