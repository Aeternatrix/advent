// ====================================================================
//  $File: main.c $
//  $Date: 13-07-2025 @ 22-35-51 $
//  $Revision: 0.0.0 $
//  $Creator: aeternatrix $
//  $Notice: (C) Copyright 2025 by aeternatrix. All Rights Reserved. $
// ===================================================================

#include <stdio.h>

typedef struct {
    unsigned long long a, b;
} registers;
void execute(registers* r);

/*
 * Little Jane Marie just got her very first computer for Christmas from some unknown benefactor. It comes with instructions and an example program, but the computer itself seems to be malfunctioning. She's curious what the program does, and would like you to help her run it.
 * 
 * The manual explains that the computer supports two registers and six instructions (truly, it goes on to remind the reader, a state-of-the-art technology). The registers are named a and b, can hold any non-negative integer, and begin with a value of 0. The instructions are as follows:
 * 
 * - `hlf r` sets register `r` to half its current value, then continues with the next instruction.
 * - `tpl r` sets register `r` to triple its current value, then continues with the next instruction.
 * - `inc r` increments register `r`, adding `1` to it, then continues with the next instruction.
 * - `jmp offset` is a jump; it continues with the instruction `offset` away relative to itself.
 * - `jie r, offset` is like `jmp`, but only jumps if register `r` is even ("jump if even").
 * - `jio r, offset` is like `jmp`, but only jumps if register `r` is `1` ("jump if one", not odd).
 * All three jump instructions work with an offset relative to that instruction. The offset is always written with a prefix + or - to indicate the direction of the jump (forward or backward, respectively). For example, jmp +1 would simply continue with the next instruction, while jmp +0 would continuously jump back to itself forever.
 * 
 * The program exits when it tries to run an instruction beyond the ones defined.
 * 
 * For example, this program sets a to 2, because the jio instruction causes it to skip the tpl instruction:
 * 
 * - inc a
 * - jio a, +2
 * - tpl a
 * - inc a
 * What is the value in register b when the program in your puzzle input is finished executing?
 */
int part_one() {
    registers r = {};
    execute(&r);
    return r.b;
}

/*
 * The unknown benefactor is very thankful for releasi-- er, helping little Jane Marie with her computer. Definitely not to distract you, what is the value in register `b` after the program is finished executing if register `a` starts as `1` instead?
 */
int part_two() {
    registers r = {1};
    execute(&r);
    return r.b;
}

int main() {
    printf("Register b holds the value %d.\n", part_one());
    printf("Register b holds the value %d.\n", part_two());
}

typedef enum { HLF, TPL, INC, JMP, JIE, JIO } ins_e;
typedef struct {
  ins_e instruction;
  int val, offset;
} ins_t;
ins_t instructions[] = {
    {JIO, 1, +18}, {INC, 1}, {TPL, 1},  {INC, 1},     {TPL, 1}, {TPL, 1},
    {TPL, 1},      {INC, 1}, {TPL, 1},  {INC, 1},     {TPL, 1}, {INC, 1},
    {INC, 1},      {TPL, 1}, {TPL, 1},  {TPL, 1},     {INC, 1}, {JMP, +22},
    {TPL, 1},      {INC, 1}, {TPL, 1},  {INC, 1},     {INC, 1}, {TPL, 1},
    {INC, 1},      {TPL, 1}, {INC, 1},  {INC, 1},     {TPL, 1}, {TPL, 1},
    {INC, 1},      {INC, 1}, {TPL, 1},  {INC, 1},     {INC, 1}, {TPL, 1},
    {INC, 1},      {INC, 1}, {TPL, 1},  {JIO, 1, +8}, {INC, 2}, {JIE, 1, +4},
    {TPL, 1},      {INC, 1}, {JMP, +2}, {HLF, 1},     {JMP, -7}};

void execute(registers* r) {
    int ptr = 0;
    while (ptr >= 0 && ptr < (sizeof(instructions) / sizeof(ins_t))) {
        ins_t curr = instructions[ptr];
        switch (curr.instruction) {
            case HLF:
                if (curr.val == 1)
                    r->a /= 2;
                if (curr.val == 2)
                    r->b /= 2;
                ptr++;
                break;
            case TPL:
                if (curr.val == 1)
                    r->a *= 3;
                if (curr.val == 2)
                    r->b *= 3;
                ptr++;
                break;
            case INC:
                if (curr.val == 1)
                    r->a++;
                if (curr.val == 2)
                    r->b++;
                ptr++;
                break;
            case JMP:
                ptr += curr.val;
                break;
            case JIE: {
                    int offset = 1;
                    if (curr.val == 1) offset = (r->a % 2) == 0 ? curr.offset : 1;
                    if (curr.val == 2) offset = (r->b % 2) == 0 ? curr.offset : 1;
                    ptr += offset;
                }break;
            case JIO: { //-- How fooking dare this not be "if odd"
                    int offset = 1;
                    if (curr.val == 1) offset = r->a  == 1 ? curr.offset : 1;
                    if (curr.val == 2) offset = r->b  == 1 ? curr.offset : 1;
                    ptr += offset;
                }break;
        }
    }
}

