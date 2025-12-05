#include "gamemath.h"



/**
 * @brief Returns the absolute value of a number.
 * @param x The number to get the absolute value of.
 * @returns The absolute value of x.
 */

f64 absv(f64 x)
{
  return x * sign(x);
}



/**
 * @brief Returns the sign of a number.
 * @param x The number to get the sign of.
 * @returns The sign of x. 
 */

i8 sign(f64 x)
{
  return (x > 0) - (x < 0);
}



/**
 * @brief Returns the minimum value of a list of arguments.
 * @param count The argument count.
 * @param ... The arguments.
 * @return The minimum value of the list.
 */

f64 min(u8 count, ...)
{
  va_list ap;

  va_start(ap, count);

  f64 curr = va_arg(ap, f64)
    , min_v = curr
  ;

  for (u8 i = 1; i < count; ++i)
    if ((curr = va_arg(ap, f64)) < min_v)
      min_v = curr;
  
  va_end(ap);

  return min_v;
}



/**
 * @brief Returns the maximum value of a list of arguments.
 * @param count The argument count.
 * @param ... The arguments.
 * @return The maximum value.
 */

f64 max(u8 count, ...)
{
  va_list ap;

  va_start(ap, count);

  f64 curr = va_arg(ap, f64)
    , max_v = curr
  ;

  for (u8 i = 1; i < count; ++i)
    if ((curr = va_arg(ap, f64)) > max_v)
      max_v = curr;
  
  va_end(ap);

  return max_v;
}



/**
 * @brief Clamps a value to a range.
 * @param val The value to clamp.
 * @param min_v The minimum value.
 * @param max_v The maximum value.
 * @return The clamped value.
 */

f64 clamp(f64 val, f64 min_v, f64 max_v)
{
  return min(2, max(2, val, min_v), max_v);
}



/**
 * @brief Generates a random number between 0 and a given maximum.
 * @param max The maximum generated value.
 * @return A random number between 0 and max.
 */

u16 irandom(u16 max)
{
  return rand() % max;
}



/**
 * @brief Generates a random number between 0 and a given maximum included.
 * @param max The maximum generated value.
 * @return A random number between 0 and max.
 */

u16 irandom_inclusive(u16 max)
{
  return rand() % (max + 1);
}



/**
 * @brief Generates a random number between a given minimum and maximum.
 * @param min The minimum generated value.
 * @param max The maximum generated value.
 * @return A random number between min and max.
 */

u16 irandom_range(u16 min, u16 max)
{
  return rand() % (max - min) + min;
}



/**
 * @brief Generates a random number between a given minimum and maximum included.
 * @param min The minimum generated value.
 * @param max The maximum generated value.
 * @return A random number between min and max.
 */

u16 irandom_range_inclusive(u16 min, u16 max)
{
  return rand() % (max - min + 1) + min;
}



/**
 * @brief Sums the elements in the given array.
 * @param arr The array to sum.
 * @param len The element count.
 * @return The sum of the elements in the array.
 */

f64 array_sum(f64* arr, u16 len)
{
  f64 sum = 0;

  while (len--)
    sum += arr[len];

  return sum;
}



/**
 * @brief Returns the index of the element chosen in a random generation.
 * @param items The array of chances to process.
 * @param len The length of the array.
 * @return The index of the chosen element; -1 if the array is empty.
 */

i16 chance_weighted(f64* arr, u16 len)
{
  if (!len)
    return -1;

  f64 n = irandom((i16) array_sum(arr, len));

  for (u8 i = 0; i < len; n -= arr[i++])
    if (n < arr[i])
      return i;

  return len - 1;
}



/**
 * @brief Returns 1 (e * 100)% of the time.
 * @param e The chance of returning 1.
 * @return 1 (e * 100)% of the time.
 */

u8 chance(f64 e)
{
  return rand() % GAME_RAND_MOD < e * GAME_RAND_MOD;
}
