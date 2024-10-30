#include <stdio.h>



typedef unsigned int u32;
typedef unsigned char u8;



void input(const char* msg, const char* format, void* var);
u8 triangle_equal_sides_count(u32 sides[]);
u8 triangle_is_right_angled(u32 sides[]);
u8 triangle_is_valid(u32 sides[]);



int main()
{
  u32 sides[3]; u8 invalid;

  do
  {
    input("\nInsert the size of the first side: ", "%4u", &sides[0]);
    input("\nInsert the size of the second side: ", "%4u", &sides[1]);
    input("\nInsert the size of the third side: ", "%4u", &sides[2]);

    invalid = !triangle_is_valid(sides);

    if (invalid)
      printf_s("\n<-- The sizes you inputted do not make up a valid triangle -->\n");
  }
  while (invalid);

  u8 equal_sides_count = triangle_equal_sides_count(sides);
  u8 is_right_angled = triangle_is_right_angled(sides);

  printf_s("\nThe triangle is ");

  if (equal_sides_count == 3)
  {
    printf_s("equilateral");
  }
  else
  {
    printf_s(equal_sides_count ? "isosceles" : "scalene");
  
    if (is_right_angled)
      printf_s(" and right-angled");
  }

  printf_s(".\n");

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
 * Gets the number of equal side couples (3 = equilateral, 1 = isosceles, 0 = scalene).
 * @param {u32[]} sides - The sides of the triangle.
 * @returns {u8}
 */

u8 triangle_equal_sides_count(u32 sides[])
{
  u8 count = 0;

  for (u8 i = 0; i < 3; i++)
    count += sides[i] == sides[(i + 1) % 3];

  return count;
}



/**
 * Determines whether a triangle is right-angled.
 * @param {u32[]} sides - The sides of the triangle.
 * @returns {u8}
 */

u8 triangle_is_right_angled(u32 sides[])
{
  u8 hyp_i = 0, s1_i = 1, s2_i = 2;

  for (u8 i = 1; i < 3; ++i)
    if (sides[i] > sides[hyp_i])
      hyp_i = i;

  s1_i = (hyp_i + 1) % 3;
  s2_i = (hyp_i + 2) % 3;

  return sides[hyp_i] * sides[hyp_i]
    == sides[s1_i] * sides[s1_i]
    + sides[s2_i] * sides[s2_i]
  ;
}



/**
 * Checks if a triangle is valid.
 * @param {u32[]} sides - The sides of the triangle.
 * @returns {u8}
 */

u8 triangle_is_valid(u32 sides[])
{
  u8 hyp_i = 0, s1_i = 1, s2_i = 2;

  for (u8 i = 1; i < 3; ++i)
    if (sides[i] > sides[hyp_i])
      hyp_i = i;

  s1_i = (hyp_i + 1) % 3;
  s2_i = (hyp_i + 2) % 3;

  return sides[hyp_i] < sides[s1_i] + sides[s2_i];
}
