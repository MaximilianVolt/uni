/// Libraries

#ifndef GAMELIB_H

  #define GAMELIB_H

  #include <stdio.h>
  #include <limits.h>
  #include "gamemenu.h"
  #include "gamemath.h"



  /// Game flags



  #define __FLAG_GAME_READY__            "Game ready"
  #define __FLAG_GAME_OVER__             "Game over"
  #define __FLAG_GAME_GENIE__            "Genie mode"
  #define __FLAG_GAME_ENHANCED_FIGHTS__  "Enhanced fights"
  #define __FLAG_GAME_REVENGEANCE_MODE__ "Revengeance mode"
  #define __FLAG_GAME_PROCEDURAL_MODE__  "Procedural mode"



  /// Game macros

  #define PLAYER_MAX_STAT                 _max
  #define PLAYER_COUNT_STAT               _count
  #define PLAYER_STAT_X_MAX(stat)         __xconcat(stat, PLAYER_MAX_STAT)
  #define PLAYER_STAT_X_COUNT(stat)       __xconcat(stat, PLAYER_COUNT_STAT)

  #define PLAYER_STAT_HP                  hp
  #define PLAYER_STAT_ATK                 atk
  #define PLAYER_STAT_DEF                 def
  #define PLAYER_STAT_LIVES               lives
  #define PLAYER_STAT_ESCAPES             escapes
  #define PLAYER_STAT_IMMUNITY            immunity
  #define PLAYER_STAT_ATK_COUNT           PLAYER_STAT_X_COUNT(PLAYER_STAT_ATK)
  #define PLAYER_STAT_DEF_COUNT           PLAYER_STAT_X_COUNT(PLAYER_STAT_DEF)

  #define STATE_NONE                      0
  #define GAME_PLAYER_ID_NONE             0
  #define GAME_SPECIAL_PLAYER_MULTIPLIER  5

  #define GAME_MAP_MIN_SIZE               15
  #define GAME_ROOM_COUNT_MAX             200
  #define GAME_ROOM_FIRST                 251
  #define GAME_ROOM_LAST                  250
  #define GAME_ROOM_DIR                   4
  #define GAME_ROOM_PLAYER_VISITS_MASK    0xF

  #define GAME_PLAYERS_MAX                4
  #define GAME_LEADERBOARD_SIZE           3
  #define GAME_LIVES_BASE                 1
  #define GAME_LIVES_GENIE_BASE           3
  #define GAME_HP_MAX                     16
  #define GAME_DIE_ROLL_MAX               12
  #define GAME_DIE_ROLL_BASE              6
  #define GAME_DIE_COUNT_MAX              8
  #define GAME_DIE_COUNT_BASE             2
  #define GAME_HP_PRINCE_BASE             6
  #define GAME_ESCAPES_PRINCE_MAX         1
  #define GAME_IMMUNITY_PRINCE_MAX        1
  #define GAME_HP_DOPPELGANGER_BASE       5
  #define GAME_ESCAPES_DOPPELGANGER_MAX   2
  #define GAME_IMMUNITY_DOPPELGANGER_MAX  0

  #define BATTLE_ROLE_ATTACKER            0
  #define BATTLE_ROLE_DEFENDER            1
  #define BATTLE_CRIT_1                   .33
  #define BATTLE_CRIT_2                   .75

  #define GAME_CHANCES_TRAP_NONE          65
  #define GAME_CHANCES_TRAP_TILE          10
  #define GAME_CHANCES_TRAP_BLADES        9
  #define GAME_CHANCES_TRAP_FALL          8
  #define GAME_CHANCES_TRAP_PIT           8

  #define GAME_CHANCES_TREASURE_NONE      20
  #define GAME_CHANCES_TREASURE_POISON    20
  #define GAME_CHANCES_TREASURE_HEAL      20
  #define GAME_CHANCES_TREASURE_FORTITUDE 15
  #define GAME_CHANCES_TREASURE_SWORD     15
  #define GAME_CHANCES_TREASURE_SHIELD    10

  #define GAME_CHANCES_ROOM_ATTEMPT_1     .33
  #define GAME_CHANCES_ROOM_ATTEMPT_2     .20
  #define GAME_CHANCES_ROOM_ATTEMPT_3     .15
  #define GAME_CHANCES_ROOM_SEARCH_COUNT  3

  #define GAME_CHANCES_ENEMY_SKELETON     60
  #define GAME_CHANCES_ENEMY_GUARD        40

  #define BATTLE_HP_STATE_COUNT           3



  /// Maths and text



  #define DIR_OPPOSITE(dir)               (((dir) + GAME_ROOM_DIR / 2) % GAME_ROOM_DIR)
  #define __stat(sign, amt, stat)         __xstr(sign) __xstr(amt) __xstr(stat)



  /// Menus and interactions



  #ifndef BUF_SAFE
    #define BUF_SAFE                      1 +
  #endif

  #define BUF_PLAYERNAME_MAXLEN           31

  #define MENU_SIZE                       4
  #define MENU_MAP_SIZE                   6
  #define MENU_GAME_SIZE                  7
  #define MENU_COMBAT_SIZE                7
  #define MENU_EASTER_EGG_COUNT           7
  #define MENU_MASK_ALL                   -1u

  #define __GAME_ICON_PATH__                    "./icons/"
  #define __GAME_ICON_CREDITS_FILENAME__        __GAME_ICON_PATH__ "icon_credits.txt"
  #define __GAME_ICON_BARTOK_FILENAME__         __GAME_ICON_PATH__ "icon1.txt"
  #define __GAME_ICON_WR_FILENAME__             __GAME_ICON_PATH__ "icon2.txt"
  #define __GAME_ICON_SINGULARITY_FILENAME__    __GAME_ICON_PATH__ "icon3.txt"
  #define __GAME_ICON_DRENNETH_FILENAME__       __GAME_ICON_PATH__ "icon4.txt"
  #define __GAME_ICON_GUARD_FILENAME__          __GAME_ICON_PATH__ "icon5.txt"
  #define __GAME_ICON_SKELETON_FILENAME__       __GAME_ICON_PATH__ "icon6.txt"
  #define __GAME_ICON_JAFFAR_FILENAME__         __GAME_ICON_PATH__ "icon7.txt"
  #define __GAME_ICON_SENATOR_FILENAME__        __GAME_ICON_PATH__ "icon8.txt"
  #define __GAME_SPECIAL_PLAYER_USERNAME__      "Santini"

  #define __MENU_TEXT_TITLE__                   "Prince of Inertia - Main menu"
  #define __MENU_TEXT_SETUP_CHARACTERS__        "Character creation menu"
  #define __MENU_TEXT_GOODBYE__                 "^^ - Goodbye!"
  #define __ROOM_FMT__                          "rm_"
  #define __MENU_TEXT_ROOM_INFO__               __ROOM_FMT__ __FMT_U8__ " info"
  #define __MENU_TEXT_ROOM_INFO_ADJACENT__      "Adjacent rooms"
  #define __MENU_TEXT_ROOM_INFO_VISITS__        "Clears"

  #define __SELECTION_PLAYER_CLASS__            "Class selection menu"
  #define __SELECTION_MAP_CREATION__            "Map creation menu"
  #define __SELECTION_ROOM_TYPE__               "Room type selection"
  #define __SELECTION_ROOM_TRAP_TYPE__          "Room trap type selection"
  #define __SELECTION_ROOM_TREASURE_TYPE__      "Room treasure type selection"
  #define __SELECTION_ROOM_DIRECTION__          "Room linking selection"
  #define __SELECTION_ROOM_GEN__                "Room management selection"
  #define __SELECTION_GAME_OPTION__             "Select one or more options to toggle"
  #define __SELECTION_GAME_ACTION__             "Game action selection"
  #define __SELECTION_GAME_DIRECTION__          "Where would you like to go?"
  #define __SELECTION_TARGET__                  "Choose an enemy to attack"
  #define __SELECTION_ROOM_GAME_DIRECTION__     "Room peeking selection"

  #define __OPT__
  #define __OPT_YES__                           "Yes"
  #define __OPT_NO__                            "No"
  #define __OPT_MAYBE__                         "Maybe"
  #define __OPT_QUIT__                          "Quit"
  #define __OPT_SETUP__                         "Setup game"
  #define __OPT_PLAY__                          "Play game"
  #define __OPT_CREDITS__                       "Show credits"
  #define __OPT_EASTER_EGG__                    ""
  #define __OPT_CLASS_PRINCE__                  "Prince"
  #define __OPT_CLASS_DOPPELGANGER__            "Doppelganger"

  #define __OPT_CLASS_ENTITY_SKELETON__         "Skeleton"
  #define __OPT_CLASS_ENTITY_GUARD__            "Guard"
  #define __OPT_CLASS_ENTITY_JAFFAR__           "Magical Grand Vizier Jaffar"
  #define __OPT_CLASS_ENTITY_ARMSTRONG__        "Senator Armstrong"

  #define __OPT_MAP_QUIT__                      "Back to main menu"
  #define __OPT_MAP_CREATE_ROOM__               "Create room"
  #define __OPT_MAP_DELETE_ROOM__               "Delete room"
  #define __OPT_MAP_SHOW_ALL__                  "Print game map"
  #define __OPT_MAP_GENERATE__                  "Generate random game map"
  #define __OPT_MAP_RESET__                     "Reset game"
  #define __OPT_MAP_DIR_RIGHT__                 "Right"
  #define __OPT_MAP_DIR_UP__                    "Up"
  #define __OPT_MAP_DIR_LEFT__                  "Left"
  #define __OPT_MAP_DIR_DOWN__                  "Down"
  #define __OPT_MAP_DIR_RIGHT_INDICATOR__       ">"
  #define __OPT_MAP_DIR_UP_INDICATOR__          "^"
  #define __OPT_MAP_DIR_LEFT_INDICATOR__        "<"
  #define __OPT_MAP_DIR_DOWN_INDICATOR__        "v"

  #define __OPT_ROOM_RAND_OVERWRITE__           "Overwrite"
  #define __OPT_ROOM_RAND_APPEND__              "Append"

  #define __OPT_ROOM_TYPE_CORRIDOR__            "Corridor"
  #define __OPT_ROOM_TYPE_STAIRCASE__           "Staircase"
  #define __OPT_ROOM_TYPE_DINING_ROOM__         "Dining room"
  #define __OPT_ROOM_TYPE_WAREHOUSE__           "Warehouse"
  #define __OPT_ROOM_TYPE_GUARD_POST__          "Guard post"
  #define __OPT_ROOM_TYPE_DUNGEON__             "Dungeon"
  #define __OPT_ROOM_TYPE_ARMORY__              "Armory"
  #define __OPT_ROOM_TYPE_MOSQUE__              "Mosque"
  #define __OPT_ROOM_TYPE_TOWER__               "Tower"
  #define __OPT_ROOM_TYPE_BATHROOM__            "Bathroom"
  #define __OPT_ROOM_TYPE_ROYAL_ROOM__          "Royal room"

  #define __OPT_ROOM_TRAP_TYPE_NONE__           "No trap"
  #define __OPT_ROOM_TRAP_TYPE_TILE__           "Tile"
  #define __OPT_ROOM_TRAP_TYPE_BLADES__         "Blades"
  #define __OPT_ROOM_TRAP_TYPE_FALL__           "Fall"
  #define __OPT_ROOM_TRAP_TYPE_PIT__            "Pit"

  #define __OPT_ROOM_TREASURE_TYPE_NONE__       "No treasure"
  #define __OPT_ROOM_TREASURE_TYPE_POISON__     "Poison"
  #define __OPT_ROOM_TREASURE_TYPE_HEAL__       "Heal"
  #define __OPT_ROOM_TREASURE_TYPE_FORTITUDE__  "Fortitude"
  #define __OPT_ROOM_TREASURE_TYPE_SWORD__      "Sword"
  #define __OPT_ROOM_TREASURE_TYPE_SHIELD__     "Shield"

  #define __OPT_GAME_SKIP_TURN__                "Skip turn"
  #define __OPT_GAME_ADVANCE__                  "Advance rooms"
  #define __OPT_GAME_LOOT__                     "Loot room treasure"
  #define __OPT_GAME_FIGHT__                    "Fight"
  #define __OPT_GAME_FLEE__                     "Flee"
  #define __OPT_GAME_PLAYER_INFO__              "Show player info"
  #define __OPT_GAME_ROOM_INFO__                "Show room info"
  #define __OPT_GAME_ROOM_PEEK_INFO__           "[EXAM] Peek room info"

  #define __PROMPT__
  #define __PROMPT_NUMBER__                     "Select an option: "
  #define __PROMPT_STRING__                     "Type in something: "
  #define __PROMPT_PLAYER_COUNT__               "Insert the number of players: "
  #define __PROMPT_PLAYER_CLASS__               "Choose a character class: "
  #define __PROMPT_PLAYER_USERNAME__            "Player " __FMT_U8__ " - Type in your username (max: " __xstr(BUF_PLAYERNAME_MAXLEN) " chars): "
  #define __PROMPT_ROOM_TYPE__                  "Insert the room type: "
  #define __PROMPT_ROOM_TRAP_TYPE__             "Insert the room trap type: "
  #define __PROMPT_ROOM_TREASURE_TYPE__         "Insert the room treasure type: "
  #define __PROMPT_ROOM_DIRECTION__             "Insert the room location from the previous one: "
  #define __PROMPT_ROOM_ID__                    "Select room by id (" __xstr(GAME_ROOM_FIRST) ": first | " __xstr(GAME_ROOM_LAST) ": last): "

  #define __MSG__
  #define __MSG_SMART_ONE_SEQ_1__               ":O - Uhh what? Oh this is an error message, don't worry!"
  #define __MSG_SMART_ONE_SEQ_2__               ":3 - Didn't you hear? This is an error message, choose a valid option!"
  #define __MSG_SMART_ONE_SEQ_3__               ":| - What are you doing?"
  #define __MSG_SMART_ONE_SEQ_4__               ":( - This is not funny..."
  #define __MSG_SMART_ONE_SEQ_5__               ">:( - You just HAD TO try and be the smart one, didn'tcha?"
  #define __MSG_SMART_ONE_SEQ_6__               ">;) - Well then, let's see how you like this..."
  #define __MSG_SMART_ONE_SEQ_7__               "Pressed [" __xstr(MENU_SIZE) "] %d times: nothing happened."
  #define __MSG_LEADERBOARD_INTRO__             "A huge thanks to all our princes of Inertia!"
  #define __MSG_UNABLE_TO_CHOOSE__              "You should learn to choose for yourself sometimes..."
  #define __MSG_USELESS_PLAY_SESSION__          ">:O - Why even open up the game then???"
  #define __MSG_CREDITS_INTRODUCTION__          "^^ - Ah! A wonderful portrait of Master Maximilian!"
  #define __MSG_SPECIAL_PLAYER_RECOGNIZED__     "Sir yes sir! Procedural mode is active, sir! o7"
  #define __MSG_OPTION_SET__                    "> Option activated!"
  #define __MSG_OPTION_UNSET__                  "> Option removed!"
  #define __MSG_ROOM_CREATION_DONE__            "Room creation successful"
  #define __MSG_ROOM_TYPE__                     "> Room type: "
  #define __MSG_ROOM_STATE__                    "> Room state: "
  #define __MSG_ROOM_TRAP_TYPE__                "> Room trap type: "
  #define __MSG_ROOM_TREASURE_TYPE__            "> Room treasure type: "
  #define __MSG_ROOM_VISIT_COUNT__              "> Room visits: "
  #define __MSG_ROOM_STATE__                    "> Room state: "
  #define __MSG_ROOM_STATE_NONE__               "Undiscovered"
  #define __MSG_ROOM_STATE_VISITED__            "Visited"
  #define __MSG_ROOM_STATE_LOOTED__             "Looted"
  #define __MSG_ROOM_STATE_ENEMY__              "Has enemies"
  #define __MSG_ROOM_STATE_BOSS__               "Has boss"

  #define __MSG_ROOM_COUNT__                    "Map room count: "
  #define __MSG_GAME_SEED__                     "Game seed: "
  #define __MSG_ROOM_ISOLATED__                 "[Isolated room]"
  #define __MSG_ROOM_UNCLEARED__                "[Uncleared room]"
  #define __MSG_GAME_FLAG_ACTIVE__              ">| "

  #define __MSG_PLAYER_IS_RECOVERING__          "%s is recovering..."
  #define __MSG_PLAYER_DEFEATED__               "> Player %s is defeated"
  #define __MSG_HP_DANGER_TEXT__                " - DANGER"
  #define __MSG_PLAYER_ULTIMATE__               " - The ultimate game master"
  #define __MSG_GAME_PLAYERS_REMAINING__        "> Remaining players: " __FMT_U8__
  #define __MSG_GAME_PLAYER_TURN_START__        "> Your turn, %s [" __FMT_U8__ "]!"
  #define __MSG_NO_ENEMY_NEARBY__               "There are no enemies nearby"
  #define __MSG_PLAYER_NOT_IN_COMBAT__          "You are not currently in combat"
  #define __MSG_PLAYER_RAN_AWAY__               "> %s ran away."
  #define __MSG_ROOM_INFO_INTRO__               "Current room info - "
  #define __MSG_ROOM_INSPECTION_FAILED__        "It's just an ordinary room..."
  #define __MSG_ROOM_INSPECTION_SUCCEEDED__     "> Hidden room discovered!"
  #define __MSG_PLAYER_CANNOT_ESCAPE__          "> You can no longer escape"
  #define __MSG_ROOM_VISITED__                  "> Room visited"
  #define __MSG_ROOM_LOOTED__                   "> Room is looted"
  #define __MSG_ROOM_SEARCHED__                 "> Room is searched"
  #define __MSG_ROOM_HAS_ENEMY__                "> Unwanted company is in here..."
  #define __MSG_ROOM_HAS_TREASURE__             "> There' a shiny chest... What's inside?"
  #define __MSG_TRAP_IN_ROOM__                  "> There happened to be a trap in the room..."
  #define __MSG_TRAP_AVOIDED__                  " but %s was lucky enough to avoid it!"
  #define __MSG_ENTITY_STARTS_FIRST__           "> %s starts first!"
  #define __MSG_ENTITY_ROLLED_DICE__            __EOL__ __ANSI_COLOR_CYAN__ "> %s rolled a " __FMT_U8__ "!" __EOL__
  #define __MSG_ROLL_ATTACKER_WON__             __EOL__ __ANSI_COLOR_CYAN__ "> %s hit %s!" __EOL__
  #define __MSG_ROLL_TIE__                      __EOL__ __ANSI_COLOR_CYAN__ "> %s and %s performed their absolute best!" __EOL__
  #define __MSG_ROLL_DEFENDER_WON__             __EOL__ __ANSI_COLOR_CYAN__ "> %s's attacks were perfectly tanked by %s!" __EOL__
  #define __MSG_PROC_ENTITY_ROLLED_DICE__       __EOL__ __ANSI_COLOR_CYAN__ "> %s->RNG == " __FMT_U8__ "!" __EOL__
  #define __MSG_PROC_ROLL_ATTACKER_WON__        __EOL__ __ANSI_COLOR_CYAN__ "> %s decreased %s->hp!" __EOL__
  #define __MSG_PROC_ROLL_TIE__                 __EOL__ __ANSI_COLOR_CYAN__ "> %s->roll == %s->roll (sorta)!" __EOL__
  #define __MSG_PROC_ROLL_DEFENDER_WON__        __EOL__ __ANSI_COLOR_CYAN__ "> %s->atk = 0, %s->hp *= 1!" __EOL__
  #define __MSG_ENEMY_DEFEATED__                "> %s was blown away!"
  #define __MSG_TOTAL_DAMAGE_DEALT__            "> Total damage dealt: %d"
  #define __MSG_FIGHT_LOST__                    "> %s lost the fight."
  #define __MSG_ROOM_PEEK__                     "Peeking at the next room, you see..."

  #define __MSG_GAME_PLAYER_REVIVED__           "> %s came back to life."
  #define __MSG_GAME_PLAYER_GENIE_REVIVED__     "> A genie appears and magically you feel like none of this ever happened." __EOL__                           \
                                                "> The genie smiles and you are back, from where you thought you wouldn't have gotten out alive." __EOL__     \
                                                "> Did someone wish for you to stay alive? You'll never know until you get out of here and find out." __EOL__ \
                                                "> The genie fades away, with the lamp that came with him."

  #define __MSG_GAME_NO_WINNERS__               "All players have been defeated."
  #define __MSG_PLAYER_WON__                    "Jaffar has been defeated! %s won!"

  #define __ERR__
  #define __ERR_TOOMANY_PLAYERS__               "Player count must be 1 - " __xstr(GAME_PLAYERS_MAX)
  #define __ERR_TOOMANY_ROOMS__                 "Room count cannot exceed " __xstr(GAME_ROOM_COUNT_MAX)
  #define __ERR_EMPTY_MAP__                     "Map is empty"
  #define __ERR_PRINCE_ALREADY_ASSIGNED__       "Already assigned " __OPT_CLASS_PRINCE__ " to another player"
  #define __ERR_NO_PRINCE_ASSIGNED__            "No " __OPT_CLASS_PRINCE__ " assigned"
  #define __ERR_GAME_NOT_SETUP__                "Game not set up properly"
  #define __ERR_IMPOSSIBLE_CHOICE__             "H-how???"
  #define __ERR_ROOM_NOT_FOUND__                "Room not found"
  #define __ERR_ROOM_LINK_UNAVAILABLE__         "Room connection already exists"
  #define __ERR_ROOM_NOT_LINKABLE__             "Room cannot be linked further"
  #define __ERR_ROOM_STACK_FULL__               "Room id stack full - reset game to clear"
  #define __ERR_GAME_ROOM_UNSAFE__              "Cannot do that now: room unsafe"
  #define __ERR_ROOM_ALREADY_LOOTED__           "Room is already looted"
  #define __ERR_ROOM_NO_TREASURE__              "There is no treasure here"
  #define __ERR_TARGET_INVALID__                "Defeated enemies cannot be targeted"



  /// Enums



  typedef enum PLAYER_CLASSES {
    CLASS_PRINCE,
    CLASS_DOPPELGANGER,
    CLASS_COUNT,
    CLASS_ENTITY_SKELETON = CLASS_COUNT,
    CLASS_ENTITY_GUARD,
    CLASS_ENTITY_ENEMY_INDEX_END,
    CLASS_ENTITY_JAFFAR = CLASS_ENTITY_ENEMY_INDEX_END,
    CLASS_ENTITY_ARMSTRONG,
    CLASS_ENTITY_COUNT_TOTAL,
    CLASS_ENTITY_COUNT = CLASS_ENTITY_COUNT_TOTAL - CLASS_COUNT,
    CLASS_ENTITY_BOSS_COUNT = CLASS_ENTITY_COUNT - CLASS_ENTITY_ENEMY_INDEX_END + CLASS_COUNT,
    CLASS_ENTITY_ENEMY_COUNT = CLASS_ENTITY_COUNT - CLASS_ENTITY_BOSS_COUNT
  }
  PLAYER_CLASS;

  typedef enum ROOM_TYPES {
    ROOM_CORRIDOR,
    ROOM_STAIRCASE,
    ROOM_DINING_ROOM,
    ROOM_WAREHOUSE,
    ROOM_GUARD_POST,
    ROOM_DUNGEON,
    ROOM_ARMORY,
    ROOM_MOSQUE,
    ROOM_TOWER,
    ROOM_BATHROOM,
    ROOM_ROYAL_ROOM,
    ROOM_TYPES_COUNT
  }
  ROOM_TYPE;

  typedef enum TRAP_TYPES {
    TRAP_NONE,
    TRAP_TILE,
    TRAP_BLADES,
    TRAP_FALL,
    TRAP_PIT,
    TRAP_TYPES_COUNT
  }
  TRAP_TYPE;

  typedef enum TREASURE_TYPES {
    TREASURE_NONE,
    TREASURE_POISON,
    TREASURE_HEAL,
    TREASURE_FORTITUDE,
    TREASURE_SWORD,
    TREASURE_SHIELD,
    TREASURE_TYPES_COUNT
  }
  TREASURE_TYPE;

  typedef enum PLAYER_STATES {
    PLAYER_STATE_NONE,
    PLAYER_STATE_ENEMY_NEARBY,
    PLAYER_STATE_COMBAT,
    PLAYER_STATE_RECOVERY,
    PLAYER_STATE_SPECIAL,
    PLAYER_STATE_COUNT
  }
  PLAYER_STATE;

  typedef enum ROOM_STATES {
    ROOM_STATE_NONE,
    ROOM_STATE_VISITED,
    ROOM_STATE_LOOTED,
    ROOM_STATE_SAFE,
    ROOM_STATE_ENEMY,
    ROOM_STATE_BOSS,
    ROOM_STATE_COUNT
  }
  ROOM_STATE;

  typedef enum GAME_STATES {
    GAME_STATE_OVER,
    GAME_STATE_JAFFAR_DEFEATED,
    GAME_STATE_COUNT
  }
  GAME_STATE;

  typedef enum GAME_OPTIONS {
    GAME_OPTION_READY,
    GAME_OPTION_REVENGEANCE_MODE,
    GAME_OPTION_PROCEDURAL_MODE,
    GAME_OPTION_SECRET_COUNT,
    GAME_OPTION_ENHANCED_FIGHTS = GAME_OPTION_SECRET_COUNT,
    GAME_OPTION_GENIE,
    GAME_OPTION_COUNT_TOTAL,
    GAME_OPTION_COUNT = GAME_OPTION_COUNT_TOTAL - GAME_OPTION_SECRET_COUNT
  }
  GAME_OPTION;

  typedef enum PLAYER_ICON {
    PLAYER_ICON_BARTOK,
    PLAYER_ICON_WR,
    PLAYER_ICON_SINGULARITY,
    PLAYER_ICON_DRENNETH,
    PLAYER_ICON_COUNT
  }
  PLAYER_ICON;

  typedef enum ENEMY_ICONS {
    ENEMY_ICON_GUARD,
    ENEMY_ICON_SKELETON,
    ENEMY_ICON_COUNT
  }
  ENEMY_ICON;

  typedef enum BOSS_ICONS {
    BOSS_ICON_JAFFAR,
    BOSS_ICON_SENATOR,
    BOSS_ICON_COUNT
  }
  BOSS_ICON;



  /// Compound types



  typedef struct Room {
    struct Room* room_next;
    struct Room* adjacent[GAME_ROOM_DIR];
    TREASURE_TYPE treasure_type;
    TRAP_TYPE trap_type;
    ROOM_TYPE room_type;
    u32 state;
    u8 adjacent_count;
    u8 search_count;
    u8 visit_count;
    u8 visited_by;
    u8 id;
  }
  Room;

  typedef struct BattleEntity {
    string icon;
    PLAYER_CLASS class;
    c8 name[BUF_SAFE BUF_PLAYERNAME_MAXLEN];
    u8 PLAYER_STAT_X_MAX(PLAYER_STAT_ATK_COUNT);
    u8 PLAYER_STAT_X_MAX(PLAYER_STAT_DEF_COUNT);
    u8 PLAYER_STAT_X_MAX(PLAYER_STAT_IMMUNITY);
    u8 PLAYER_STAT_X_MAX(PLAYER_STAT_ESCAPES);
    u8 PLAYER_STAT_X_MAX(PLAYER_STAT_LIVES);
    u8 PLAYER_STAT_X_MAX(PLAYER_STAT_ATK);
    u8 PLAYER_STAT_X_MAX(PLAYER_STAT_DEF);
    u8 PLAYER_STAT_X_MAX(PLAYER_STAT_HP);
    u8 PLAYER_STAT_ATK_COUNT;
    u8 PLAYER_STAT_DEF_COUNT;
    u8 PLAYER_STAT_IMMUNITY;
    u8 PLAYER_STAT_ESCAPES;
    u8 PLAYER_STAT_LIVES;
    u8 PLAYER_STAT_ATK;
    u8 PLAYER_STAT_DEF;
    u8 PLAYER_STAT_HP;
  }
  BattleEntity;

  typedef struct Player {
    BattleEntity battle_entity;
    Room* room_previous;
    Room* room;
    u32 state;
    u8 id;
  }
  Player;

  typedef struct GameData {
    Player* players[GAME_PLAYERS_MAX];
    c8 leaderboard[GAME_LEADERBOARD_SIZE][BUF_SAFE BUF_PLAYERNAME_MAXLEN];
    Room* room_start;
    u32 options;
    time_t seed;
    u8 player_count; // I wanna represent negative people so much...
    u8 room_count;
    u8 room_id;
    u8 winner_count;
  }
  GameData;

  typedef struct Game {
    Player* players[GAME_PLAYERS_MAX];
    u16 state;
    u16 turn;
    u8 player_index;
    u8 player_count;
  }
  Game;


  /// Lazyness-induced macros



  #define ROOM_TYPES_LIST          \
    __OPT_ROOM_TYPE_CORRIDOR__,    \
    __OPT_ROOM_TYPE_STAIRCASE__,   \
    __OPT_ROOM_TYPE_DINING_ROOM__, \
    __OPT_ROOM_TYPE_WAREHOUSE__,   \
    __OPT_ROOM_TYPE_GUARD_POST__,  \
    __OPT_ROOM_TYPE_DUNGEON__,     \
    __OPT_ROOM_TYPE_ARMORY__,      \
    __OPT_ROOM_TYPE_MOSQUE__,      \
    __OPT_ROOM_TYPE_TOWER__,       \
    __OPT_ROOM_TYPE_BATHROOM__,    \
    __OPT_ROOM_TYPE_ROYAL_ROOM__

  #define ROOM_TRAP_TYPES_LIST     \
    __OPT_ROOM_TRAP_TYPE_NONE__,   \
    __OPT_ROOM_TRAP_TYPE_TILE__,   \
    __OPT_ROOM_TRAP_TYPE_BLADES__, \
    __OPT_ROOM_TRAP_TYPE_FALL__,   \
    __OPT_ROOM_TRAP_TYPE_PIT__

  #define ROOM_TREASURE_TYPES_LIST        \
    __OPT_ROOM_TREASURE_TYPE_NONE__,      \
    __OPT_ROOM_TREASURE_TYPE_POISON__,    \
    __OPT_ROOM_TREASURE_TYPE_HEAL__,      \
    __OPT_ROOM_TREASURE_TYPE_FORTITUDE__, \
    __OPT_ROOM_TREASURE_TYPE_SWORD__,     \
    __OPT_ROOM_TREASURE_TYPE_SHIELD__

  #define ROOM_STATES_LIST      \
    __MSG_ROOM_STATE_NONE__,    \
    __MSG_ROOM_STATE_VISITED__, \
    __MSG_ROOM_STATE_LOOTED__,  \
    __MSG_ROOM_STATE_ENEMY__,   \
    __MSG_ROOM_STATE_BOSS__

  #define ROOM_DIRECTIONS_LIST \
    __OPT_MAP_DIR_RIGHT__,     \
    __OPT_MAP_DIR_UP__,        \
    __OPT_MAP_DIR_LEFT__,      \
    __OPT_MAP_DIR_DOWN__

  #define ROOM_DIRECTION_INDICATORS_LIST \
    __OPT_MAP_DIR_RIGHT_INDICATOR__,     \
    __OPT_MAP_DIR_UP_INDICATOR__,        \
    __OPT_MAP_DIR_LEFT_INDICATOR__,      \
    __OPT_MAP_DIR_DOWN_INDICATOR__

  #define PLAYER_CLASSES_LIST  \
    __OPT_CLASS_PRINCE__,      \
    __OPT_CLASS_DOPPELGANGER__ \

  #define ENTITY_CLASSES_LIST      \
    __OPT_CLASS_ENTITY_SKELETON__, \
    __OPT_CLASS_ENTITY_GUARD__,    \
    __OPT_CLASS_ENTITY_JAFFAR__,   \
    __OPT_CLASS_ENTITY_ARMSTRONG__

  #define ENTITY_CLASSES_COMPLETE_LIST \
    PLAYER_CLASSES_LIST,               \
    ENTITY_CLASSES_LIST

  #define PLAYER_HP_CLASSES_LIST \
    GAME_HP_PRINCE_BASE,         \
    GAME_HP_DOPPELGANGER_BASE

  #define PLAYER_IMMUNITY_CLASSES_LIST \
    GAME_IMMUNITY_PRINCE_MAX,          \
    GAME_IMMUNITY_DOPPELGANGER_MAX

  #define PLAYER_ESCAPES_CLASSES_LIST \
    GAME_ESCAPES_PRINCE_MAX,          \
    GAME_ESCAPES_DOPPELGANGER_MAX

  #define EASTER_EGG_MESSAGES_LIST \
    __MSG_SMART_ONE_SEQ_1__,       \
    __MSG_SMART_ONE_SEQ_2__,       \
    __MSG_SMART_ONE_SEQ_3__,       \
    __MSG_SMART_ONE_SEQ_4__,       \
    __MSG_SMART_ONE_SEQ_5__,       \
    __MSG_SMART_ONE_SEQ_6__,       \
    __MSG_SMART_ONE_SEQ_7__

  #define MENU_OPTIONS_LIST \
    __OPT_QUIT__,           \
    __OPT_SETUP__,          \
    __OPT_PLAY__,           \
    __OPT_CREDITS__,        \
    __OPT_EASTER_EGG__

  #define MENU_MAP_OPTIONS_LIST \
    __OPT_MAP_QUIT__,           \
    __OPT_MAP_CREATE_ROOM__,    \
    __OPT_MAP_DELETE_ROOM__,    \
    __OPT_MAP_SHOW_ALL__,       \
    __OPT_MAP_GENERATE__,       \
    __OPT_MAP_RESET__

  #define MENU_GAME_OPTIONS_LIST \
    __OPT_GAME_SKIP_TURN__,      \
    __OPT_GAME_ADVANCE__,        \
    __OPT_GAME_FIGHT__,          \
    __OPT_GAME_FLEE__,           \
    __OPT_GAME_LOOT__,           \
    __OPT_GAME_PLAYER_INFO__,    \
    __OPT_GAME_ROOM_INFO__,      \
    __OPT_GAME_ROOM_PEEK_INFO__

  #define GAME_TRAP_CHANCES_LIST \
    GAME_CHANCES_TRAP_NONE,      \
    GAME_CHANCES_TRAP_TILE,      \
    GAME_CHANCES_TRAP_BLADES,    \
    GAME_CHANCES_TRAP_FALL,      \
    GAME_CHANCES_TRAP_PIT

  #define GAME_TREASURE_CHANCES_LIST \
    GAME_CHANCES_TREASURE_NONE,      \
    GAME_CHANCES_TREASURE_POISON,    \
    GAME_CHANCES_TREASURE_HEAL,      \
    GAME_CHANCES_TREASURE_FORTITUDE, \
    GAME_CHANCES_TREASURE_SWORD,     \
    GAME_CHANCES_TREASURE_SHIELD

  #define GAME_ENEMY_CHANCES_LIST \
    GAME_CHANCES_ENEMY_SKELETON,  \
    GAME_CHANCES_ENEMY_GUARD      \

  #define GAME_SECRET_ROOM_CHANCES_LIST \
    GAME_CHANCES_ROOM_ATTEMPT_1,        \
    GAME_CHANCES_ROOM_ATTEMPT_2,        \
    GAME_CHANCES_ROOM_ATTEMPT_3

  #define GAME_OPTIONS_LIST         \
    __FLAG_GAME_READY__,            \
    __FLAG_GAME_REVENGEANCE_MODE__, \
    __FLAG_GAME_PROCEDURAL_MODE__,  \
    __FLAG_GAME_ENHANCED_FIGHTS__,  \
    __FLAG_GAME_GENIE__



  /// Function declarations



  // GLOBAL SETUP (CORE)

  void     game_setup        (GameData* data);
  void     game_play         (GameData* data);
  void     game_show_credits (GameData* data);

  // GLOBAL SETUP (UTILS)

  GameData game_init         ();
  void     game_cleanup      (GameData* data);
  void     game_easter_egg   (GameData* data);
  void     game_print_image  (string filename);

#endif
