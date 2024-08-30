/**
 * @desc
 * Write a C program that reads a text file and counts the number of words, 
 * characters, and lines in the file. The program should also identify the 
 * longest word in the file.
 * 
 * @note
 * The program should prompt the user to enter the filename to be processed.
 * 
 * @note
 * Use standard file I/O functions like `fopen`, `fgetc`, `fgets`, etc.
 * 
 * @note
 * Handle any potential errors (e.g., file not found) gracefully, by displaying 
 * appropriate error messages.
 * 
 * @note
 * Ensure that the program can handle files with varying formats and delimiters 
 * (spaces, tabs, newlines).
 */



/*
|---------------------------------------------------------------------
| CONTEXT
|---------------------------------------------------------------------
|
| I haven't programmed in C for two years and I'm surprised I managed
| to get this far. If I complete this exercise which, btw, thx ChatGPT
| for generating these generous assignments :), I'd say I'd B-rank the
| C language.
|
*/



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>



// I found this cool stuff as well
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"



#define MENU_SIZE 3
#define FILEREADER_FILENAME_MAXLEN 64
#define CHAR_IS_LETTER(c) ((c - 'A' < 0x19u) || (c - 'a' < 0x19u))
#define CHAR_IS_DIGIT(c) (c - '0' < 0xAu)
#define __string_reallocate(string, size) string = realloc(string, size); if (string == NULL) { perror(ANSI_COLOR_RED "Error while reading file" ANSI_COLOR_RESET); break; }



//extern int errno = 0; // First time using "extern" kw btw



typedef unsigned int uint;

typedef struct FileReader
{
  char* filename;
  char* longest_word;
  uint character_count;
  uint space_count;
  uint line_count;
  uint word_count;
}
FileReader;



//            Core functions
FileReader    filereader_create();
void          filereader_destroy(FileReader* filereader);
void          filereader_reset(FileReader* filereader, bool new_filename);
void          filereader_print(FileReader* filereader);
void          filereader_read(FileReader* filereader);

//            Interface functions
void          menu_file_read(FileReader* filereader);
void          menu_file_change(FileReader* filereader);
void          user_input_get_filename(FileReader* filereader);



int main(void)
{
  uint opt = 0;
  FileReader filereader = filereader_create();

  void (*menu_actions[])(FileReader*) = {
    menu_file_read,
    menu_file_change
  };

  do
  {
    // Why did I even do this lol
    printf(ANSI_COLOR_CYAN "\n\n<-- Welcome to the ultimate file reading experience -->" ANSI_COLOR_RESET);
    printf("\n> We have carefully chosen the file reader that most adapts\n> to your needs, because your time for reading files matters.\n\n");
    char* menu[] = {"Exit", "Read file", "Change file"};

    for (uint i = 0; i < MENU_SIZE; i++)
    {
      printf(ANSI_COLOR_YELLOW "%d" ANSI_COLOR_RESET ". %s\n", i, menu[i]);
    }

    printf("\nPlease select an option: ");
    scanf("%d", &opt);
    fflush(stdin);

    if (!opt) break;

    if (opt >= MENU_SIZE)
      perror(ANSI_COLOR_RED "\n\nInvalid command" ANSI_COLOR_RESET);

    menu_actions[opt - 1](&filereader);
  }
  while (opt);

  filereader_destroy(&filereader);

  printf(ANSI_COLOR_GREEN "\n\nProgram terminated successfully." ANSI_COLOR_RESET);

  return EXIT_SUCCESS;
}



/**
 * Creates a FileReader struct.
 * @returns {FileReader}
 */

FileReader filereader_create()
{
  FileReader filereader;
  filereader.filename = NULL;

  filereader_reset(&filereader, false);

  return filereader;
}



/**
 * Deallocates the given FileReader struct from memory.
 * @param {FileReader*} filereader The file reader to deallocate.
 */

void filereader_destroy(FileReader* filereader)
{
  free(filereader->longest_word);
  free(filereader->filename);
}



/**
 * Resets a file reader to its initial values.
 * @param {FileReader*} filereader The file reader to reset.
 * @param {bool} new_filename Option to change the file name (true) or not (false).
 */

void filereader_reset(FileReader* filereader, bool new_filename)
{
  if (new_filename)
  {
    user_input_get_filename(filereader);
  }

  filereader->longest_word = NULL;
  filereader->character_count = 0;
  filereader->space_count = 0;
  filereader->line_count = 0;
  filereader->word_count = 0;
}



/** 
 * Validates the user input for the file name.
 * @param {FileReader*} filereader The file reader to assign the new file to read.
*/

