#include "gamelib.h"



#define __entity_set_stat entity_set_stat

  #define __entity_set_stat_head(stat) [[maybe_unused]] static void __xconcat(entity_set_, stat)(BattleEntity* entity, i16 stat)
  #define __entity_set_stat_body(stat)                                       \
  {                                                                          \
    __entity_set_stat(&entity->stat, stat, entity->PLAYER_STAT_X_MAX(stat)); \
  }

  #define __entity_change_stat_head(stat) [[maybe_unused]] static void __xconcat(entity_change_, stat)(BattleEntity* entity, i16 __xconcat(stat, _diff))
  #define __entity_change_stat_body(stat)                                              \
  {                                                                                    \
    __xconcat(entity_set_, stat)(entity, (i16) entity->stat + __xconcat(stat, _diff)); \
  }

  #define __declare_entity_setter(stat) __entity_set_stat_head(stat); __entity_change_stat_head(stat);
  #define __define_entity_setter(stat) __entity_set_stat_head(stat) __entity_set_stat_body(stat) __entity_change_stat_head(stat) __entity_change_stat_body(stat)

  #define __declare_entity_setters()               \
    __declare_entity_setter(PLAYER_STAT_HP)        \
    __declare_entity_setter(PLAYER_STAT_ATK)       \
    __declare_entity_setter(PLAYER_STAT_DEF)       \
    __declare_entity_setter(PLAYER_STAT_LIVES)     \
    __declare_entity_setter(PLAYER_STAT_ESCAPES)   \
    __declare_entity_setter(PLAYER_STAT_IMMUNITY)  \
    __declare_entity_setter(PLAYER_STAT_ATK_COUNT) \
    __declare_entity_setter(PLAYER_STAT_DEF_COUNT)

  #define __define_entity_setters()               \
    __define_entity_setter(PLAYER_STAT_HP)        \
    __define_entity_setter(PLAYER_STAT_ATK)       \
    __define_entity_setter(PLAYER_STAT_DEF)       \
    __define_entity_setter(PLAYER_STAT_LIVES)     \
    __define_entity_setter(PLAYER_STAT_ESCAPES)   \
    __define_entity_setter(PLAYER_STAT_IMMUNITY)  \
    __define_entity_setter(PLAYER_STAT_ATK_COUNT) \
    __define_entity_setter(PLAYER_STAT_DEF_COUNT)



/// Function declarations



// GAME SETUP (CORE)

static void          game_register_players                 (GameData* data);
static void          game_map_create                       (GameData* data      , Room* last);
static Room*         game_map_add_menu                     (GameData* data      , Room* previous              , Room* next         , Room* last);
static Room*         game_map_generate_random              (GameData* data);
static Room*         game_map_remove                       (GameData* data      , Room** room_list            , Room* room_target  , u8 room_target_id);
static void          game_map_info                         (GameData* data);

// GAME SETUP (UTILS)

static void          game_clear_rooms                      (GameData* data);
static Room*         game_map_add                          (GameData* data      , Room* previous              , Room* next         , Room* last                 , u8 adj_index);
static Room*         game_map_push                         (GameData* data      , Room* room                  , Room* last_room    , u8 adj_index);
static Room*         game_map_push_menu                    (GameData* data      , Room* room                  , Room* last_room);
static void          game_map_pop                          (GameData* data      , Room* last);
static Room*         game_map_search                       (Room* room_list     , u8 search_id);
static void          game_map_info_room_list               (GameData* data);
static Room*         room_create                           (GameData* data      , ROOM_TYPE room_type         , TRAP_TYPE trap_type, TREASURE_TYPE treasure_type);
static Room*         room_create_menu                      (GameData* data);
static Room*         room_create_random                    (GameData* data);
static void          room_info                             (GameData* data      , Room* room);
static void          room_reset_stats                      (Room* room);
static void          room_destroy                          (Room* room);
static Player*       player_create                         (u8 id               , PLAYER_CLASS class);
static void          player_refill_lives                   (Player* player      , u32 options);
static void          player_reset_stats                    (Player* player      , f32 multiplier);
static void          player_info                           (Player* player      , u8 print_image);
static void          player_kill                           (Player* player);

// GAME LOOP (CORE)

static Game*         game_loop                             (GameData* data);
static void          game_player_advance                   (GameData* data      , Game* game                  , u8* turn);
static void          game_player_combat                    (GameData* data      , Game* game                  , u8* turn);
static void          game_player_flee                      (GameData* data      , Game* game                  , u8* turn);
static void          game_player_loot                      (GameData* data      , Game* game                  , u8* turn);
static void          game_player_info                      (GameData* data      , Game* game                  , u8* turn);
static void          game_room_info                        (GameData* data      , Game* game                  , u8* turn);

// GAME LOOP (UTILS)

static BattleEntity* game_entity_create                    (PLAYER_CLASS class);
static void          game_battle                           (GameData* data      , BattleEntity* e1            , BattleEntity* e2);
static void          game_entity_battle_info               (BattleEntity* entity, u8 print_image);
static void          game_room_change                      (Player* player      , Room* target_room);
static void          game_room_print_info                  (Room* room          , Player* player);
static Room*         game_room_search_first_of             (Room* room_start    , u8 (*search_criteria)(Room*));
static Room*         game_room_search_last_of              (Room* room_start    , u8 (*search_criteria)(Room*));
static Room*         game_room_search_nth_of               (Room* room_start    , u8 (*search_criteria)(Room*), u8 n);
static u8            game_reorder_player_list              (Game* game);
static void          game_player_list_swap                 (Player* p1          , Player* p2);


// GAME ACTIONS

static u8            game_room_search_criteria_isolated    (Room* room);
static u8            game_room_search_criteria_linked      (Room* room);
static u8            game_room_search_criteria_split_paths (Room* room);
static void          game_trap_effect_tile                 (Player* player);
static void          game_trap_effect_blades               (Player* player);
static void          game_trap_effect_fall                 (Player* player);
static void          game_trap_effect_pit                  (Player* player);
static void          game_treasure_effect_poison           (Player* player);
static void          game_treasure_effect_heal             (Player* player);
static void          game_treasure_effect_fortitude        (Player* player);
static void          game_treasure_effect_sword            (Player* player);
static void          game_treasure_effect_shield           (Player* player);
static void          __entity_set_stat                     (u8* stat            , i16 val                     , u8 max_v);
                     __declare_entity_setters              ()

// EXAM

static void          exam                                  (GameData* data      , Game* game                  , u8* turn);



/// Function definitions



// GLOBAL SETUP (CORE)












/**
 * @brief
 * @param data
 */
void game_setup(GameData* data)
{
  if (!data->player_count)
    game_register_players(data);

  game_map_create(data, data->room_start);
}



/**
 * @brief
 */
