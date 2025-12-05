/**
 * @desc
 * Write a C program that takes a 4-digit year as input and determines whether 
 * the year is a leap year. The program should also calculate the number of days 
 * in February for that year, considering the different rules that apply for leap years.
 * 
 * @note
 * The rules for leap years are:
 * - The year must be divisible by 4.
 * - If the year is divisible by 100, it is not a leap year, unless...
 * - The year is also divisible by 400, in which case it is a leap year.
 * 
 * @note
 * The program should validate that the input is a 4-digit year.
 */



#include <stdio.h>



#define YEAR_LEAP_YEAR_TEXT(year) "is a leap year"
#define YEAR_NOT_LEAP_YEAR_TEXT(year) "is not a leap year"
#define YEAR_FEBRUARY_DAYS 28



void input(const char* msg, const char* format, void* var);
int year_is_leap_year(int year);



int main(void)
{
  int year;

  input("Insert a valid 4-digit year to check: ", "%4d", &year);

  int is_leap_year = year_is_leap_year(year);
  char * msg = (is_leap_year)
    ? YEAR_LEAP_YEAR_TEXT(year)
    : YEAR_NOT_LEAP_YEAR_TEXT(year)
  ;

  printf_s("%d %s. February %d has %d days.", year, msg, year, YEAR_FEBRUARY_DAYS + is_leap_year);
}



/**
 * Checks if the given year is a leap year.
 * @param {int} year - The year to check.
 * @returns {int}
 */

int year_is_leap_year(int year)
{
  return year % 4 == 0
    && year % 100 != 0
    || year % 400 == 0
  ;
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
    invalid = !scanf_s(format, var);
    fflush(stdin);
  }
}
