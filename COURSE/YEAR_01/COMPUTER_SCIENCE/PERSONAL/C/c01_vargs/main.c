#include <stdio.h>
#include <stdarg.h>

double average(int argc, ...)
{
  va_list arglist;
  double sum = 0.0;

  va_start(arglist, argc);

  for (int i = 0; i < argc; ++i)
    sum += va_arg(arglist, double);

  va_end(arglist);

  return sum / argc;
}

int main()
{
  printf_s("Avrg: %lf\n", average((4), (double) 1, 3.0, 5.0, 7.0));
}
