#include <stdio.h>



#define __print__ printf("Exponent: %lld\n", exp)



typedef int i32;
typedef double f64;
typedef long long int i64;



f64 power1(f64 base, i64 exp);
f64 power2(f64 base, i64 exp);
i64 ilog2(i64 x);



i32 main()
{
  f64 base = 0x1.0000000000001p+0;
  i64 exp = (i64) 0x7FFFFFFFFFFFFFll;

  // base = 2;
  // exp = -1;

  f64 r1 = power2(base, exp)
    // , r2 = power2(base, exp)
  ;

  printf(
    "Power algorithm 1: %.32lf\n"
    "Power algorithm 2: %.32lf\n"
    "log2 answer: %lld",
    r1,
    0,
    ilog2(0x7FFFFFFFFFFFFFll)
    //, r2
  );
}



f64 power1(f64 base, i64 exp)
{
  if (!exp)
    return 1;

  if (!base)
    return 0;

  if (exp < 0)
  {
    base = 1 / base;
    exp = -exp;
  }

  if (exp == 1)
    return base;

  f64 res = base;

  while (--exp)
    res *= base, __print__;

  return res;
}



f64 power2(f64 base, i64 exp)
{
  if (!exp)
    return 1;

  if (!base)
    return 0;

  if (exp < 0)
  {
    base = 1 / base;
    exp = -exp;
  }

  if (exp == 1)
    return base;

  f64 result = 1;

  for (; exp; base *= base, exp >>= 1)
    result *= exp & 1
      ? base
      : 1
    , __print__;

  return result;
}



// +100 / 100

i64 log2ceil(i64 x)
{
  i32 e = x > 0;

  while ((x >>= 1) > 0)
    ++e;

  return e;
}