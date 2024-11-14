/************************************************************************/
/* File Name : lc4_disassembler.c 										*/
/* Purpose   : This file implements the reverse assembler 				*/
/*             for LC4 assembly.  It will be called by main()			*/
/*             															*/
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lc4_memory.h"

int reverse_assemble(row_of_memory *memory) {
  row_of_memory *current = memory;
  while (current != NULL) {
    if (current->assembly == NULL) {
      unsigned short instr = current->contents;
      unsigned short opcode = (instr >> 12) & 0xF;
      char *assembly = (char *)malloc(50);
      if (assembly == NULL) {
        return -1;
      }
      switch (opcode) {
        case 0x0:  // NOP or BR
          if (instr == 0x0000) {
            // sprintf(assembly, "NOP");
			// here we remove nop instruct
            free(assembly);
            assembly = NULL;
          } else {
            unsigned short n = (instr >> 11) & 0x1;
            unsigned short z = (instr >> 10) & 0x1;
            unsigned short p = (instr >> 9) & 0x1;
            short offset = instr & 0x1FF;
            if (offset & 0x100) {
              offset |= 0xFE00;
            }
            char condition[4] = "";
            if (n) strcat(condition, "n");
            if (z) strcat(condition, "z");
            if (p) strcat(condition, "p");
            if (condition[0] == '\0') {
            //   sprintf(assembly, "NOP");
            free(assembly);
            assembly = NULL;
            } else {
              sprintf(assembly, "BR%s #%d", condition, offset);
            }
          }
          break;
        case 0x1: {  // Arithmetic operations
          unsigned short sub_opcode = (instr >> 3) & 0x7;
          unsigned short Rd = (instr >> 9) & 0x7;
          unsigned short Rs = (instr >> 6) & 0x7;
          if (((instr >> 5) & 0x1) == 0) {
            unsigned short Rt = instr & 0x7;
            switch (sub_opcode) {
              case 0x0:
                sprintf(assembly, "ADD R%d, R%d, R%d", Rd, Rs, Rt);
                break;
              case 0x1:
                sprintf(assembly, "MUL R%d, R%d, R%d", Rd, Rs, Rt);
                break;
              case 0x2:
                sprintf(assembly, "SUB R%d, R%d, R%d", Rd, Rs, Rt);
                break;
              case 0x3:
                sprintf(assembly, "DIV R%d, R%d, R%d", Rd, Rs, Rt);
                break;
              default:
                sprintf(assembly, "INVALID");
                break;
            }
          } else {
            short imm5 = instr & 0x1F;
            if (imm5 & 0x10) {
              imm5 |= 0xFFE0;
            }
            sprintf(assembly, "ADD R%d, R%d, #%d", Rd, Rs, imm5);
          }
          break;
        }
        case 0x5: {  // Logical operations
          unsigned short sub_opcode = (instr >> 3) & 0x7;
          unsigned short Rd = (instr >> 9) & 0x7;
          unsigned short Rs = (instr >> 6) & 0x7;
          if (((instr >> 5) & 0x1) == 0) {
            unsigned short Rt = instr & 0x7;
            switch (sub_opcode) {
              case 0x0:
                sprintf(assembly, "AND R%d, R%d, R%d", Rd, Rs, Rt);
                break;
              case 0x1:
                sprintf(assembly, "NOT R%d, R%d", Rd, Rs);
                break;
              case 0x2:
                sprintf(assembly, "OR R%d, R%d, R%d", Rd, Rs, Rt);
                break;
              case 0x3:
                sprintf(assembly, "XOR R%d, R%d, R%d", Rd, Rs, Rt);
                break;
              default:
                sprintf(assembly, "INVALID");
                break;
            }
          } else {
            short imm5 = instr & 0x1F;
            if (imm5 & 0x10) {
              imm5 |= 0xFFE0;
            }
            sprintf(assembly, "AND R%d, R%d, #%d", Rd, Rs, imm5);
          }
          break;
        }
        case 0xF: {  // TRAP
          unsigned short trapvect8 = instr & 0xFF;
          sprintf(assembly, "TRAP x%02X", trapvect8);
          break;
        }
        /* Handle other opcodes similarly */
        default:
          //   sprintf(assembly, "UNIMPLEMENTED");
          free(assembly);
          assembly = NULL;
          break;
      }
      current->assembly = assembly;
    }
    current = current->next;
  }
  return 0;
}
