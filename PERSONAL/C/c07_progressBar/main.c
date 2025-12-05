#include <stdio.h>



void draw_progress_bar(int val, int max, int step_count, char* msg);



int main()
{
  int time = 3e3
    , steps = 45
    , msg = 0
  ;

  #define MSG_COUNT 8
  #define CURSOR_HIDE "\e[?25l"

  char* messages[MSG_COUNT + 1] = {
    "Initializing...",
    "Preparing assets...",
    "Remembering where I came from...",
    "Importing assets...",
    "Improving quality...",
    "Finalizing assets...",
    "Integrity verification...",
    "Finalizing...",
    "Done!"
  };

  printf("\n");

  for (int i = 0; i <= time; ++i)
  {
    msg = (int) ((double) i / time * MSG_COUNT);
    draw_progress_bar(i, time, steps, messages[msg]);
  }

  printf("\n\n");

  return 0;
}



void draw_progress_bar(int val, int max, int step_count, char* msg)
{
  printf(CURSOR_HIDE "\r[");

  int step = (int) ((double) val / max * step_count);

  for (int v = 0; v < step_count; ++v)
    printf(step > v ? ")" : "_");

  printf("] < %.2f%% > %-30s", (double) val / max * 100, msg);

  for (int c = 0; c < 12; ++c)
    printf(" ");
}