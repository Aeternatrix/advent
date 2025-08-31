// ====================================================================
//  $File: main.c $
//  $Date: 01-09-2025 @ 04-54-37 $
//  $Revision: 0.0.0 $
//  $Creator: aeternatrix $
//  $Notice: (C) Copyright 2025 by aeternatrix. All Rights Reserved. $
// ===================================================================


#include <stdio.h>
#include "day12_input.h"

typedef enum { INS_ERR, CPY, INC, DEC, JNZ } ins_type;
typedef enum { PARAM_ERR, NUM, REG } param_type;

typedef struct { param_type type; union { int val; char reg; }; } param;
typedef struct { ins_type type; param x, y; } instruction;
typedef struct { int ra, rb, rc, rd; } registers;

void read_instructions();
void run(registers* reg);

static instruction instructions[100] = {};

int part_one() {
    registers reg = {};
    run(&reg);
    return reg.ra;
}

int part_two() {
    registers reg = { .rc = 1 };
    run(&reg);
    return reg.ra;
}

int main() {
    read_instructions();
    printf("The value in register a is %d\n", part_one());
    printf("The value in register a is %d if the c register initialises with 1\n", part_two());
}

void
read_instructions() {
    char reg_a, reg_b;
    int val_a, val_b, n;

    const char* c = day12_input;
    instruction* ins = instructions;
    int reading = 1;
    while(reading) {
        if (sscanf(c, "cpy %d %c%n", &val_a, &reg_b, &n) == 2) {
            ins->type = CPY;
            ins->x = (param){NUM, val_a};
            ins->y = (param){REG, reg_b};
        } else if (sscanf(c, "cpy %c %c%n", &reg_a, &reg_b, &n) == 2) {
            ins->type = CPY;
            ins->x = (param){REG, reg_a};
            ins->y = (param){REG, reg_b};
        } else if (sscanf(c, "inc %c%n", &reg_a, &n) == 1) {
            ins->type = INC;
            ins->x = (param){REG, reg_a};
            ins->y = (param){PARAM_ERR, 0};
        } else if (sscanf(c, "dec %c%n", &reg_a, &n) == 1) {
            ins->type = DEC;
            ins->x = (param){REG, reg_a};
            ins->y = (param){PARAM_ERR, 0};
        } else if (sscanf(c, "jnz %d %d%n", &val_a, &val_b, &n) == 2) {
            ins->type = JNZ;
            ins->x = (param){NUM, val_a};
            ins->y = (param){NUM, val_b};
        } else if (sscanf(c, "jnz %c %d%n", &reg_a, &val_b, &n) == 2) {
            ins->type = JNZ;
            ins->x = (param){REG, reg_a};
            ins->y = (param){NUM, val_b};
        } else reading = 0;
        ins++;
        c+=n;
        if (*c=='\n') c++;
    }
}

void
run(registers *reg) {
    instruction* current = instructions;
    int pos = 0;
    for (;current->type != INS_ERR;) {
        switch (current->type) {
            case CPY: {
                int val = 0;
                if (current->x.type == NUM) val = current->x.val;
                else {
                    switch (current->x.reg) {
                        case 'a': val = reg->ra; break;
                        case 'b': val = reg->rb; break;
                        case 'c': val = reg->rc; break;
                        case 'd': val = reg->rd; break;
                        default: break;
                    }
                }
                switch (current->y.reg) {
                    case 'a': reg->ra = val; break;
                    case 'b': reg->rb = val; break;
                    case 'c': reg->rc = val; break;
                    case 'd': reg->rd = val; break;
                    default: break;
                }

            } break;
            case INC: {
                switch (current->x.reg) {
                    case 'a': reg->ra++; break;
                    case 'b': reg->rb++; break;
                    case 'c': reg->rc++; break;
                    case 'd': reg->rd++; break;
                    default: break;
                }
            } break;
            case DEC: {
                switch (current->x.reg) {
                    case 'a': reg->ra--; break;
                    case 'b': reg->rb--; break;
                    case 'c': reg->rc--; break;
                    case 'd': reg->rd--; break;
                    default: break;
                }
            } break;
            case JNZ: {
                int jmp_val = current->y.val;
                int condition = 0;
                if (current->x.type == NUM) condition = current->x.val;
                else {
                    switch (current->x.reg) {
                        case 'a': condition = reg->ra; break;
                        case 'b': condition = reg->rb; break;
                        case 'c': condition = reg->rc; break;
                        case 'd': condition = reg->rd; break;
                        default: break;
                    }
                }
                if (condition) {
                    current += jmp_val;
                    pos += jmp_val;
                    continue;
                }
            } break;
            default:
                break;
        }
        pos++;
        current++;
    }
}
