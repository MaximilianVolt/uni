#include <stdio.h>
#include <math.h>



#define COEFFICIENT_COUNT 3
#define _a 0
#define _b 1
#define _c 2



typedef double f64;
typedef char i8;
typedef unsigned char u8;



void coefficients_input(f64 coefficients[]);
void equation_get_roots_real(f64 coefficients[]);
void input(const char* msg, const char* format, void* var);



int main()
{
  f64 coefficients[COEFFICIENT_COUNT];

  coefficients_input(coefficients);
  equation_get_roots_real(coefficients);

  return 0;
}



/**
 * @brief Gets the input from the user.
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
    invalid = !scanf_s(format, var);
    fflush(stdin);
  }
}



/**
 * @brief Gets in input all the coefficients for an equation.
 * @param {f64[]} coefficients - The coefficients to input.
 */

void coefficients_input(f64 coefficients[])
{
  i8 coeffs[COEFFICIENT_COUNT] = {'a', 'b', 'c'};

  for (u8 i = 0; i < COEFFICIENT_COUNT; ++i)
  {
    printf_s("\n%c", coeffs[i]);
    input(": ", "%lf", &coefficients[i]);
  }
}



/**
 * @brief Returns all the real roots of the given equation.
 * @param {f64[]} coefficients - The coefficients of the equation.
 */

void equation_get_roots_real(f64 coefficients[])
{
  f64 a = coefficients[_a], b = coefficients[_b], c = coefficients[_c];

  if (!a)
  {
    printf_s(
      b
        ? "\nRoot: x = %.2lf/%.2lf"
        : "\nAll real roots",
      c, b
    );
    return;
  }

  f64 delta = b * b - 4 * a * c;

  if (delta < 0)
  {
    printf_s("\nNo real solutions exist.");
    return;
  }

  if (!delta)
  {
    printf_s(
      "\nRoot with algebraic multiplicity of 2: x1,2 = %.2lf",
      -b / 2 / a
    );
    return;
  }

  f64 sqrt_delta = sqrt(delta);

  printf_s(
    "\nRoots: x1 = %.2lf, x2 = %.2lf",
    (-b - sqrt_delta) / 2 / a,
    (-b + sqrt_delta) / 2 / a
  );
}
