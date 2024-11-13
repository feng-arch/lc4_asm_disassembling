/************************************************************************/
/* File Name : lc4_loader.c		 										*/
/* Purpose   : This file implements the loader (ld) from PennSim		*/
/*             It will be called by main()								*/
/*             															*/
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "lc4_memory.h"

/* declarations of functions that must defined in lc4_loader.c */

FILE *open_file(char *file_name) {
  FILE *file = fopen(file_name, "rb");
  if (file == NULL) {
    perror("Error opening file");
  }
  return file;
}

/* Helper function to read a 16-bit word from the file */
unsigned short read_half_word(FILE *file) {
  unsigned char bytes[2];
  if (fread(bytes, 1, 2, file) != 2) {
    return 0;
  }
  return (bytes[0] << 8) | bytes[1];
}

int parse_file(FILE *my_obj_file, row_of_memory **memory) {
  while (!feof(my_obj_file)) {
    unsigned short header = read_half_word(my_obj_file);
    if (feof(my_obj_file)) {
      break;
    }
    unsigned short address = read_half_word(my_obj_file);
    unsigned short n = read_half_word(my_obj_file);

    if (header == 0xCADE || header == 0xDADA) {
      /* Code or Data section */
      for (int i = 0; i < n; i++) {
        unsigned short contents = read_half_word(my_obj_file);
        add_to_list(memory, address + i, contents);
      }
    } else if (header == 0xC3B7) {
      /* Symbol section */
      char *label = (char *)malloc(n + 1);
      if (label == NULL) {
        return -1;
      }
      if (fread(label, 1, n, my_obj_file) != n) {
        free(label);
        return -1;
      }
      label[n] = '\0';  // Null-terminate the string

      row_of_memory *node = search_address(*memory, address);
      if (node != NULL) {
        node->label = label;
      } else {
        /* Create a new node with only label and address */
        add_to_list(memory, address, 0);
        node = search_address(*memory, address);
        node->label = label;
      }
    } else {
      /* Unknown header, skip n words */
      fseek(my_obj_file, n * 2, SEEK_CUR);
    }
  }
  return 0;
}
