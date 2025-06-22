// ====================================================================
//  $File: main.c $
//  $Date: 10-06-2025 @ 16-38-19 $
//  $Revision: 0.0.0 $
//  $Creator: aeternatrix $
//  $Notice: (C) Copyright 2025 by aeternatrix. All Rights Reserved. $
// ===================================================================

#include <stdio.h>
#include "input.h"

// Dun wanna retype all those letters
typedef unsigned char       byte;
typedef unsigned short int  uint16;

// Okay, so, plan™:
// - Read each line into an instruction set array
// - Read back from the wire

// Instructions
// V1 op V2 -> dest
// V1 -> dest
// op V1 -> dest

// Operator Flags
#define NONE    0
#define AND     1
#define OR      2
#define NOT     3
#define LSHIFT  4
#define RSHIFT  5


typedef struct {
    uint16 values[2];       // 4 bytes
    uint16 identifiers[2];  // 4 bytes
    byte op;                // 1 byte
} instruction;

// Behold, my laziness! These are HashMaps if you squint... Keys are char << 8 | char
instruction instructions[0xFFFF] = {};  // 10 bytes * 65535 = approx 639KB
uint16 wires[0xFFFF] = {};              // 2 bytes * 65535 = approx 127KB
                                        // Memory is cheap — and I am lazy

void
read_instructions() {
    char c;
    uint16 o = NONE;
    uint16 vals[3] = {};
    uint16 ids[3] = {};
    int itr = 0;
    int v = 0;
    do {
        if (v > 2) { 
            printf("ERROR");
            return;
        }
        c = input[itr++];
        if (c <= 'Z' && c >= 'A') {
            if (c == 'A') o = AND;
            if (c == 'O') o = OR;
            if (c == 'N') o = NOT;
            if (c == 'L') o = LSHIFT;
            if (c == 'R') o = RSHIFT;
            while (input[itr-1] != ' ') c = input[itr++];
            continue;
        }
        if (c == ' ') {
            if (input[itr] == '-') {
                while (input[itr] != ' ') c = input[itr++];
                itr++;
            }
            v++;
        }
        if (c <= 'z' && c >= 'a') ids[v] = ids[v] << 8 | c;
        if (c <= '9' && c >= '0') vals[v] = vals[v] * 10 + c - '0';

        if (c == '\n' || c == '\0') {
            instruction ins;
            uint16 dest = ids[2] == 0 ? ids[1] : ids[2];
            instructions[dest].op = o;
            instructions[dest].values[0] = vals[0];
            instructions[dest].values[1] = vals[1];
            instructions[dest].identifiers[0] = ids[0];
            instructions[dest].identifiers[1] = ids[1];

            vals[0] = 0;
            vals[1] = 0;
            vals[2] = 0;
            ids[0] = 0;
            ids[1] = 0;
            ids[2] = 0;
            v = 0;
            o = NONE;
        }
    } while(input[itr] != '\0');
}


uint16
resolve_instruction(uint16 key) {
    instruction ins = instructions[key];
    if (wires[key]) return wires[key];
    uint16 left, right;
    if (ins.identifiers[0] && ins.identifiers[0] != key) {
        left = resolve_instruction(ins.identifiers[0]);
    } else {
        left = ins.values[0];
    }

    if (ins.identifiers[1] && ins.identifiers[1] != key) {
        right = resolve_instruction(ins.identifiers[1]);
    } else {
        right = ins.values[1];
    }

    switch (ins.op) {
        case NONE:
            wires[key] = left;
            return left;
        case AND:
            wires[key] = left & right;
            return left & right;
        case OR:
            wires[key] = left | right;
            return left | right;
        case NOT:
            wires[key] = ~left;
            return ~left;
        case LSHIFT:
            wires[key] = left << right;
            return left << right;
        case RSHIFT:
            wires[key] = left >> right;
            return left >> right;
    }
    return 0;
}

/*
 * This year, Santa brought little Bobby Tables a set of wires and bitwise logic gates! Unfortunately, little Bobby is a little under the recommended age range, and he needs help assembling the circuit.
 * 
 * Each wire has an identifier (some lowercase letters) and can carry a 16-bit signal (a number from `0` to `65535`). A signal is provided to each wire by a gate, another wire, or some specific value. Each wire can only get a signal from one source, but can provide its signal to multiple destinations. A gate provides no signal until all of its inputs have a signal.
 * 
 * The included instructions booklet describes how to connect the parts together: `x AND y -> z` means to connect wires `x` and `y` to an AND gate, and then connect its output to wire `z`.
 * 
 * For example:
 * 
 * - `123 -> x` means that the signal `123` is provided to wire x.
 * - `x AND y -> z` means that the bitwise AND of wire `x` and wire `y` is provided to wire `z`.
 * - `p LSHIFT 2 -> q` means that the value from wire `p` is left-shifted by `2` and then provided to wire `q`.
 * - `NOT e -> f` means that the bitwise complement of the value from wire `e` is provided to wire `f`.
 * Other possible gates include `OR` (bitwise OR) and `RSHIFT` (right-shift). If, for some reason, you'd like to emulate the circuit instead, almost all programming languages (for example, C, JavaScript, or Python) provide operators for these gates.
 * 
 * For example, here is a simple circuit:
 * 
 * - `123 -> x`
 * - `456 -> y`
 * - `x AND y -> d`
 * - `x OR y -> e`
 * - `x LSHIFT 2 -> f`
 * - `y RSHIFT 2 -> g`
 * - `NOT x -> h`
 * - `NOT y -> i`
 * After it is run, these are the signals on the wires:
 * 
 * - `d: 72`
 * - `e: 507`
 * - `f: 492`
 * - `g: 114`
 * - `h: 65412`
 * - `i: 65079`
 * - `x: 123`
 * - `y: 456`
 * In little Bobby's kit's instructions booklet (provided as your puzzle input), what signal is ultimately provided to wire a?
 */
int part_one() {
    uint16 key = 'a';
    return resolve_instruction(key);
}
/*
 * Now, take the signal you got on wire a, override wire b to that signal, and reset the other wires (including wire a). What new signal is ultimately provided to wire a?
 */
int part_two() {
    uint16 a_key = 'a';
    uint16 b_key = 'b';
    uint16 a_wire = resolve_instruction(a_key);
    for (int wire = 0; wire < 0xFFFF; wire++) wires[wire] = 0;
    wires[b_key] = a_wire;
    return resolve_instruction(a_key);
}

int main() {
    read_instructions();
    printf("Wire a has the signal %d.\n", part_one());
    printf("Wire a has the signal %d after the additional instructions.\n", part_two());
}
