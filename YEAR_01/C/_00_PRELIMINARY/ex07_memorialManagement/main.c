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



#define MEM_FREE 0
#define BLOCK_SIZE 256



typedef unsigned int uint;

typedef struct Node
{
  char data[BLOCK_SIZE];
  uint program_id;
  Node* next;
}
Node;



typedef struct Program
{
  Node* head;
  uint size;
}
Program;



// Core functions
Node*     allocator_initialize_memory(uint size);
void      allocator_allocate_program(Program* program);
void      allocator_deallocate_program(Program* program);
void      allocator_allocate_node(Node* node);
void      allocator_deallocate_node(Node* node);

//Interface functions



int main(void)
{
  // STEPS:
  // 1. Create a linked list given the size as input
  // 2. Make a user-friendly menu with the options to add, remove and view all the memory blocks.
  //  2.1. (EXTRA) Add an option to optimize the memory (defragment)
  //

}