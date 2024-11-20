// Pass the parameters:
// ./main.c 3 4 5 Hello World

#include <stdio.h>



int main(int argc, char** argv)
{
  for (int i = 0; i < argc; ++i)
    printf_s("Argument %i: %s\n", i, argv[i]);
}