/**
 * Write a C program that calculates the area of any triangle and rectangle,
 * given the base and the height as inputs.
 * 
 * @note
 * Create two separate functions for each formula.
 * 
 * @note
 * Declare a dimension of type 'int' and apply casting.
 */



#include <stdio.h>

float area_calculate_triangle_area(float base, float height);
float area_calculate_rectangle_area(float base, float height);

int main(void)
{
  int base = 4;
  float height = 4.5f;

  float triangle_area = area_calculate_triangle_area((float) base, height);
  float rectangle_area = area_calculate_rectangle_area((float) base, height);

  printf("The area of the triangle is %.2f sq. units.\n", triangle_area);
  printf("The area of the rectangle is %.2f sq. units.\n", rectangle_area);

  return 0;
}



/**
 * Calculates the area of a triangle.
 * @param {float} base The base of the triangle.
 * @param {float} height The height of the triangle.
 * @returns {float}
 */

float area_calculate_triangle_area(float base, float height)
{
  return base * height / 2;
}



/**
 * Calculates the area of a rectangle.
 * @param {float} base The base of the rectangle.
 * @param {float} height The height of the rectangle.
 * @returns {float}
 */

float area_calculate_rectangle_area(float base, float height)
{
  return base * height;
}
