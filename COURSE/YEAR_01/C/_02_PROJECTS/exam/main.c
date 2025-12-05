#include "gamelib.h"



#warning No warnings found.



i32 main()
{
  print(__CONSOLE_CLEAR__);

  GameData data = game_init();
  u32 interaction_count = 0;
  u8 invalid = 1, opt = 0;

  string menu_options[MENU_SIZE + 1] = {
    MENU_OPTIONS_LIST
  };

  void (*menu_actions[MENU_SIZE])(GameData*) = {
    game_setup,
    game_play,
    game_show_credits,
    game_easter_egg
  };

  for (; invalid || opt; ++interaction_count)
  {
    #define MASK_MENU_ALWAYS         0b01011
    #define MASK_MENU_REQUIRES_SETUP 0b00100

    u8 conditions = MASK_MENU_ALWAYS
      | (MASK_MENU_REQUIRES_SETUP * flag_is_set(data.options, GAME_OPTION_READY))
    ;

    invalid = menu(
      __MENU_TEXT_TITLE__,
      menu_options,
      conditions,
      MENU_SIZE + 1,
      FROM 0,
      __PROMPT_NUMBER__,
      __ERR_INVALID_INPUT__,
      __FMT_U8__,
      &opt
    );

    if (invalid)
      continue;

    if (!opt)
      break;

    print(__CONSOLE_CLEAR__);

    menu_actions[opt - 1](&data);
  }

  game_cleanup(&data);

  if (interaction_count)
    console_print_header(__MENU_TEXT_GOODBYE__, __ANSI_COLOR_GREEN__);
  else
    console_print_header(__MSG_USELESS_PLAY_SESSION__, __ANSI_COLOR_BLUE__);

  print(__EOL__);

  return 0;
}
