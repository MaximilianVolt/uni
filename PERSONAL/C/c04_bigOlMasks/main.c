#include <stdio.h>



#define FLAG_R 030u
#define FLAG_G 020u
#define FLAG_B 010u
#define FLAG_A 000u

#define MASK_COLOR 0xFFu
#define MASK_R (MASK_COLOR << FLAG_R) 
#define MASK_G (MASK_COLOR << FLAG_G)
#define MASK_B (MASK_COLOR << FLAG_B)
#define MASK_A (MASK_COLOR << FLAG_A)



typedef unsigned int u32;
typedef unsigned char u8;



void color_print_values(u32 color);
u32 color_make_rgba(u8 r, u8 g, u8 b, u8 a);



int main()
{
  u32 color = color_make_rgba(104, 69, 88, 16);
  color_print_values(color);
}



u32 color_make_rgba(u8 r, u8 g, u8 b, u8 a)
{
  return a << FLAG_A
    | r << FLAG_R
    | g << FLAG_G
    | b << FLAG_B
  ;
}



void color_print_values(u32 color)
{
  printf_s(
    "R: %u\nG: %u\nB: %u\nA: %u\n",
    color >> FLAG_R & MASK_COLOR,
    color >> FLAG_G & MASK_COLOR,
    color >> FLAG_B & MASK_COLOR,
    color >> FLAG_A & MASK_COLOR
  );
}