#include <stdio.h>



#define ROWS 9
#define COLS 9
#define STATUS_COUNT 3



enum GAME_STATUSES {
  WATER,
  SHIP,
  SHIP_DESTROYED
};



typedef unsigned char u8;
typedef unsigned int u32;
typedef enum GAME_STATUSES GAME_STATUS;



void game_grid_init(u8 grid[ROWS][COLS]);
void game_grid_print(u8 grid[ROWS][COLS]);



int main()
{
  // Dichiara la matrice con le sue dimensioni
  u8 grid[ROWS][COLS];

  // Inizializza la griglia (completamente vuota, ovvero stato "acqua")
  game_grid_init(grid);

  GAME_STATUS ship = SHIP;
  GAME_STATUS ship_destroyed = SHIP_DESTROYED;

  // Assegna degli stati randomicamente
  grid[0][4] = ship;
  grid[1][8] = ship;
  grid[3][7] = ship;
  grid[2][2] = ship_destroyed;
  grid[4][4] = ship_destroyed;
  grid[5][2] = ship_destroyed;

  // Stampa la griglia di gioco
  game_grid_print(grid);

  return 0;
}



void game_grid_init(u8 grid[ROWS][COLS])
{
  GAME_STATUS water = WATER;

  // Itera per tutte le righe
  for (u8 i = 0; i < ROWS; ++i)
    // Itera per tutte le colonne
    for (u8 j = 0; j < COLS; ++j)
      // Imposta lo stato ad "acqua"
      grid[i][j] = water;
}



void game_grid_print(u8 grid[ROWS][COLS])
{
  // Mappa dei caratteri per lo stato
  /*
   * Stato 0 ('O'): "acqua"
   * Stato 1 ('X'): "nave"
   * Stato 2 ('-'): "nave abbattuta"
  */
  char status[STATUS_COUNT] = { 'O', 'X', '-' };

  printf_s("/ ");

  // Stampa la prima riga enumerando le colonne
  for (u8 i = 1; i <= COLS; ++i)
    printf_s("%u ", i);
  
  // Stampa tutte le righe del campo di gioco
  for (u8 i = 0; i < ROWS; ++i)
  {
    // Stampa la lettera della riga
    printf_s("\n%c ", i + 'A');

    // Stampa tutte le celle
    for (u8 j = 0; j < COLS; ++j)
      // Ottiene il carattere dalla mappa sopra (status[]) in base allo stato della cella
      // grid[i][j] può essere 0, 1 o 2 (o qualsiasi altro stato dichiarato)
      printf_s("%c ", status[grid[i][j]]);
  }
}