void user_input_get_filename(FileReader* filereader)
{
  char temp[FILEREADER_FILENAME_MAXLEN];

  // Semi-dynamic formatter construction
  char format[8] = "%", n[4];
  strcat(format, itoa(FILEREADER_FILENAME_MAXLEN - 1, n, 10));
  strcat(format, "s");

  printf("> Enter an existing file name: ");
  scanf(format, temp);
  fflush(stdin);

  uint length = strlen(temp);
  filereader->filename = (char*) realloc(filereader->filename, length + 1);

  if (filereader->filename == NULL)
  {
    perror(ANSI_COLOR_RED "An error occurred while getting the file name." ANSI_COLOR_RESET);
    exit(EXIT_FAILURE);
  }

  strcpy(filereader->filename, temp);
}



/**
 * Reads the file bound to the file reader.
 * @param {FileReader*} filereader The file reader to use.
 */

void filereader_read(FileReader* filereader)
{
  FILE* file = fopen(filereader->filename, "r");

  if (file == NULL)
  {
    perror(ANSI_COLOR_RED "File not found" ANSI_COLOR_RESET);
    return;
  }

  char c;
  bool is_word = false;
  uint buffer_size = 64;
  uint longest_word_length = 0;
  uint current_word_length = 0;
  char* current_word = (char*) malloc(buffer_size);
  char* longest_word = (char*) malloc(buffer_size);

  for (filereader->line_count = 1; (c = fgetc(file)) != EOF; filereader->character_count++)
  {
    if (CHAR_IS_LETTER(c) || CHAR_IS_DIGIT(c))
    {
      // I think this is pretty clever ngl
      filereader->word_count += !is_word;
      is_word = true;

      if (++current_word_length + 1 > buffer_size)
      {
        buffer_size <<= 1;
        __string_reallocate(current_word, buffer_size);
        __string_reallocate(longest_word, buffer_size);
      }

      current_word[current_word_length - 1] = c;
      current_word[current_word_length] = '\0';

      if (current_word_length > longest_word_length)
      {
        longest_word_length = current_word_length;
        strcpy(longest_word, current_word);
      }

      continue;
    }

    current_word_length = 0;
    current_word[current_word_length] = '\0';
    is_word = false;

    switch (c)
    {
      case ' ':
        filereader->space_count++;
      break;

      case '\n':
        filereader->character_count++;
        filereader->line_count++;
      break;
    }
  }

  filereader->longest_word = realloc(filereader->longest_word, current_word_length + 1);

  if (filereader->longest_word == NULL)
    perror(ANSI_COLOR_RED "Error occurred while reading the file" ANSI_COLOR_RESET);
  else
    strcpy(filereader->longest_word, longest_word);

  free(current_word);
  free(longest_word);
  fclose(file);
}



/**
 * Prints out the information of the given file reader.
 * @param {FileReader*} filereader The file reader to print.
 */

void filereader_print(FileReader* filereader)
{
  printf("\n\n" ANSI_COLOR_CYAN "<-- |FILE RESULTS| -->" ANSI_COLOR_RESET "\n\n");
  printf("File: "             ANSI_COLOR_YELLOW "%s\n" ANSI_COLOR_RESET, filereader->filename);
  printf("Longest word: "     ANSI_COLOR_YELLOW "%s\n" ANSI_COLOR_RESET, filereader->longest_word);
  printf("Character count: "  ANSI_COLOR_YELLOW "%u\n" ANSI_COLOR_RESET, filereader->character_count);
  printf("Space count: "      ANSI_COLOR_YELLOW "%u\n" ANSI_COLOR_RESET, filereader->space_count);
  printf("Line count: "       ANSI_COLOR_YELLOW "%u\n" ANSI_COLOR_RESET, filereader->line_count);
  printf("Word count: "       ANSI_COLOR_YELLOW "%u\n" ANSI_COLOR_RESET, filereader->word_count);
  printf(ANSI_COLOR_CYAN "\n<-- <|o|> -->" ANSI_COLOR_RESET "\n\n");
}



/**
 * Assigns a file to the file reader if inexistent and reads the file.
 * @param {FileReader*} filereader The file reader to use.
 */

void menu_file_read(FileReader* filereader)
{
  if (filereader->filename == NULL)
    filereader_reset(filereader, true);

  filereader_read(filereader);

  if (filereader->character_count)
    filereader_print(filereader);
}



/**
 * Reassigns a file to the file reader.
 * @param {FileReader*} filereader The file reader to update.
 */

void menu_file_change(FileReader* filereader)
{
  filereader_reset(filereader, true);
}