#include <stdio.h>



int main()
{
  // Max thing doable is just declaration :(
  int sum(int a, int b);

  printf("Sum: %d\n", sum(3, 4));
}



int sum(int a, int b)
{
  return a + b;
}
