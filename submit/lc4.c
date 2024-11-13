/************************************************************************/
/* File Name : lc4.c 													*/
/* Purpose   : This file contains the main() for this project			*/
/*             main() will call the loader and disassembler functions	*/
/*             															*/
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include <string.h>
#include "lc4_memory.h"
#include "lc4_loader.h"
#include "lc4_disassembler.h"

/* program to mimic pennsim loader and disassemble object files */

int main(int argc, char **argv) {
  /* leave plenty of room for the filename */

  char filename[100];

  /**
     * main() holds the linked list &
     * only calls functions in other files
     */

  /* step 1: create head pointer to linked list: memory   */
  /* do not change this line - there should no be malloc calls in main() */

  row_of_memory *memory = NULL;

  /* step 2: determine filename, then open it     */
  /*   TODO: extract filename from argv, pass it to open_file() */
  if (argc < 2) {
    printf("Usage: %s <object_file.obj>\n", argv[0]);
    return -1;
  }
  strcpy(filename, argv[1]);
  FILE *file = open_file(filename);
  if (file == NULL) {
    return -1;
  }

  /* step 3: call function: parse_file() in lc4_loader.c  */
  /*   TODO: call function & check for errors     */
  if (parse_file(file, &memory) != 0) {
    fclose(file);
    return -1;
  }
  fclose(file);

  /* step 4: call function: reverse_assemble() in lc4_disassembler.c */
  /*   TODO: call function & check for errors     */
  if (reverse_assemble(memory) != 0) {
    return -1;
  }

  /* step 5: call function: print_list() in lc4_memory.c   */
  /*   TODO: call function                */
  print_list(memory);

  /* step 6: call function: delete_list() in lc4_memory.c */
  /*   TODO: call function & check for errors     */
  if (delete_list(&memory) != 0) {
    return -1;
  }

  /* only return 0 if everything works properly */
  return 0;
}
