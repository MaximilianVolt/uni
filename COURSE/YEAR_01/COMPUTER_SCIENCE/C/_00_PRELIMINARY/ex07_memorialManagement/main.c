/**
 * @desc
 * Write a C program that simulates a basic memory allocator. The program should
 * allow the user to request memory blocks of varying sizes and then free them
 * when no longer needed.
 *
 * @note
 * Implement a `malloc` and `free` mechanism using linked lists to manage
 * the memory blocks.
 *
 * @note
 * The program should keep track of the allocated and free memory blocks.
 *
 * @note
 * The user should be able to allocate memory of different sizes, view the
 * current memory allocation, and free specific blocks.
 *
 * @note
 * Handle cases where memory cannot be allocated due to insufficient available
 * memory.
 */



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>



#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"



#define MEM_SIZE_MAX 64
#define MEM_FREE 0
#define MENU_SIZE 4



typedef unsigned int uint;

typedef struct Node
{
  struct Node* next;
  uint data;
}
Node;



//        Core functions
Node*     memory_allocate_all();
void      memory_print_all(Node* head);
Node*     memory_append_block(Node* head, uint data);
uint      memory_remove_block(Node** head, uint data);



//        Interface functions
Node*     memory_add_block(Node* head, uint data);
void      memory_delete_block(Node** head);
uint      menu_input_manage();
void      menu(Node* memory);
void      menu_print();



int main(void)
{
  Node* memory = memory_allocate_all();

  menu(memory);

  printf_s(ANSI_COLOR_GREEN "\n\nProgram terminated successfully.\n\n" ANSI_COLOR_RESET);
  return EXIT_SUCCESS;
}



/**
 * Creates an user-friendly interface menu.
 */

void menu(Node* memory)
{
  uint opt = 0;

  do
  {
    menu_print();
    opt = menu_input_manage();

    switch (opt)
    {
      case 0: break;

      case 1:
        memory_print_all(memory);
      break;

      case 2:
        memory = memory_append_block(memory, 1);
      break;

      case 3:
        memory_delete_block(&memory);
      break;
    }
  }
  while (opt);

  free(memory);
  memory = NULL;
}



/**
 * Prints the menu.
 */

void menu_print()
{
  char* menu_options[] = {"Quit", "Print", "Add", "Remove"};

  for (uint i = 0; i < MENU_SIZE; i++)
  {
    printf_s("%d. %s\n", i, menu_options[i]);
  }
}



/**
 * Gets the input of the user.
 * @returns {uint}
 */

uint menu_input_manage()
{
  int opt = 0;
  bool invalid = false;

  do
  {
    printf_s("\nSelect an option: ");
    invalid = !scanf_s("%d", &opt) || opt >= MENU_SIZE;
    fflush(stdin);

    if (invalid)
    {
      perror("\n\n<-- Invalid command! -->");
    }
  }
  while (invalid);

  return opt;
}



/**
 * 
 */

Node* memory_allocate_all()
{
  Node* head = NULL;

  for (uint i = 0; i < 20; i++)
  {
    head = memory_append_block(head, i);
  }

  return head;
}



/**
 * 
 */

Node* memory_append_block(Node* head, uint data)
{
  Node* new = malloc(sizeof(Node));

  if (new)
  {
    new->data = data;
    new->next = head;
  }

  free(head);
  return new;
}



/**
 * 
 */

void memory_print_all(Node* head)
{
  uint i = 0;
  Node* current = head;

  while (current)
  {
    printf_s("%d -> ", current->data);
    current = current->next;
  }

  printf_s("\n\n");
}



/**
 * 
 */

uint memory_remove_block(Node** head, uint data)
{
  Node* previous = *head;
  Node* current = *head;

  while (current != NULL)
  {
    if (current->data == data)
    {
      if (current != *head)
      {
        previous->next = current->next;
        free(current);
        current = NULL;
        return 1;
      }
      else
        *head = current->next;
    }

    previous = current;
    current = current->next;
  }

  return 0;
}



/**
 * 
 */

void memory_delete_block(Node** head)
{
  uint data;
  bool invalid = false;

  do
  {
    printf_s(ANSI_COLOR_CYAN "\n\nType in a data to remove: " ANSI_COLOR_RESET);
    invalid = !scanf_s("%d", &data);
    fflush(stdin);
  }
  while (invalid);

  memory_remove_block(head, data);
}