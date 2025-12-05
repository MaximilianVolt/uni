#include <stdio.h>
#include <math.h>



#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"



typedef int i32;



int main(void)
{
  i32 a, b;
  
  printf_s(ANSI_COLOR_CYAN "Input two values separated by spaces: " ANSI_COLOR_RESET);
  scanf_s("%d %d", &a, &b);
  fflush(stdin);

  printf_s("a + b = %d\n", a + b);
  printf_s("a - b = %d\n", a - b);
  printf_s("a * b = %d\n", a * b);
  printf_s("a / b = %.3f\n", (double) a / b);
  printf_s("a %% b = %d\n\n", a % b);

  printf_s("a^2 = %d\n", a * a);
  printf_s("sqrt(b) = %.3f\n\n", sqrt(b));
}