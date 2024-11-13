/************************************************************************/
/* File Name : lc4_memory.c		 										*/
/* Purpose   : This file implements the linked_list helper functions	*/
/* 			   to manage the LC4 memory									*/
/*             															*/
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lc4_memory.h"

/*
 * adds a new node to a linked list pointed to by head
 */
int add_to_list(row_of_memory **head,
                short unsigned int address,
                short unsigned int contents) {
  /* Check if the node already exists */
  row_of_memory *existing_node = search_address(*head, address);
  if (existing_node != NULL) {
    existing_node->contents = contents;
    return 0;
  }

  /* Allocate memory for a new node */
  row_of_memory *new_node = (row_of_memory *)malloc(sizeof(row_of_memory));
  if (new_node == NULL) {
    return -1;
  }

  /* Initialize the new node */
  new_node->address = address;
  new_node->contents = contents;
  new_node->label = NULL;
  new_node->assembly = NULL;
  new_node->next = NULL;

  /* Insert the new node into the linked list in ascending order */
  if (*head == NULL || (*head)->address > address) {
    new_node->next = *head;
    *head = new_node;
  } else {
    row_of_memory *current = *head;
    while (current->next != NULL && current->next->address < address) {
      current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
  }

  return 0;
}

/*
 * search linked list by address field, returns node if found
 */
row_of_memory *search_address(row_of_memory *head,
                              short unsigned int address) {
  row_of_memory *current = head;
  while (current != NULL) {
    if (current->address == address) {
      return current;
    }
    current = current->next;
  }
  return NULL;
}

/*
 * search linked list by opcode field, returns node if found
 */
row_of_memory *search_opcode(row_of_memory *head,
                             short unsigned int opcode) {
  row_of_memory *current = head;
  while (current != NULL) {
    unsigned short instr = current->contents;
    unsigned short instr_opcode = (instr >> 12) & 0xF;
    if (instr_opcode == opcode && current->assembly == NULL) {
      return current;
    }
    current = current->next;
  }
  return NULL;
}

void print_list(row_of_memory *head) {
  /* make sure head isn't NULL */
  if (head == NULL) {
    return;
  }

  /* print out a header */
  printf("%-20s %-20s %-20s %s\n", "<label>", "<address>", "<contents>", "<assembly>");

  /* traverse linked list, print contents of each node */
  row_of_memory *current = head;
  while (current != NULL) {
    char address_str[20];
    char contents_str[20];
    sprintf(address_str, "%04X", current->address);
    sprintf(contents_str, "%04X", current->contents);
    printf("%-20s %-20s %-20s %s\n",
           current->label ? current->label : "",
           address_str,
           contents_str,
           current->assembly ? current->assembly : "");
    current = current->next;
  }

  return;
}

/*
 * delete entire linked list
 */
int delete_list(row_of_memory **head) {
  row_of_memory *current = *head;
  while (current != NULL) {
    row_of_memory *next_node = current->next;
    if (current->label != NULL) {
      free(current->label);
    }
    if (current->assembly != NULL) {
      free(current->assembly);
    }
    free(current);
    current = next_node;
  }
  *head = NULL;
  return 0;
}