void game_play(GameData* data)
{
  if (!flag_is_set(data->options, GAME_OPTION_READY))
  {
    console_print_header(__ERR_GAME_NOT_SETUP__, __ANSI_COLOR_RED__);
    return;
  }

  u8 opt,
    invalid = 1
  ;

  string options[GAME_OPTION_COUNT + 1] = {
    __OPT_PLAY__,
    __FLAG_GAME_ENHANCED_FIGHTS__,
    __FLAG_GAME_GENIE__
  };

  while (invalid || opt)
  {
    invalid = menu(
      __SELECTION_GAME_OPTION__,
      options,
      data->options >> (GAME_OPTION_SECRET_COUNT - 1) | 1,
      GAME_OPTION_COUNT + 1,
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

    opt += GAME_OPTION_SECRET_COUNT - 1;

    print(
      __EOL__ __ANSI_COLOR_CYAN__ "%s" __EOL__,
      flag_is_set(data->options, opt)
        ? __MSG_OPTION_UNSET__
        : __MSG_OPTION_SET__
    );

    flag_toggle(data->options, opt);
  }

  Player** players = data->players;
  Room *room_start = data->room_start
    , *iterator = room_start
    , *last = iterator
  ;

  for (u8 i = 0; i < data->player_count; ++i)
  {
    Player* player = players[i];
    player->room = player->room_previous = room_start;
    player_refill_lives(player, data->options);
    player_reset_stats(player, 1);
  }

  #define GAME_ENEMY_SPAWN_RATE .25

  for (; iterator; room_reset_stats(last = iterator), iterator = iterator->room_next)
    if (!flag_is_set(iterator->state, ROOM_STATE_SAFE) && chance(GAME_ENEMY_SPAWN_RATE))
      flag_set(iterator->state, ROOM_STATE_ENEMY);

  flag_clear(room_start->state, ROOM_STATE_ENEMY);
  flag_set(last->state, ROOM_STATE_ENEMY);
  flag_set(last->state, ROOM_STATE_BOSS);

  Game* game = game_loop(data);

  if (game->player_count)
  {
    Player* winner = game->players[game->player_index];
    u8 buf_size = BUF_SAFE BUF_PLAYERNAME_MAXLEN;

    print(
      __EOL__ __FMT_L__ __ANSI_COLOR_CYAN__ __MSG_PLAYER_WON__ __FMT_R__ __EOL__,
      winner->battle_entity.name
    );

    data->winner_count = min(2, (f64) data->winner_count + 1, (f64) GAME_LEADERBOARD_SIZE);

    for (u8 i = data->winner_count - 1; i > 0; --i)
      string_copy(data->leaderboard[i], data->leaderboard[i - 1], buf_size);

    string_copy(data->leaderboard[0], winner->battle_entity.name, buf_size);
  }
  else
    console_print_header(__MSG_GAME_NO_WINNERS__, __ANSI_COLOR_RED__);

  for (u8 i = 0; i < data->player_count; ++i)
    player_info(data->players[i], 0);

  game_map_info(data);

  deallocate(game);
}



/**
 * @brief
 */
void game_show_credits(GameData* data)
{
  game_print_image(__GAME_ICON_CREDITS_FILENAME__);
  console_print_color(__EOL__ __MSG_CREDITS_INTRODUCTION__ __EOL__, __ANSI_COLOR_BLUE__);

  if (!data->winner_count)
    return;

  console_print_header(__MSG_LEADERBOARD_INTRO__, __ANSI_COLOR_MAGENTA__);

  for (u8 i = (print(__EOL__), 0); i < data->winner_count; ++i)
    print(
      __ANSI_COLOR_CYAN__ __FMT_U8__ ". " __ANSI_COLOR_YELLOW__ "%s" __EOL__,
      i + 1,
      data->leaderboard[i]
    );
}












// GLOBAL SETUP (UTILS)












/**
 * @brief
 * @return
 */
GameData game_init()
{
  GameData data = {
    .room_start = NULL,
    .player_count = 0,
    .winner_count = 0,
    .room_count = 0,
    .room_id = 0,
    .options = 0
  };

  for (u8 i = 0; i < GAME_PLAYERS_MAX; ++i)
    data.players[i] = NULL;

  srand((u32) time((time_t*) data.seed));

  return data;
}



/**
 * @brief
 * @param data
 */
void game_cleanup(GameData* data)
{
  game_clear_rooms(data);

  while (data->player_count--)
    deallocate(data->players[data->player_count]);

  data->options = 0;
}



/**
 *
 */
void game_easter_egg(GameData* data)
{
  static u32 interaction_count = 0;

  string messages[MENU_EASTER_EGG_COUNT] = {
    EASTER_EGG_MESSAGES_LIST
  };

  u32 idx = interaction_count++;

  if (interaction_count >= MENU_EASTER_EGG_COUNT)
  {
    flag_set(data->options, GAME_OPTION_REVENGEANCE_MODE);
    idx = MENU_EASTER_EGG_COUNT - 1;
  }

  console_set_color(__ANSI_COLOR_BLUE__);
  print(__EOL__);
  print(messages[idx], interaction_count);
  print(__EOL__);
  console_reset_color();
}



/**
 * 
 */
void game_print_image(string filename)
{
  FILE *file = fopen(filename, "r");
  c8 c;

  if (!file)
    return;

  while ((c = fgetc(file)) != EOF)
    print("%c", c);

  print(__EOL__);

  fclose(file);
}












// GAME SETUP (CORE)












/**
 * @brief
 * @param data
 */
static void game_register_players(GameData* data)
{
  console_print_header(__MENU_TEXT_SETUP_CHARACTERS__, __ANSI_COLOR_MAGENTA__);

  u8 invalid = 1;

  while (invalid)
    invalid = menu_input_number(
      __EOL__ __PROMPT_PLAYER_COUNT__,
      __ERR_TOOMANY_PLAYERS__,
      __FMT_U8__,
      &data->player_count,
      GAME_PLAYERS_MAX,
      FROM 1
    )
    || data->player_count++ > GAME_PLAYERS_MAX;

  string player_classes[CLASS_COUNT] = {
    PLAYER_CLASSES_LIST
  };

  Player** players = data->players;

  for (u8 i = 0, class, prince_assigned = 0; i < data->player_count; ++i)
  {
    invalid = 1;

    if (prince_assigned)
      class = CLASS_DOPPELGANGER;
    else if (i == data->player_count - 1)
      class = CLASS_PRINCE;
    else while (invalid)
      invalid = menu(
        __SELECTION_PLAYER_CLASS__,
        player_classes,
        (1 << CLASS_COUNT) - 1,
        CLASS_COUNT,
        FROM 1,
        __PROMPT_PLAYER_CLASS__,
        __ERR_PRINCE_ALREADY_ASSIGNED__,
        __FMT_U8__,
        &class
      );

    prince_assigned |= (PLAYER_CLASS) class == CLASS_PRINCE;
    players[i] = player_create(i, class);

    if (flag_is_set(players[i]->state, PLAYER_STATE_SPECIAL))
      flag_set(data->options, GAME_OPTION_PROCEDURAL_MODE);
  }
}



/**
 * @brief
 * @param
 */
static void game_map_create(GameData* data, Room* last)
{
  print(__CONSOLE_CLEAR__);

  u8 invalid = 1
    , opt = 0
  ;

  string menu_options[MENU_MAP_SIZE] = {
    MENU_MAP_OPTIONS_LIST
  };

  for (u8 interaction_count = 0; invalid || opt; ++interaction_count)
  {
    // Masks in reversed option order
    #define MASK_MAP_MENU_ALWAYS    0b110001
    #define MASK_MAP_MENU_MAX_ROOMS 0b000010
    #define MASK_MAP_MENU_MIN_ROOMS 0b001100

    u8 conditions = MASK_MAP_MENU_ALWAYS
      | (MASK_MAP_MENU_MAX_ROOMS * (data->room_count < GAME_ROOM_COUNT_MAX))
      | (MASK_MAP_MENU_MIN_ROOMS * !!data->room_count)
    ;

    flag_set_cond(
      data->options,
      GAME_OPTION_READY,
      !!data->player_count & (data->room_count >= GAME_MAP_MIN_SIZE)
    );

    if (flag_is_set(data->options, GAME_OPTION_PROCEDURAL_MODE))
      print(__EOL__ __ANSI_COLOR_CYAN__ __MSG_SPECIAL_PLAYER_RECOGNIZED__ __EOL__);

    invalid = menu(
      __SELECTION_MAP_CREATION__,
      menu_options,
      conditions,
      MENU_MAP_SIZE,
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

    switch (opt)
    {
      default:
        if (!interaction_count)
          console_print_header(__ERR_IMPOSSIBLE_CHOICE__, __ANSI_COLOR_RED__);
      break;

      case 1:
      {
        if (data->room_count >= GAME_ROOM_COUNT_MAX)
        {
          console_print_header(__ERR_TOOMANY_ROOMS__, __ANSI_COLOR_RED__);
          break;
        }

        game_map_info_room_list(data);

        if (!data->room_count)
        {
          last = data->room_start = room_create_menu(data);
          break;
        }

        u8 room_id;
        invalid = 1;

        while (invalid)
          invalid = menu_input_number(
            __PROMPT_ROOM_ID__,
            __ERR_INVALID_INPUT__,
            __FMT_U8__,
            &room_id,
            (u8) -1,
            FROM 0
          );

        Room *room = game_map_search(data->room_start, room_id);

        if (!room)
        {
          console_print_header(__ERR_ROOM_NOT_FOUND__, __ANSI_COLOR_RED__);
          break;
        }

        if (room->adjacent_count == GAME_ROOM_DIR)
        {
          console_print_header(__ERR_ROOM_NOT_LINKABLE__, __ANSI_COLOR_RED__);
          break;
        }

        Room* room_new = room_create_menu(data);

        game_map_add_menu(
          data,
          room,
          room_new,
          last
        );

        last = room_new;
      }
      break;

      case 2:
      {
        if (!data->room_count)
        {
          console_print_header(__ERR_EMPTY_MAP__, __ANSI_COLOR_RED__);
          break;
        }

        game_map_info_room_list(data);

        u8 room_id;
        invalid = 1;

        while (invalid)
          invalid = menu_input_number(
            __PROMPT_ROOM_ID__,
            __ERR_INVALID_INPUT__,
            __FMT_U8__,
            &room_id,
            (u8) -1u,
            FROM 0
          );

        last = game_map_remove(
          data,
          &data->room_start,
          NULL,
          room_id
        );
      }
      break;

      case 3:
        game_map_info(data);
      break;

      case 4:
        last = game_map_generate_random(data);
      break;

      case 5:
        last = (game_cleanup(data), NULL);
        game_register_players(data);
      break;
    }
  }

  print(__CONSOLE_CLEAR__);
}



/**
 * @brief 
 * @param data 
 * @param previous 
 * @param next 
 */
static Room* game_map_add_menu(GameData* data, Room* previous, Room* next, Room* last)
{
  if (data->room_count >= GAME_ROOM_COUNT_MAX)
  {
    console_print_header(__ERR_TOOMANY_ROOMS__, __ANSI_COLOR_RED__);
    return last;
  }

  u8 invalid = 1;
  u8 adj_index = 0;
  u80 conditions = 0;
  string room_directions[GAME_ROOM_DIR] = {
    ROOM_DIRECTIONS_LIST
  };

  for (u8 i = 0; i < GAME_ROOM_DIR; ++i)
    conditions |= !previous->adjacent[i] << i;

  while (invalid)
  {
    invalid = menu(
      __SELECTION_ROOM_DIRECTION__,
      room_directions,
      conditions,
      GAME_ROOM_DIR,
      FROM 1,
      __PROMPT_NUMBER__,
      __ERR_INVALID_INPUT__,
      __FMT_U8__,
      &adj_index
    )
    || previous->adjacent[adj_index];

    if (adj_index < GAME_ROOM_DIR && previous->adjacent[adj_index])
      console_print_header(__ERR_ROOM_LINK_UNAVAILABLE__, __ANSI_COLOR_RED__);
  }

  return game_map_add(data, previous, next, last, adj_index);
}



/**
 * @brief 
 * @param data 
 * @return 
 */
static Room* game_map_generate_random(GameData* data)
{
  u8 invalid = 1
    , opt = 0
  ;

  string menu_options[2] = {
    __OPT_ROOM_RAND_OVERWRITE__,
    __OPT_ROOM_RAND_APPEND__
  };

  Room* room = data->room_start;

  if (room)
  {
    #define MENU_ROOM_GEN_ALWAYS         0b01
    #define MENU_ROOM_GEN_REQUIRES_ROOMS 0b10

    u8 conditions = MENU_ROOM_GEN_ALWAYS
      | (MENU_ROOM_GEN_REQUIRES_ROOMS * (data->room_count < GAME_ROOM_COUNT_MAX))
    ;

    while (invalid)
      invalid = menu(
        __SELECTION_ROOM_GEN__,
        menu_options,
        conditions,
        2,
        FROM 1,
        __PROMPT_NUMBER__,
        __ERR_INVALID_INPUT__,
        __FMT_U8__,
        &opt
      );
    
    if (!opt)
      game_clear_rooms(data);
  }

  room = (opt)
    ? game_map_search(room, GAME_ROOM_LAST)
    : (data->room_start = room_create(
        data,
        irandom(ROOM_TYPES_COUNT),
        TRAP_NONE,
        TREASURE_NONE
      ))
  ;

  if (opt && data->room_count >= GAME_ROOM_COUNT_MAX)
  {
    console_print_header(__ERR_TOOMANY_ROOMS__, __ANSI_COLOR_RED__);
    return room;
  }

  for (u8 i = !opt; i < GAME_MAP_MIN_SIZE && data->room_count < GAME_ROOM_COUNT_MAX; ++i, room = room->room_next)
  {
    u8 dir;

    if (room->adjacent_count == GAME_ROOM_DIR)
      return room;
    else do
      dir = irandom(GAME_ROOM_DIR);
    while (room->adjacent[dir]);

    game_map_push(
      data,
      room_create_random(data),
      room,
      dir
    );
  }

  return room;
}



/**
 * @brief 
 * @param data 
 * @param room_list 
 * @param room_target 
 */
static Room* game_map_remove(GameData* data, Room** room_list, Room* room_target, u8 room_target_id)
{
  if (!data->room_count)
  {
    console_print_header(__ERR_EMPTY_MAP__, __ANSI_COLOR_RED__);
    return NULL;
  }

  Room* room_start = *room_list;
  Room* room_current = room_start;
  Room* room_previous = room_start;
  Room* room_previous_previous = room_start;

  if (
    room_start == room_target
    || room_start->id == room_target_id
    || room_target_id == GAME_ROOM_FIRST
  ) {
    data->room_start = room_start = room_start->room_next;
    room_previous_previous = room_start;
    room_previous = room_start;
    goto clear;
  }

  while (
    room_current
    && room_current != room_target
    && room_current->id != room_target_id
  ) {
    room_previous_previous = room_previous;
    room_previous = room_current;
    room_current = room_current->room_next;
  }

  if (room_target_id == GAME_ROOM_LAST)
  {
    room_current = room_previous;
    room_previous = room_previous_previous;
  }

  if (!room_current)
  {
    console_print_header(__ERR_ROOM_NOT_FOUND__, __ANSI_COLOR_RED__);
    return room_previous;
  }

  room_previous->room_next = room_current->room_next;

  clear: room_destroy(room_current);

  return --data->room_count
    ? game_map_search(room_previous_previous, GAME_ROOM_LAST)
    : (data->room_start = NULL)
  ;
}



/**
 * @brief 
 * @param data 
 */
static void game_map_info(GameData* data)
{
  print(__EOL__ __EOL__ __EOL__);

  game_map_info_room_list(data);

  print(
    __EOL__ __ANSI_COLOR_CYAN__ __MSG_GAME_SEED__
    __ANSI_COLOR_YELLOW__ "%lu" __EOL__,
    data->seed
  );

  print(
    __EOL__ __ANSI_COLOR_CYAN__ __MSG_ROOM_COUNT__
    __ANSI_COLOR_YELLOW__ __FMT_U8__ __EOL__,
    data->room_count
  );

  u32 flags = data->options;

  string game_flags[GAME_OPTION_COUNT_TOTAL] = {
    GAME_OPTIONS_LIST
  };

  for (u8 i = (print(__EOL__), 0); flags; flags &= ~(1 << i++))
    if (flag_is_set(flags, i))
      print(
        __ANSI_COLOR_CYAN__ __MSG_GAME_FLAG_ACTIVE__
        __ANSI_COLOR_YELLOW__ "%s" __EOL__,
        game_flags[i]
      );

  print(__EOL__ __EOL__ __EOL__);
}












// GAME SETUP (UTILS)












/**
 * @brief 
 * @param data 
 */
static void game_clear_rooms(GameData* data)
{
  Room* room = data->room_start;

  if (!room)
    return;

  for (Room* next = room->room_next; next; room = next, next = next->room_next)
    deallocate(room);

  data->room_start = NULL;
  data->room_count = 0;
  data->room_id = 0;
}



/**
 * 
 */
static Room* game_map_link(Room* old, Room* new, u8 adj_index)
{
  new->adjacent[DIR_OPPOSITE(adj_index)] = old;
  old->adjacent[adj_index] = new;
  old->adjacent_count++;
  new->adjacent_count++;

  return new;
}



/**
 * @brief 
 * @param data 
 * @param previous 
 * @param next 
 * @param last 
 * @param adj_index 
 * @return 
 */
static Room* game_map_add(GameData* data, Room* previous, Room* next, Room* last, u8 adj_index)
{
  last->room_next = game_map_link(previous, next, adj_index);

  return last;
}



/**
 * @brief 
 * @param data 
 * @param room 
 * @param adj_index 
 */
static Room* game_map_push(GameData* data, Room* room, Room* last_room, u8 adj_index)
{
  return game_map_add(data, last_room, room, last_room, adj_index);
}



/**
 * @brief 
 * @param data 
 * @param room 
 */
[[maybe_unused]]
static Room* game_map_push_menu(GameData* data, Room* room, Room* last_room)
{
  return game_map_add_menu(data, last_room, room, last_room);
}



/**
 * @brief 
 * @param data 
 */
[[maybe_unused]]
static void game_map_pop(GameData* data, Room* last)
{
  game_map_remove(data, &data->room_start, last, GAME_ROOM_LAST);
}



/**
 * @brief
 * @param room_list
 * @param search_id
 * @return
 */
static Room* game_map_search(Room* room_list, u8 search_id)
{
  if (
    !room_list
    || search_id == room_list->id
    || search_id == GAME_ROOM_FIRST
  )
    return room_list;

  Room *iterator = room_list
    , *last = room_list
  ;

  while ((last = iterator, iterator = iterator->room_next))
    if (iterator->id == search_id)
      return iterator;

  return search_id == GAME_ROOM_LAST
    ? last
    : NULL
  ;
}



/**
 * @brief 
 * @param data 
 */
static void game_map_info_room_list(GameData* data)
{
  Room* iterator = data->room_start;

  if (!iterator)
    return;

  room_info(data, iterator);

  while ((iterator = iterator->room_next))
    room_info(data, iterator);

  print(__EOL__);
}



/**
 * @brief 
 * @param data 
 * @param room_type 
 * @param trap_type 
 * @param treasure_type 
 * @return 
 */
static Room* room_create(GameData* data, ROOM_TYPE room_type, TRAP_TYPE trap_type, TREASURE_TYPE treasure_type)
{
  if (data->room_id >= GAME_ROOM_COUNT_MAX)
  {
    console_print_header(__ERR_ROOM_STACK_FULL__, __ANSI_COLOR_RED__);
    return NULL;
  }

  Room* room = (Room*) malloc(sizeof(Room));

  room->visited_by = GAME_PLAYER_ID_NONE;
  room->treasure_type = treasure_type;
  room->trap_type = trap_type;
  room->room_type = room_type;
  room->adjacent_count = 0;
  room->search_count = 0;
  room->room_next = NULL;
  room->visit_count = 0;
  room->state = STATE_NONE;
  room->id = data->room_id++;

  for (u8 i = 0; i < GAME_ROOM_DIR; ++i)
    room->adjacent[i] = NULL;

  ++data->room_count;

  console_print_header(__MSG_ROOM_CREATION_DONE__, __ANSI_COLOR_GREEN__);

  return room;
}



/**
 * @brief
 * @param
 * @return
 */
static Room* room_create_menu(GameData* data)
{
  u8 room_type
    , trap_type
    , treasure_type
    , invalid = 1
  ;

  string room_types[ROOM_TYPES_COUNT] = {
    ROOM_TYPES_LIST
  };

  while (invalid)
    invalid = menu(
      __SELECTION_ROOM_TYPE__,
      room_types,
      MENU_MASK_ALL,
      ROOM_TYPES_COUNT,
      FROM 1,
      __PROMPT_ROOM_TYPE__,
      __ERR_INVALID_INPUT__,
      __FMT_U8__,
      &room_type
    );

  invalid = 1;

  string room_trap_types[TRAP_TYPES_COUNT] = {
    ROOM_TRAP_TYPES_LIST
  };

  while (invalid)
    invalid = menu(
      __SELECTION_ROOM_TRAP_TYPE__,
      room_trap_types,
      MENU_MASK_ALL,
      TRAP_TYPES_COUNT,
      FROM 1,
      __PROMPT_ROOM_TRAP_TYPE__,
      __ERR_INVALID_INPUT__,
      __FMT_U8__,
      &trap_type
    );

  invalid = 1;

  string room_treasure_types[TREASURE_TYPES_COUNT] = {
    ROOM_TREASURE_TYPES_LIST
  };

  while (invalid)
    invalid = menu(
      __SELECTION_ROOM_TREASURE_TYPE__,
      room_treasure_types,
      MENU_MASK_ALL,
      TREASURE_TYPES_COUNT,
      FROM 1,
      __PROMPT_ROOM_TREASURE_TYPE__,
      __ERR_INVALID_INPUT__,
      __FMT_U8__,
      &treasure_type
    );

  return room_create(data, room_type, trap_type, treasure_type);
}



/**
 * 
 */
static Room* room_create_random(GameData* data)
{
  f64 room_trap_chances[TRAP_TYPES_COUNT] = {
    GAME_TRAP_CHANCES_LIST
  };

  f64 room_treasure_chances[TREASURE_TYPES_COUNT] = {
    GAME_TREASURE_CHANCES_LIST
  };

  return room_create(
    data,
    irandom(ROOM_TYPES_COUNT),
    chance_weighted(room_trap_chances, TRAP_TYPES_COUNT),
    chance_weighted(room_treasure_chances, TREASURE_TYPES_COUNT)
  );
}



/**
 * @brief 
 * @param game 
 * @param room 
 */
static void room_info(GameData* data, Room* room)
{
  if (!room)
    return;

  console_set_color(__ANSI_COLOR_MAGENTA__);
  print(__EOL__ __FMT_L__ __MENU_TEXT_ROOM_INFO__ __FMT_R__ __EOL__, room->id);
  console_reset_color();

  string room_types[ROOM_TYPES_COUNT] = {
    ROOM_TYPES_LIST
  };

  print(
    __EOL__ __ANSI_COLOR_CYAN__ __MSG_ROOM_TYPE__
    __ANSI_COLOR_YELLOW__ "%s",
    room_types[room->room_type]
  );

  string room_trap_types[TRAP_TYPES_COUNT] = {
    ROOM_TRAP_TYPES_LIST
  };

  print(
    __EOL__ __ANSI_COLOR_CYAN__ __MSG_ROOM_TRAP_TYPE__
    __ANSI_COLOR_YELLOW__ "%s",
    room_trap_types[room->trap_type]
  );

  string room_treasure_types[TREASURE_TYPES_COUNT] = {
    ROOM_TREASURE_TYPES_LIST
  };

  print(
    __EOL__ __ANSI_COLOR_CYAN__ __MSG_ROOM_TREASURE_TYPE__
    __ANSI_COLOR_YELLOW__ "%s",
    room_treasure_types[room->treasure_type]
  );

   string room_statuses[ROOM_STATE_COUNT - 1] = {
    ROOM_STATES_LIST
  };

  u32 state = room->state;

  // Tired yet? ;3
  for (u8 i = 0; state; state &= ~(1 << i++))
    if (flag_is_set(state, i))
      print(
        __EOL__ __ANSI_COLOR_CYAN__ __MSG_ROOM_STATE__
        __ANSI_COLOR_YELLOW__ "%s",
        room_statuses[i - 1]
      ); 

  print(
    __EOL__ __ANSI_COLOR_CYAN__ __MSG_ROOM_VISIT_COUNT__
    __ANSI_COLOR_YELLOW__ __FMT_U8__,
    room->visit_count
  );

  print(
    __EOL__ __EOL__ __ANSI_COLOR_MAGENTA__ __FMT_L__ __MENU_TEXT_ROOM_INFO_ADJACENT__ ": " __FMT_U8__ __FMT_R__ __EOL__,
    // Oh hey, you found this comment, hooray!
    room->adjacent_count
  );

  string room_directions[GAME_ROOM_DIR] = {
    ROOM_DIRECTION_INDICATORS_LIST
  },
  room_dir_colors[2] = {
    __ANSI_COLOR_GREEN__,
    __ANSI_COLOR_RESET__
  };

  if (!room->adjacent_count)
    console_print_header(__MSG_ROOM_ISOLATED__, __ANSI_COLOR_BLUE__);
  else for (u8 i = (print(__EOL__), 0); i < GAME_ROOM_DIR; ++i)
    if (room->adjacent[i])
      print(
        "%s{%s} "
        __ANSI_COLOR_YELLOW__ __ROOM_FMT__ __FMT_U8__ " (0x" __FMT_PTR__ ")" __EOL__,
        room_dir_colors[!!room->adjacent[i]->visited_by],
        room_directions[i],
        room->adjacent[i]->id,
        room->adjacent[i]
      );

  console_print_header(__MENU_TEXT_ROOM_INFO_VISITS__, __ANSI_COLOR_MAGENTA__);

  u8 visits = room->visited_by;

  if (!visits)
    console_print_header(__MSG_ROOM_UNCLEARED__, __ANSI_COLOR_BLUE__);
  else for (u8 i = (print(__EOL__), 0); visits; visits &= ~(1 << i++))
    if (flag_is_set(visits, i))
      print(
        __ANSI_COLOR_CYAN__ "[" __FMT_U8__ "]"
        __ANSI_COLOR_YELLOW__ " %s" __EOL__,
        i + 1,
        data->players[i]->battle_entity.name
      );

  console_reset_color();
}



/**
 * 
 */
static void room_reset_stats(Room* room)
{
  #define ROOM_STATE_RESETTABLE_MASK 0b1011

  room->state &= ~(ROOM_STATE_RESETTABLE_MASK);
  room->visited_by = GAME_PLAYER_ID_NONE;
  room->search_count = 0;
  room->visit_count = 0;
}



/**
 * @brief
 * @param room
 */
static void room_destroy(Room* room)
{
  if (!room)
    return;

  for (u8 dir = 0; dir < GAME_ROOM_DIR; ++dir)
  {
    Room* room_adj = room->adjacent[dir];

    if (!room_adj)
      continue;

    room_adj->adjacent[DIR_OPPOSITE(dir)] = NULL;
    room_adj->adjacent_count--;
  }

  deallocate(room);
}



/**
 * @brief
 * @param id
 * @param
 * @return
 */
static Player* player_create(u8 id, PLAYER_CLASS class)
{
  Player* player = (Player*) malloc(sizeof(Player));

  player->room_previous = player->room = NULL;
  player->battle_entity.class = class;
  player->id = id;

  u8 strlen = 0;
  c8 username[BUF_SAFE BUF_PLAYERNAME_MAXLEN];

  do
  {
    print(__EOL__ __ANSI_COLOR_CYAN__ __PROMPT_PLAYER_USERNAME__ __ANSI_COLOR_YELLOW__, id + 1);
    strlen = menu_input_string(username, BUF_SAFE BUF_PLAYERNAME_MAXLEN);
  }
  until (strlen);

  console_reset_color();

  string player_icons[PLAYER_ICON_COUNT] = {
    __GAME_ICON_BARTOK_FILENAME__,
    __GAME_ICON_WR_FILENAME__,
    __GAME_ICON_SINGULARITY_FILENAME__,
    __GAME_ICON_DRENNETH_FILENAME__
  };

  player->battle_entity.icon = player_icons[irandom(PLAYER_ICON_COUNT)];
  string_copy(player->battle_entity.name, username, BUF_SAFE BUF_PLAYERNAME_MAXLEN);
  
  if (string_includes_substring_ignorecase(player->battle_entity.name, __GAME_SPECIAL_PLAYER_USERNAME__))
    flag_set(player->state, PLAYER_STATE_SPECIAL);

  player_reset_stats(player, 1);   

  return player;
}



/**
 * 
 */
static void player_refill_lives(Player* player, u32 options)
{
  BattleEntity* entity = &player->battle_entity;
  u8 player_is_special = flag_is_set(player->state, PLAYER_STATE_SPECIAL);

  entity->lives = entity->lives_max = (player_is_special * GAME_SPECIAL_PLAYER_MULTIPLIER + !player_is_special) * (
    flag_is_set(options, GAME_OPTION_GENIE)
      ? GAME_LIVES_GENIE_BASE
      : GAME_LIVES_BASE
  );
}



/**
 * 
 */
static void player_reset_stats(Player* player, f32 multiplier)
{
  u8 hp_class[CLASS_COUNT] = {
    PLAYER_HP_CLASSES_LIST
  }
  , immunity_class[CLASS_COUNT] = {
    PLAYER_IMMUNITY_CLASSES_LIST
  }
  , escapes_class[CLASS_COUNT] = {
    PLAYER_ESCAPES_CLASSES_LIST
  };

  BattleEntity* entity = &player->battle_entity;
  u8 class = entity->class;

  if (flag_is_set(player->state, PLAYER_STATE_SPECIAL))
    multiplier = GAME_SPECIAL_PLAYER_MULTIPLIER;

  // Assignment hell
  entity->atk_count_max = entity->def_count_max = GAME_DIE_COUNT_MAX * multiplier;
  entity->immunity = entity->immunity_max = immunity_class[class] * multiplier;
  entity->escapes = entity->escapes_max = escapes_class[class] * multiplier;
  entity->atk_count = entity->def_count = GAME_DIE_COUNT_BASE * multiplier;
  entity->atk_max = entity->def_max = GAME_DIE_ROLL_MAX * multiplier;
  entity->atk = entity->def = GAME_DIE_ROLL_BASE * multiplier;
  entity->hp = entity->hp_max = hp_class[class] * multiplier;
  player->state &= 1 << PLAYER_STATE_SPECIAL;
}



/**
 * 
*/
static void player_info(Player* player, u8 print_image)
{
  BattleEntity* entity = &player->battle_entity;

  game_entity_battle_info(entity, print_image);

  u8 vhp = entity->hp
    , vmhp = entity->hp_max
    , battle_hp_state_index = (vhp > (vmhp >> 2)) + (vhp > (vmhp >> 1))
  ;

  string battle_hp_state_colors[BATTLE_HP_STATE_COUNT] = {
    __ANSI_COLOR_RED__,
    __ANSI_COLOR_YELLOW__,
    __ANSI_COLOR_CYAN__
  };

  print(
    " " __ANSI_COLOR_CYAN__ __FMT_U8__ __ANSI_COLOR_RESET__ "|" __xstr(PLAYER_STAT_IMMUNITY)
    " " __ANSI_COLOR_CYAN__ __FMT_U8__ __ANSI_COLOR_RESET__ "|" __xstr(PLAYER_STAT_ESCAPES)
    " %s" __FMT_U8__ __ANSI_COLOR_RESET__ "|" __xstr(PLAYER_STAT_LIVES)
    __EOL__,
    entity->immunity,
    entity->escapes,
    battle_hp_state_colors[battle_hp_state_index],
    entity->lives
  );
}



/**
 *
 */
static void player_kill(Player* player)
{
  BattleEntity* entity = &player->battle_entity;

  entity_change_lives(entity, -1);

  if (entity->lives)
    player_reset_stats(player, 1);
}












// GAME LOOP (CORE)












/**
 * 
 */
static Game* game_loop(GameData* data)
{
  print(__CONSOLE_CLEAR__);

  Game* game = malloc(sizeof(Game));

  game->turn = 0;
  game->state = STATE_NONE;
  game->player_count = data->player_count;

  for (u8 i = 0; i < game->player_count; ++i)
    game->players[i] = data->players[i];

  string menu_options[MENU_GAME_SIZE] = {
    MENU_GAME_OPTIONS_LIST
  };

  void (*menu_actions[MENU_GAME_SIZE - 1])(GameData*, Game*, u8*) = {
    game_player_advance,
    game_player_combat,
    game_player_flee,
    game_player_loot,
    game_player_info,
    game_room_info,
    exam
  };

  for (; !flag_is_set(game->state, GAME_STATE_OVER); ++game->turn)
  {
    u8 turn_starting_player = irandom(game->player_count);

    for (u8 turn = 0, opt = 0, invalid = 1; turn < game->player_count && !flag_is_set(game->state, GAME_STATE_OVER); ++turn, invalid = 1)
    {
      game->player_index = (turn_starting_player + turn) % game->player_count;
      Player* current_player = game->players[game->player_index];

      if (!current_player->battle_entity.hp)
      {
        player_kill(current_player);

        if (!current_player->battle_entity.lives)
        {
          flag_set_cond(
            game->state,
            GAME_STATE_OVER,
            !game_reorder_player_list(game)
          );

          print(
            __EOL__ __ANSI_COLOR_RED__ __MSG_PLAYER_DEFEATED__ __EOL__ __EOL__
            __ANSI_COLOR_BLUE__ __MSG_GAME_PLAYERS_REMAINING__ __EOL__,
            current_player->battle_entity.name,
            game->player_count
          );

          --turn;
        }
        else
        {
          if (flag_is_set(data->options, GAME_OPTION_GENIE))
            print(__EOL__ __ANSI_COLOR_CYAN__ __MSG_GAME_PLAYER_GENIE_REVIVED__ __EOL__);

          print(
            __EOL__ __ANSI_COLOR_CYAN__ __MSG_GAME_PLAYER_REVIVED__ __EOL__,
            current_player->battle_entity.name
          );
        }

        continue;
      }

      if (flag_is_set(current_player->state, PLAYER_STATE_RECOVERY))
      {
        flag_clear(current_player->state, PLAYER_STATE_RECOVERY);
        print(
          __EOL__ __ANSI_COLOR_BLUE__ __MSG_PLAYER_IS_RECOVERING__ __EOL__,
          current_player->battle_entity.name
        );
        continue;
      }

      #define FLAG_GAME_MENU_SKIP    0
      #define FLAG_GAME_MENU_ADVANCE 1
      #define FLAG_GAME_MENU_FIGHT   2
      #define FLAG_GAME_MENU_FLEE    3
      #define FLAG_GAME_MENU_LOOT    4
      #define FLAG_GAME_MENU_PEEK    7
      #define MASK_GAME_MENU_ALWAYS  0b01100000

      Room* room = current_player->room;

      u8 room_has_treasure = !flag_is_set(room->state, ROOM_STATE_LOOTED) && room->treasure_type;
      u8 room_has_enemies = flag_is_set(room->state, ROOM_STATE_ENEMY);
      u8 room_is_safe = !room_has_enemies;

      u16 conditions = MASK_GAME_MENU_ALWAYS;

      flag_set_cond(conditions, FLAG_GAME_MENU_SKIP, room_is_safe);
      flag_set_cond(conditions, FLAG_GAME_MENU_ADVANCE, room_is_safe);
      flag_set_cond(conditions, FLAG_GAME_MENU_FIGHT, room_has_enemies);
      flag_set_cond(conditions, FLAG_GAME_MENU_LOOT, room_is_safe && room_has_treasure);
      flag_set_cond(conditions, FLAG_GAME_MENU_FLEE, room_has_enemies && current_player->battle_entity.escapes);
      flag_set_cond(conditions, FLAG_GAME_MENU_PEEK, room_is_safe);

      print(
        __EOL__ __ANSI_COLOR_CYAN__ __MSG_GAME_PLAYER_TURN_START__ __EOL__,
        current_player->battle_entity.name,
        game->player_index + 1
      );

      while (invalid)
        invalid = menu(
          __SELECTION_GAME_ACTION__,
          menu_options,
          conditions,
          MENU_GAME_SIZE,
          FROM 0,
          __PROMPT_NUMBER__,
          __ERR_INVALID_INPUT__,
          __FMT_U8__,
          &opt
        );

      print(__CONSOLE_CLEAR__);

      if (!opt)
      {
        if (flag_is_set(room->state, ROOM_STATE_ENEMY))
        {
          console_print_header(__ERR_GAME_ROOM_UNSAFE__, __ANSI_COLOR_BLUE__);
          --turn;
        }

        continue;
      }

      menu_actions[opt - 1](data, game, &turn);
    }
  }

  print(__CONSOLE_CLEAR__);

  return game;
}



/**
 * 
 */
static void game_player_advance(GameData* data, Game* game, u8* turn)
{
  Player* player = game->players[game->player_index];

  Room *room = player->room
    , *target_room = NULL
  ;

  if (flag_is_set(room->state, ROOM_STATE_ENEMY))
  {
    console_print_header(__ERR_GAME_ROOM_UNSAFE__, __ANSI_COLOR_BLUE__);
    --*turn;
    return;
  }

  f64 secret_room_chances[GAME_CHANCES_ROOM_SEARCH_COUNT] = {
    GAME_SECRET_ROOM_CHANCES_LIST
  };

  u8 dir_index
    , invalid = 1
    , conditions = 0
  ;

  string directions[GAME_ROOM_DIR] = {
    ROOM_DIRECTIONS_LIST
  },
  room_types[ROOM_TYPES_COUNT] = {
    ROOM_TYPES_LIST
  },
  room_directions[GAME_ROOM_DIR] = {
    ROOM_DIRECTION_INDICATORS_LIST
  },
  room_dir_colors[2] = {
    __ANSI_COLOR_GREEN__,
    __ANSI_COLOR_RESET__
  };

  for (u8 i = 0; i < GAME_ROOM_DIR; ++i)
    conditions |= !!room->adjacent[i] << i;

  print(
    __EOL__ __EOL__ __ANSI_COLOR_MAGENTA__ __FMT_L__ __MENU_TEXT_ROOM_INFO_ADJACENT__ ": " __FMT_U8__ __FMT_R__ __EOL__,
    room->adjacent_count
  );

  for (u8 i = (print(__EOL__), 0); i < GAME_ROOM_DIR; ++i)
    if (room->adjacent[i])
      print(
        "%s{%s} " __ANSI_COLOR_YELLOW__ "%s" __EOL__,
        room_dir_colors[flag_is_set(room->adjacent[i]->visited_by, player->id)],
        room_directions[i],
        room_types[room->adjacent[i]->room_type]
      );

  while (invalid)
    invalid = menu(
      __SELECTION_GAME_DIRECTION__,
      directions,
      conditions,
      GAME_ROOM_DIR,
      FROM 1,
      __PROMPT_NUMBER__,
      __ERR_INVALID_INPUT__,
      __FMT_U8__,
      &dir_index
    );

  if (
    !room->adjacent[dir_index]
    && data->room_count < GAME_ROOM_COUNT_MAX
    && room->search_count < GAME_CHANCES_ROOM_SEARCH_COUNT
    && chance(secret_room_chances[room->search_count++])
  ) {
    console_print_header(__MSG_ROOM_INSPECTION_SUCCEEDED__, __ANSI_COLOR_BLUE__);

    target_room = game_room_search_first_of(data->room_start, game_room_search_criteria_isolated)
      ? game_map_link(room, target_room, dir_index)
      : game_map_add(
          data,
          room,
          room_create_random(data),
          game_map_search(room, GAME_ROOM_LAST),
          dir_index
        )
        ->room_next
    ;

    flag_set(target_room->state, ROOM_STATE_SAFE);
    target_room->search_count = GAME_CHANCES_ROOM_SEARCH_COUNT;
    target_room->trap_type = TRAP_NONE;
  }
  else
    target_room = room->adjacent[dir_index];

  if (!target_room)
  {
    console_print_header(__MSG_ROOM_INSPECTION_FAILED__, __ANSI_COLOR_BLUE__);
    --*turn;
    return;
  }

  game_room_change(player, target_room);
}



/**
 * 
 */
static void game_player_combat(GameData* data, Game* game, u8* turn)
{
  Player* player = game->players[game->player_index];
  Room* room = player->room;

  if (!flag_is_set(room->state, ROOM_STATE_ENEMY))
  {
    console_print_header(__MSG_NO_ENEMY_NEARBY__, __ANSI_COLOR_BLUE__);
    --*turn;
    return;
  }

  flag_set(player->state, PLAYER_STATE_COMBAT);

  #define GAME_ENHANCED_MODE_MAX_ENEMY_COUNT 3

  u8 revengeance_mode = flag_is_set(data->options, GAME_OPTION_REVENGEANCE_MODE)
    , enhanced_mode = flag_is_set(data->options, GAME_OPTION_ENHANCED_FIGHTS)
    , requires_boss = flag_is_set(room->state, ROOM_STATE_BOSS)
    , enemy_count = max(
        2,
        (f64) 1,
        (f64) irandom_range_inclusive(
          1,
          GAME_ENHANCED_MODE_MAX_ENEMY_COUNT
        ) * enhanced_mode
      )
  ;

  BattleEntity* enemies[GAME_ENHANCED_MODE_MAX_ENEMY_COUNT];

  // I'm tired of macros
  PLAYER_CLASS enemy_classes[CLASS_ENTITY_BOSS_COUNT] = {
    CLASS_ENTITY_SKELETON,
    CLASS_ENTITY_GUARD
  },
  boss_classes[CLASS_ENTITY_ENEMY_COUNT] = {
    CLASS_ENTITY_JAFFAR,
    CLASS_ENTITY_ARMSTRONG
  };

  f64 enemy_chances[CLASS_ENTITY_ENEMY_COUNT] = {
    GAME_ENEMY_CHANCES_LIST
  };

  c8 enemy_names[GAME_ENHANCED_MODE_MAX_ENEMY_COUNT][BUF_SAFE BUF_PLAYERNAME_MAXLEN];
  u8 str_size = BUF_SAFE BUF_PLAYERNAME_MAXLEN;
  
  for (u8 i = 0, class; i < enemy_count; ++i)
  {
    class = requires_boss
      ? boss_classes[revengeance_mode]
      : enemy_classes[chance_weighted(enemy_chances, CLASS_ENTITY_ENEMY_COUNT)]
    ;

    requires_boss = 0;
    enemies[i] = game_entity_create(class);
    string_copy(enemy_names[i], enemies[i]->name, str_size);
  }

  u8 battle_ongoing = 1
    , invalid = 1
    , target
  ;

  for (u8 battle_turn = 0; battle_ongoing; ++battle_turn, invalid = 1)
  {
    if (!player->battle_entity.hp)
    {
      print(
        __EOL__ __ANSI_COLOR_CYAN__ __MSG_FIGHT_LOST__ __EOL__,
        player->battle_entity.name
      );
      --*turn;
      break;
    }

    u8 conditions = 0;
    battle_ongoing = 0;

    for (u8 i = 0; i < enemy_count; ++i)
    {
      u8 enemy_has_hp = !!enemies[i]->hp;
      conditions |= enemy_has_hp << i;
      battle_ongoing |= enemy_has_hp;
    }

    if (!battle_ongoing)
      break;

    while (invalid)
    {
      console_print_header(__SELECTION_TARGET__, __ANSI_COLOR_MAGENTA__);

      for (u8 i = (print(__EOL__), 0); i < enemy_count; ++i)
        if (flag_is_set(conditions, i))
          print(
            __ANSI_COLOR_CYAN__ __FMT_U8__ ". " __ANSI_COLOR_YELLOW__ "%s" __EOL__,
            i + 1,
            enemy_names[i]
          );
        else
          print(
            __ANSI_COLOR_RED__ __FMT_U8__ ". " "%s" __EOL__,
            i + 1,
            enemy_names[i]
          );

      print(__EOL__);

      invalid = menu_input_number(
        __PROMPT_NUMBER__,
        __ERR_INVALID_INPUT__,
        __FMT_U8__,
        &target,
        enemy_count,
        FROM 1
      )
      || !enemies[target]->hp;

      if (!enemies[target]->hp)
        console_print_header(__ERR_TARGET_INVALID__, __ANSI_COLOR_BLUE__);
    }

    game_battle(data, &player->battle_entity, enemies[target]);

    if (!enemies[target]->hp)
      print(
        __EOL__ __ANSI_COLOR_CYAN__ __MSG_ENEMY_DEFEATED__ __EOL__,
        enemies[target]->name
      );
  }

  flag_clear(player->state, PLAYER_STATE_COMBAT);

  if (!flag_is_set(room->state, ROOM_STATE_BOSS))
    flag_clear(room->state, ROOM_STATE_ENEMY);

  if (player->battle_entity.hp && flag_is_set(room->state, ROOM_STATE_BOSS))
    flag_set(game->state, GAME_STATE_OVER);

  for (u8 i = 0; i < enemy_count; ++i)
    deallocate(enemies[i]);
}



/**
 * 
 */
static void game_player_flee(GameData* data, Game* game, u8* turn)
{
  Player* player = game->players[game->player_index];
  Room* room = player->room;

  if (!flag_is_set(room->state, ROOM_STATE_ENEMY))
  {
    console_print_header(__MSG_NO_ENEMY_NEARBY__, __ANSI_COLOR_BLUE__);
    --*turn;
    return;
  }

  if (!player->battle_entity.escapes)
  {
    console_print_header(__MSG_PLAYER_CANNOT_ESCAPE__, __ANSI_COLOR_BLUE__);
    --*turn;
    return;
  }

  u8 invalid = 1
    , dir_index
    , conditions = 0
  ;

  string directions[GAME_ROOM_DIR] = {
    ROOM_DIRECTIONS_LIST
  };

  for (u8 i = 0; i < GAME_ROOM_DIR; ++i)
    conditions |= !!room->adjacent[i] << i;

  while (invalid)
    invalid = menu(
      __SELECTION_GAME_DIRECTION__,
      directions,
      conditions,
      GAME_ROOM_DIR,
      FROM 1,
      __PROMPT_NUMBER__,
      __ERR_INVALID_INPUT__,
      __FMT_U8__,
      &dir_index
    )
    || !room->adjacent[dir_index];

  game_room_change(player, room->adjacent[dir_index]);
  entity_change_escapes(&player->battle_entity, -1);
  print(
    __EOL__ __ANSI_COLOR_CYAN__ __MSG_PLAYER_RAN_AWAY__ __EOL__,
    player->battle_entity.name
  );
}



/**
 * 
 */
static void game_player_loot(GameData* data, Game* game, u8* turn)
{
  Player* player = game->players[game->player_index];
  Room* room = player->room;

  if (flag_is_set(room->state, ROOM_STATE_ENEMY))
  {
    console_print_header(__ERR_GAME_ROOM_UNSAFE__, __ANSI_COLOR_BLUE__);
    --*turn;
    return;
  }

  if (flag_is_set(room->state, ROOM_STATE_LOOTED))
  {
    console_print_header(__ERR_ROOM_ALREADY_LOOTED__, __ANSI_COLOR_BLUE__);
    --*turn;
    return;
  }

  if (!room->treasure_type)
  {
    console_print_header(__ERR_ROOM_NO_TREASURE__, __ANSI_COLOR_BLUE__);
    --*turn;
    return;
  }

  void (*treasure_effects[TREASURE_TYPES_COUNT - 1])(Player*) = {
    game_treasure_effect_poison,
    game_treasure_effect_heal,
    game_treasure_effect_fortitude,
    game_treasure_effect_sword,
    game_treasure_effect_shield
  };

  treasure_effects[room->treasure_type - 1](player);

  flag_set(room->state, ROOM_STATE_LOOTED);
}



/**
 * 
 */
static void game_player_info(GameData* data, Game* game, u8* turn)
{
  Player* player = game->players[game->player_index];

  player_info(player, 1);

  if (flag_is_set(player->state, PLAYER_STATE_RECOVERY))
    print(
      __EOL__ __ANSI_COLOR_BLUE__ __MSG_PLAYER_IS_RECOVERING__ __EOL__,
      player->battle_entity.name
    );

  --*turn;
}



/**
 * 
 */
static void game_room_info(GameData* data, Game* game, u8* turn)
{
  Player* player = game->players[game->player_index];
  Room* room = player->room;

  print(
    __EOL__ __ANSI_COLOR_MAGENTA__ __FMT_L__ __MSG_ROOM_INFO_INTRO__
    __ANSI_COLOR_YELLOW__ "%s" __ANSI_COLOR_MAGENTA__ __FMT_R__ __EOL__,
    player->battle_entity.name
  );

  game_room_print_info(room, player);

  --*turn;
}












// GAME LOOP (UTILS)













/**
 * 
 */
static BattleEntity* game_entity_create(PLAYER_CLASS class)
{
  BattleEntity* entity = (BattleEntity*) malloc(sizeof(BattleEntity));

  c8 class_names[CLASS_ENTITY_COUNT][BUF_SAFE BUF_PLAYERNAME_MAXLEN] = {
    __OPT_CLASS_ENTITY_SKELETON__,
    __OPT_CLASS_ENTITY_GUARD__,
    __OPT_CLASS_ENTITY_JAFFAR__,
    __OPT_CLASS_ENTITY_ARMSTRONG__
  };

  string class_images[CLASS_ENTITY_COUNT] = {
    __GAME_ICON_SKELETON_FILENAME__,
    __GAME_ICON_GUARD_FILENAME__,
    __GAME_ICON_JAFFAR_FILENAME__,
    __GAME_ICON_SENATOR_FILENAME__
  };

  u8 hp_class[CLASS_ENTITY_COUNT] = {
    1, 2, 3, 8
  }
  , atk_count_class[CLASS_ENTITY_COUNT] = {
    1, 2, 2, 3
  }
  , def_count_class[CLASS_ENTITY_COUNT] = {
    1, 2, 3, 4
  };

  entity->class = class, class -= CLASS_COUNT;
  string_copy(entity->name, class_names[class], BUF_SAFE BUF_PLAYERNAME_MAXLEN);
  entity->atk_count_max = entity->def_count_max = GAME_DIE_COUNT_MAX;
  entity->atk_max = entity->def_max = GAME_DIE_ROLL_MAX;
  entity->atk = entity->def = GAME_DIE_ROLL_BASE;
  entity->hp = entity->hp_max = hp_class[class];
  entity->atk_count = atk_count_class[class];
  entity->def_count = def_count_class[class];
  entity->immunity = entity->immunity_max = 0;
  entity->escapes = entity->escapes_max = 0;
  entity->icon = class_images[class];

  return entity;
}



/**
 * 
 */
static void game_battle(GameData* data, BattleEntity* e1, BattleEntity* e2)
{
  BattleEntity *battlers[2]
    , *attacker
    , *defender
  ;

  i8 dmg = 0;
  u8 is_procedural_mode = flag_is_set(data->options, GAME_OPTION_PROCEDURAL_MODE)
    , roll
  ;

  f64 die_ratio;

  string messages[2][4] = {
    {
      __MSG_ENTITY_ROLLED_DICE__,
      __MSG_ROLL_ATTACKER_WON__,
      __MSG_ROLL_TIE__,
      __MSG_ROLL_DEFENDER_WON__
    }, {
      __MSG_PROC_ENTITY_ROLLED_DICE__,
      __MSG_PROC_ROLL_ATTACKER_WON__,
      __MSG_PROC_ROLL_TIE__,
      __MSG_PROC_ROLL_DEFENDER_WON__
    }
  };

  battlers[0] = e1;
  battlers[1] = e2;

  for (u8 i = 0; i < 2; ++i)
    game_entity_battle_info(battlers[i], 1), print(__EOL__);

  for (u8 battle_turn = 0; e1->hp && e2->hp; ++battle_turn)
  {
    u8 e1_first = irandom(GAME_DIE_ROLL_BASE) > irandom(GAME_DIE_ROLL_BASE);
    battlers[!e1_first] = e1;
    battlers[e1_first] = e2;

    attacker = battlers[BATTLE_ROLE_ATTACKER];
    defender = battlers[BATTLE_ROLE_DEFENDER];

    print(
      __EOL__ __ANSI_COLOR_CYAN__ __MSG_ENTITY_STARTS_FIRST__ __EOL__,
      attacker->name
    );

    for (u8 action = 0; action < 2 && e1->hp && e2->hp; ++action, dmg = 0)
    {
      for (u8 i = 0; i < attacker->atk_count; ++i)
      {
        die_ratio = (f64) (roll = irandom_range_inclusive(1, attacker->atk)) / attacker->atk;
        dmg += (die_ratio > BATTLE_CRIT_1) + (die_ratio > BATTLE_CRIT_2) + ((roll > defender->def) << 2);
        print(
          messages[is_procedural_mode][0],
          attacker->name,
          roll
        );
      }

      for (u8 i = 0; i < defender->def_count; ++i)
      {
        die_ratio = (f64) (roll = irandom_range_inclusive(1, defender->def)) / defender->def;
        dmg -= (die_ratio > BATTLE_CRIT_1) + (die_ratio > BATTLE_CRIT_2) + ((roll > attacker->atk) << 2);
        print(
          messages[is_procedural_mode][0],
          defender->name,
          roll
        );
      }

      i8 damage_dealt = min(2, (f64) -dmg, (f64) 0);
      entity_change_hp(defender, damage_dealt);

      print(
        messages[is_procedural_mode][2 - sign(dmg)],
        attacker->name,
        defender->name
      );

      print(
        __EOL__ __ANSI_COLOR_CYAN__ __MSG_TOTAL_DAMAGE_DEALT__ __EOL__,
        damage_dealt
      );

      BattleEntity* temp = attacker;
      attacker = defender;
      defender = temp;
    }

    print(__EOL__);

    for (u8 i = 0; i < 2; ++i)
      game_entity_battle_info(battlers[i], 0), print(__EOL__);
  }
}



/**
 * 
 */
static void game_entity_battle_info(BattleEntity* entity, u8 print_image)
{
  u8 vhp = entity->hp
    , vmhp = entity->hp_max
    , battle_hp_state_index = (vhp > (vmhp >> 2)) + (vhp > (vmhp >> 1))
  ;

  string class_list[CLASS_ENTITY_COUNT_TOTAL] = {
    ENTITY_CLASSES_COMPLETE_LIST
  },
  battle_hp_state_colors[BATTLE_HP_STATE_COUNT] = {
    __ANSI_COLOR_RED__,
    __ANSI_COLOR_YELLOW__,
    __ANSI_COLOR_CYAN__
  },
  battle_hp_colors_map[2] = {
    battle_hp_state_colors[battle_hp_state_index],
    __ANSI_COLOR_RESET__
  };

  c8 battle_hp_symbols_map[2] = {
    ')', '-'
  };

  vmhp++;

  console_reset_color();

  if (print_image)
    game_print_image(entity->icon);

  print(__EOL__ "[%s] %s", class_list[entity->class], entity->name);

  if (string_includes_substring_ignorecase(entity->name, __GAME_SPECIAL_PLAYER_USERNAME__))
    print(__ANSI_COLOR_YELLOW__ __MSG_PLAYER_ULTIMATE__);

  if (!battle_hp_state_index)
    print(__ANSI_COLOR_RED__ __MSG_HP_DANGER_TEXT__);

  print(__EOL__ __ANSI_COLOR_RESET__ "{%s", battle_hp_colors_map[0]);

  while (vmhp-- && vhp--)
    print("%c", battle_hp_symbols_map[0]);

  console_set_color(battle_hp_colors_map[1]);

  while (vmhp--)
    print("%c", battle_hp_symbols_map[1]);

  print(__ANSI_COLOR_RESET__ "}");

  print(
    " %s" __FMT_U8__ __ANSI_COLOR_RESET__ "/%s" __FMT_U8__ __ANSI_COLOR_RESET__ __xstr(PLAYER_STAT_HP)
    " " __ANSI_COLOR_CYAN__ __FMT_U8__ __ANSI_COLOR_RESET__ __xstr(PLAYER_STAT_ATK)
    " " __ANSI_COLOR_CYAN__ __FMT_U8__ __ANSI_COLOR_RESET__ __xstr(PLAYER_STAT_DEF),
    battle_hp_colors_map[0],
    entity->hp,
    battle_hp_colors_map[0],
    entity->hp_max,
    entity->atk_count,
    entity->def_count
  );
}



/**
 * 
 */
static void game_room_change(Player* player, Room* target_room)
{
  ++player->room_previous->visit_count;

  flag_set(player->room->visited_by, player->id);
  player->room_previous = player->room;
  player->room = target_room;

  if (target_room->treasure_type && !flag_is_set(target_room->state, ROOM_STATE_LOOTED))
    print(__EOL__ __ANSI_COLOR_CYAN__ __MSG_ROOM_HAS_TREASURE__ __EOL__);

  if (flag_is_set(target_room->state, ROOM_STATE_ENEMY))
    print(__EOL__ __ANSI_COLOR_RED__ __MSG_ROOM_HAS_ENEMY__ __EOL__);

  // Avoids trap retriggering
  if (target_room->visited_by)
    return;

  if (target_room->trap_type)
  {
    void (*trap_effects[TRAP_TYPES_COUNT - 1])(Player*) = {
      game_trap_effect_tile,
      game_trap_effect_blades,
      game_trap_effect_fall,
      game_trap_effect_pit
    };

    print(__EOL__ __ANSI_COLOR_RED__ __MSG_TRAP_IN_ROOM__);

    if (player->battle_entity.immunity)
    {
      print(__ANSI_COLOR_CYAN__ __MSG_TRAP_AVOIDED__ __EOL__, player->battle_entity.name);
      entity_change_immunity(&player->battle_entity, -1);
    }
    else
      trap_effects[target_room->trap_type - 1](player);
  }

  flag_set(target_room->visited_by, player->id);
}


/**
 * 
*/
static void game_room_print_info(Room* room, Player* player)
{
  string room_types[ROOM_TYPES_COUNT] = {
    ROOM_TYPES_LIST
  };

  print(
    __EOL__ __ANSI_COLOR_CYAN__ __MSG_ROOM_TYPE__
    __ANSI_COLOR_YELLOW__ "%s",
    room_types[room->room_type]
  );

  if (flag_is_set(room->visited_by, player->id))
    print(__EOL__ __ANSI_COLOR_CYAN__ __MSG_ROOM_VISITED__);

  if (flag_is_set(room->state, ROOM_STATE_LOOTED))
    print(__EOL__ __ANSI_COLOR_CYAN__ __MSG_ROOM_LOOTED__);
  else if (room->treasure_type)
    print(__EOL__ __ANSI_COLOR_CYAN__ __MSG_ROOM_HAS_TREASURE__);

  if (room->search_count == GAME_CHANCES_ROOM_SEARCH_COUNT)
    print(__EOL__ __ANSI_COLOR_CYAN__ __MSG_ROOM_SEARCHED__);

  if (flag_is_set(room->state, ROOM_STATE_ENEMY))
    print(__EOL__ __ANSI_COLOR_RED__ __MSG_ROOM_HAS_ENEMY__);

  print(
    __EOL__ __EOL__ __ANSI_COLOR_MAGENTA__ __FMT_L__ __MENU_TEXT_ROOM_INFO_ADJACENT__ ": " __FMT_U8__ __FMT_R__ __EOL__,
    room->adjacent_count
  );

  string room_directions[GAME_ROOM_DIR] = {
    ROOM_DIRECTION_INDICATORS_LIST
  },
  room_dir_colors[2] = {
    __ANSI_COLOR_GREEN__,
    __ANSI_COLOR_RESET__
  };

  for (u8 i = (print(__EOL__), 0); i < GAME_ROOM_DIR; ++i)
    if (room->adjacent[i])
      print(
        "%s{%s} " __ANSI_COLOR_YELLOW__ "%s" __EOL__,
        room_dir_colors[flag_is_set(room->adjacent[i]->visited_by, player->id)],
        room_directions[i],
        room_types[room->adjacent[i]->room_type]
      );
}



/**
 * 
 */
static Room* game_room_search_first_of(Room* room_start, u8 (*search_criteria)(Room*))
{
  if (room_start)
    while (!search_criteria(room_start) && (room_start = room_start->room_next));

  return room_start;
}



/**
 * 
 */
[[maybe_unused]]
static Room* game_room_search_last_of(Room* room_start, u8 (*search_criteria)(Room*))
{
  Room* match = room_start;

  for (; room_start; room_start = room_start->room_next)
    if (search_criteria(room_start))
      match = room_start;

  return match;
}



/**
 * 
 */
[[maybe_unused]]
static Room* game_room_search_nth_of(Room* room_start, u8 (*search_criteria)(Room*), u8 n)
{
  Room* match = room_start;

  for (; n && room_start; room_start = room_start->room_next)
    if (search_criteria(room_start))
      match = room_start, --n;

  return !n ? match : NULL;
}



/**
 * 
 */
static u8 game_reorder_player_list(Game* game)
{
  Player** players = game->players;

  u8 selected_index = game->player_index
    , count = --game->player_count
  ;

  game_player_list_swap(players[selected_index], players[count]);

  for (u8 i = selected_index; i < count - 1; ++i)
    game_player_list_swap(players[i], players[i + 1]);

  return count;
}



/**
 * 
 */
static void game_player_list_swap(Player* p1, Player* p2)
{
  Player* temp = p1;
  p1 = p2, p2 = temp;
}












// GAME ACTIONS












/**
 * 
 */
static u8 game_room_search_criteria_isolated(Room* room)
{
  return !room->adjacent_count;
}



/**
 * 
 */
[[maybe_unused]]
static u8 game_room_search_criteria_linked(Room* room)
{
  return room->adjacent_count;
}



/**
 * 
 */
[[maybe_unused]]
static u8 game_room_search_criteria_split_paths(Room* room)
{
  return room->adjacent_count > 2u;
}



/**
 * 
 */
static void game_trap_effect_tile(Player* player)
{
  #define TRAP_TYPE_TILE_DECREMENT 1
  #define __MSG_TRAP_TYPE_TILE__   "> %s fell due to a tile. Lost %d%s."

  entity_change_hp(&player->battle_entity, -TRAP_TYPE_TILE_DECREMENT);
  print(
    __EOL__ __ANSI_COLOR_RED__ __MSG_TRAP_TYPE_TILE__ __EOL__,
    player->battle_entity.name,
    TRAP_TYPE_TILE_DECREMENT,
    __xstr(PLAYER_STAT_HP)
  );
}



/**
 * 
 */
static void game_trap_effect_blades(Player* player)
{
  #define TRAP_TYPE_BLADES_DECREMENT 2
  #define __MSG_TRAP_TYPE_BLADES__   "> %s wounded theirself due to hanging blades. Lost %d%s."

  entity_change_hp(&player->battle_entity, -TRAP_TYPE_BLADES_DECREMENT);
  print(
    __EOL__ __ANSI_COLOR_RED__ __MSG_TRAP_TYPE_BLADES__ __EOL__,
    player->battle_entity.name, TRAP_TYPE_BLADES_DECREMENT,
    __xstr(PLAYER_STAT_HP)
  );
}



/**
 * 
 */
static void game_trap_effect_fall(Player* player)
{
  #define TRAP_TYPE_FALL_DECREMENT_MIN 1
  #define TRAP_TYPE_FALL_DECREMENT_MAX 2
  #define __MSG_TRAP_TYPE_FALL__       "> %s fell from a high place. Lost %d%s."

  u8 damage = irandom_range_inclusive(TRAP_TYPE_FALL_DECREMENT_MIN, TRAP_TYPE_FALL_DECREMENT_MAX);
  entity_change_hp(&player->battle_entity, -damage);
  print(
    __EOL__ __ANSI_COLOR_RED__ __MSG_TRAP_TYPE_FALL__ __EOL__,
    player->battle_entity.name,
    damage,
    __xstr(PLAYER_STAT_HP)
  );
}



/**
 * 
 */
static void game_trap_effect_pit(Player* player)
{
  #define TRAP_TYPE_PIT_DECREMENT_MIN 1
  #define TRAP_TYPE_PIT_DECREMENT_MAX 2
  #define __MSG_TRAP_TYPE_PIT__       "> %s fell into a pit, it's going to take a bit to recover... Lost %d%s."

  u8 damage = irandom_range_inclusive(TRAP_TYPE_PIT_DECREMENT_MIN, TRAP_TYPE_PIT_DECREMENT_MAX);
  entity_change_hp(&player->battle_entity, -damage);
  print(
    __EOL__ __ANSI_COLOR_RED__ __MSG_TRAP_TYPE_PIT__ __EOL__,
    player->battle_entity.name,
    damage,
    __xstr(PLAYER_STAT_HP)
  );

  flag_set(player->state, PLAYER_STATE_RECOVERY);
}



/**
 * 
 */
static void game_treasure_effect_poison(Player* player)
{
  #define TREASURE_TYPE_POISON_DECREMENT 1
  #define __MSG_TREASURE_TYPE_POISON__   "> %s spilled poison on theirself. Lost %d%s."

  entity_change_hp(&player->battle_entity, -TREASURE_TYPE_POISON_DECREMENT);
  print(
    __EOL__ __ANSI_COLOR_RED__ __MSG_TREASURE_TYPE_POISON__ __EOL__,
    player->battle_entity.name,
    TREASURE_TYPE_POISON_DECREMENT,
    __xstr(PLAYER_STAT_HP)
  );
}



/**
 * 
 */
static void game_treasure_effect_heal(Player* player)
{
  #define TREASURE_TYPE_HEAL_INCREMENT 1
  #define __MSG_TREASURE_TYPE_HEAL__   "> %s found and used a healing item. Gained %d%s."

  entity_change_hp(&player->battle_entity, TREASURE_TYPE_HEAL_INCREMENT);
  print(
    __EOL__ __ANSI_COLOR_GREEN__ __MSG_TREASURE_TYPE_HEAL__ __EOL__,
    player->battle_entity.name,
    TREASURE_TYPE_HEAL_INCREMENT,
    __xstr(PLAYER_STAT_HP)
  );
}



/**
 * 
 */
static void game_treasure_effect_fortitude(Player* player)
{
  #define TREASURE_TYPE_FORTITUDE_INCREMENT 1
  #define __MSG_TREASURE_TYPE_FORTITUDE__   "> %s has become stronger. Gained %d%s, %s fully recovered."

  player->battle_entity.hp = (player->battle_entity.hp_max += TREASURE_TYPE_FORTITUDE_INCREMENT);
  print(
    __EOL__ __ANSI_COLOR_GREEN__ __MSG_TREASURE_TYPE_FORTITUDE__ __EOL__,
    player->battle_entity.name, TREASURE_TYPE_FORTITUDE_INCREMENT,
    __xstr(PLAYER_STAT_X_MAX(PLAYER_STAT_HP)),
    __xstr(PLAYER_STAT_HP)
  );
}



/**
 * 
 */
static void game_treasure_effect_sword(Player* player)
{
  #define TREASURE_TYPE_SWORD_INCREMENT 1
  #define __MSG_TREASURE_TYPE_SWORD__   "> %s found a sword. Gained %d%s & %d%s."

  entity_change_atk_count(&player->battle_entity, TREASURE_TYPE_SWORD_INCREMENT);
  entity_change_atk(&player->battle_entity, TREASURE_TYPE_SWORD_INCREMENT);
  print(
    __EOL__ __ANSI_COLOR_GREEN__ __MSG_TREASURE_TYPE_SWORD__ __EOL__,
    player->battle_entity.name,
    TREASURE_TYPE_SWORD_INCREMENT,
    __xstr(PLAYER_STAT_ATK_COUNT),
    TREASURE_TYPE_SWORD_INCREMENT,
    __xstr(PLAYER_STAT_ATK)
  );
}



/**
 * 
 */
static void game_treasure_effect_shield(Player* player)
{
  #define TREASURE_TYPE_SHIELD_INCREMENT 1
  #define __MSG_TREASURE_TYPE_SHIELD__   "> %s found a shield. Gained %d%s & %d%s."

  entity_change_def_count(&player->battle_entity, TREASURE_TYPE_SHIELD_INCREMENT);
  entity_change_def(&player->battle_entity, TREASURE_TYPE_SHIELD_INCREMENT);
  print(
    __EOL__ __ANSI_COLOR_GREEN__ __MSG_TREASURE_TYPE_SHIELD__ __EOL__,
    player->battle_entity.name,
    TREASURE_TYPE_SHIELD_INCREMENT,
    __xstr(PLAYER_STAT_DEF_COUNT),
    TREASURE_TYPE_SHIELD_INCREMENT,
    __xstr(PLAYER_STAT_DEF)
  );
}



/**
 * 
 */
static void __entity_set_stat(u8* stat, i16 val, u8 max_v)
{
  *stat = (u8) clamp(val, 0, max_v);
}



/**
 * 
 */
__define_entity_setters()












// EXAM












/**
 * 
 */
static void exam(GameData* data, Game* game, u8* turn)
{
  /*
    Add an extra game menu function which allows to see what's inside an adjacent room
  */

  Player* player = game->players[game->player_index];
  Room* room = player->room;

  if (flag_is_set(room->state, ROOM_STATE_ENEMY))
  {
    console_print_header(__ERR_GAME_ROOM_UNSAFE__, __ANSI_COLOR_BLUE__);
    --*turn;
    return;
  }

  console_print_header(__SELECTION_GAME_ROOM_DIRECTION__, __ANSI_COLOR_MAGENTA__);

  u8 dir_index
    , invalid = 1
    , conditions = 0
  ;

  string directions[GAME_ROOM_DIR] = {
    ROOM_DIRECTIONS_LIST
  },
  room_types[ROOM_TYPES_COUNT] = {
    ROOM_TYPES_LIST
  },
  room_directions[GAME_ROOM_DIR] = {
    ROOM_DIRECTION_INDICATORS_LIST
  },
  room_dir_colors[2] = {
    __ANSI_COLOR_GREEN__,
    __ANSI_COLOR_RESET__
  };

  for (u8 i = 0; i < GAME_ROOM_DIR; ++i)
    conditions |= !!room->adjacent[i] << i;

  print(
    __EOL__ __EOL__ __ANSI_COLOR_MAGENTA__ __FMT_L__ __MENU_TEXT_ROOM_INFO_ADJACENT__ ": " __FMT_U8__ __FMT_R__ __EOL__,
    room->adjacent_count
  );

  for (u8 i = (print(__EOL__), 0); i < GAME_ROOM_DIR; ++i)
    if (room->adjacent[i])
      print(
        "%s{%s} " __ANSI_COLOR_YELLOW__ "%s" __EOL__,
        room_dir_colors[flag_is_set(room->adjacent[i]->visited_by, player->id)],
        room_directions[i],
        room_types[room->adjacent[i]->room_type]
      );

  while (invalid)
  {
    invalid = menu(
      __SELECTION_GAME_DIRECTION__,
      directions,
      conditions,
      GAME_ROOM_DIR,
      FROM 1,
      __PROMPT_NUMBER__,
      __ERR_INVALID_INPUT__,
      __FMT_U8__,
      &dir_index
    )
    || !room->adjacent[dir_index];

    if (!room->adjacent[dir_index])
      console_print_header(__ERR_ROOM_NOT_FOUND__, __ANSI_COLOR_BLUE__);
  }

  console_print_header(__MSG_ROOM_PEEK__, __ANSI_COLOR_BLUE__);

  game_room_print_info(room->adjacent[dir_index], player);

  // It takes more than eyes to C...
}
