// ====================================================================
//  $File: main.c $
//  $Date: 10-07-2025 @ 06-52-29 $
//  $Revision: 0.0.0 $
//  $Creator: aeternatrix $
//  $Notice: (C) Copyright 2025 by aeternatrix. All Rights Reserved. $
// ===================================================================

#include <stdio.h>
#include <stdlib.h>

#include "input.h"
#define PAGE 4096

typedef enum { NA, E, Rn, Y, Ar } token_t;

int read_token(const char* c, token_t* out);
int m_strlen(const char* a);
int m_strcmp(const char* a, int alen, const char* b, int blen);
int is_capital(char c) { return c <= 'Z' && c >= 'A'; }
/*
 * Rudolph the Red-Nosed Reindeer is sick! His nose isn't shining very brightly, and he needs medicine.
 * 
 * Red-Nosed Reindeer biology isn't similar to regular reindeer biology; Rudolph is going to need custom-made medicine. Unfortunately, Red-Nosed Reindeer chemistry isn't similar to regular reindeer chemistry, either.
 * 
 * The North Pole is equipped with a Red-Nosed Reindeer nuclear fusion/fission plant, capable of constructing any Red-Nosed Reindeer molecule you need. It works by starting with some input molecule and then doing a series of replacements, one per step, until it has the right molecule.
 * 
 * However, the machine has to be calibrated before it can be used. Calibration involves determining the number of molecules that can be generated in one step from a given starting point.
 * 
 * For example, imagine a simpler machine that supports only the following replacements:
 * 
 * - `H => HO`
 * - `H => OH`
 * - `O => HH`
 * Given the replacements above and starting with HOH, the following molecules could be generated:
 * 
 * - `HOOH` (via `H => HO` on the first `H`).
 * - `HOHO` (via `H => HO` on the second `H`).
 * - `OHOH` (via `H => OH` on the first `H`).
 * - `HOOH` (via `H => OH` on the second `H`).
 * - `HHHH` (via `O => HH`).
 * So, in the example above, there are `4` distinct molecules (not five, because `HOOH` appears twice) after one replacement from `HOH`. Santa's favorite molecule, `HOHOHO`, can become `7` distinct molecules (over nine replacements: six from `H`, and three from `O`).
 * 
 * The machine replaces without regard for the surrounding characters. For example, given the string `H2O`, the transition `H => OO` would result in `OO2O`.
 * 
 * Your puzzle input describes all of the possible replacements and, at the bottom, the medicine molecule for which you need to calibrate the machine. How many distinct molecules can be created after all the different ways you can do one replacement on the medicine molecule?
 */
int part_one() {
    // This is bad. I did other things that *probably* worked; however,
    // I had an error in my strlen function that caused me to rewrite
    // this so many times before I found out that the strlen was wrong
    // But I ain't rewriting it again.

    int sz = sizeof(initial);
    //-- Allocate buffers
    char** buffers = calloc(PAGE, sizeof(char*));
    for (int i = 0; i < PAGE; i++) buffers[i] = calloc(PAGE, sizeof(char));
    
    //-- Generate buffers

    int repl = 0;
    int foundat = 0;
    char* buffer = buffers[repl++];
    int ptr = 0;
    for (int i = 0; i < input_len; i++) {
        ptr = 0;
        rep wp = input[i];
        const char* c = initial;
        int replace = 0;
        do {
            if (c[0] == wp.a[0] && wp.a[1] && c[1] == wp.a[1]) {
                c+=2;
                replace = 1;
            }
            if (c[0] == wp.a[0] && !wp.a[1]) {
                c++;
                replace = 1;
            }
            if (replace) {
                replace = c - initial;
                int EoL = *c == '\0';
                //-- replace the text
                const char* replacement = wp.b;
                do buffer[ptr++] = *replacement; while (*++replacement);
                //-- finish the text
                if (!EoL) {
                    do buffer[ptr++] = *c++; while (*c);
                }
                //-- next buffer
                buffer = buffers[repl++];
                //-- fill buffer to current
                if (!EoL) {
                    c = initial;
                    for (ptr=0;ptr < replace; ptr++) buffer[ptr] = *c++;
                }
                replace = 0;
            } else {
                buffer[ptr++] = *c++;
            }
        } while (*c);
    }

    //-- Check for duplicates
    int counter = 0;
    for (int i=0;i<PAGE;i++) {
        if (!buffers[i][0]) break;
        char* str_i = buffers[i];
        int len_i = m_strlen(str_i);
        int unique = 1;

        for (int j=i+1;j<PAGE && unique;j++) {
            if (!buffers[j][0]) break;
            char* str_j = buffers[j];
            int len_j = m_strlen(str_j);
            if (m_strcmp(str_i, len_i, str_j, len_j)) unique = 0;
        }
        counter += unique;
    }

    for (int i = 0; i < input_len; i++) {
        free(buffers[i]);
    }
    free(buffers);
    return counter-1; // Subtract 1 for the initial/default
}

/*
 * Now that the machine is calibrated, you're ready to begin molecule fabrication.
 * 
 * Molecule fabrication always begins with just a single electron, e, and applying replacements one at a time, just like the ones during calibration.
 * 
 * For example, suppose you have the following replacements:
 * 
 * - `e => H`
 * - `e => O`
 * - `H => HO`
 * - `H => OH`
 * - `O => HH`
 * If you'd like to make `HOH`, you start with `e`, and then make the following replacements:
 * 
 * - `e => O` to get `O`
 * - `O => HH` to get `HH`
 * - `H => OH` (on the second `H`) to get `HOH`
 * So, you could make `HOH` after 3 steps. Santa's favorite molecule, `HOHOHO`, can be made in 6 steps.
 * 
 * How long will it take to make the medicine? Given the available replacements and the medicine molecule in your puzzle input, what is the fewest number of steps to go from `e` to the medicine molecule?
 */
int part_two() {
    // Well this was a challenge...
    // So, looking at the input, we have some patterns

    const char* c = initial;
    int count = 0;
    while (*c) {
        token_t t;
        c += read_token(c, &t);
        switch (t) {
            case E: count++;
            case Rn:
            case Ar: break;
            case Y: count--;
            default: break;
        }
    }

    return count-1; // To remove the 'final' result
}

int main() {
    printf("There are %d distinct molecules that can be created.\n", part_one());
    printf("The minimum steps needed to make the molecule is %d.\n", part_two());
}

int m_strcmp(const char* a, int alen, const char* b, int blen) {
    if (alen != blen) return 0;
    for (int itr=0;itr<alen;itr++) if (a[itr] != b[itr]) return 0;
    return 1;
}

int m_strlen(const char* a) {
    const char* c = a;
    while(*c++);
    return c-a;
}

int read_token(const char* c, token_t* out) {
    if (c[0] == 'R' && c[1] && c[1] == 'n') { *out = Rn; return 2; }
    if (c[0] == 'A' && c[1] && c[1] == 'r') { *out = Ar; return 2; }
    if (c[0] == 'Y')                        { *out = Y;  return 1; }
    *out = E;
    if (is_capital(c[0])) if (!c[1] || (c[1] && is_capital(c[1]))) return 1;
    return 2;
}
