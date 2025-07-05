// ====================================================================
//  $File: main.c $
//  $Date: 04-07-2025 @ 13-15-56 $
//  $Revision: 0.0.0 $
//  $Creator: aeternatrix $
//  $Notice: (C) Copyright 2025 by aeternatrix. All Rights Reserved. $
// ===================================================================

#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

typedef unsigned long uint64;

#define PAGE 4096

// I think I'll forward declare these from hereon instead; makes it more readable or sumthn
long read_file(char* buff);
void clear_red(char* buf);

/*
 * Santa's Accounting-Elves need help balancing the books after a recent order. Unfortunately, their accounting software uses a peculiar storage format. That's where you come in.
 * 
 * They have a JSON document which contains a variety of things: arrays (`[1,2,3]`), objects (`{"a":1, "b":2}`), numbers, and strings. Your first job is to simply find all of the numbers throughout the document and add them together.
 * 
 * For example:
 * 
 * - `[1,2,3]` and `{"a":2,"b":4}` both have a sum of `6`.
 * - `[[[3]]]` and `{"a":{"b":4},"c":-1}` both have a sum of `3`.
 * - `{"a":[-1,1]}` and `[-1,{"a":1}]` both have a sum of `0`.
 * - `[]` and `{}` both have a sum of `0`.
 * You will not encounter any strings containing numbers.
 * 
 * What is the sum of all numbers in the document?
 */

int part_one(const char* input) {
    int sum = 0;

    int ptr = 0;
    char c;
    int curr = 0;
    int neg = 1;
    do {
        c = input[ptr++];
        if (c == '-') {
            neg=-1;
            continue;
        }

        if (c <= '9' && c >='0') {
            curr = curr*10+c-'0';
        } else {
            sum += curr * neg;
            curr = 0;
            neg = 1;
        }
    } while (c);

    return sum;
}

/*
 * Uh oh - the Accounting-Elves have realized that they double-counted everything red.
 * 
 * Ignore any object (and all of its children) which has any property with the value `"red"`. Do this only for objects (`{...}`), not arrays (`[...]`).
 * 
 * - `[1,2,3]` still has a sum of `6`.
 * - `[1,{"c":"red","b":2},3]` now has a sum of `4`, because the middle object is ignored.
 * - `{"d":"red","e":[1,2,3,4],"f":5}` now has a sum of `0`, because the entire structure is ignored.
 * - `[1,"red",5]` has a sum of `6`, because "red" in an array has no effect.
 */
int part_two(char* input) {
    // First of all, how dare.
    // Now I have to write sumthn to actually parse json...
    // or... hmm... I don't need input[] after this...
    // >.>
    clear_red(input);
    
    int sum = 0;
    int ptr = 0;
    char c;
    int curr = 0;
    int neg = 1;
    do {
        c = input[ptr++];
        if (c == '-') {
            neg=-1;
            continue;
        }

        if (c <= '9' && c >='0') {
            curr = curr*10+c-'0';
        } else {
            sum += curr * neg;
            curr = 0;
            neg = 1;
        }
    } while (c);

    return sum;
}

int main() {
    char input[11 * PAGE] = {}; // File is ~10KB
    read_file(input);
    printf("The sum of all numbers is: %d.\n", part_one(input));
    printf("The sum of all non-red numbers is: %d.\n", part_two(input));
}

// Taken straight from day8; don't fix what ain't broke...
long
read_file(char* buff) {
    const char filename[] = "input.json"; // name update
    char mainc_path[PAGE] = {};
    char input_path[PAGE] = {};
    char* last_slash = mainc_path;
    int ptr = 0;
    struct stat st;

    realpath(__FILE__, mainc_path);

    for (char* scanner = mainc_path; *scanner; scanner++) {
        if (*scanner == '/') last_slash = scanner+1;
    }

    // main.c file path, excluding "main.c"
    for (int a = 0; a < (last_slash - mainc_path); a++) input_path[ptr++] = mainc_path[a];
    // append "input.json"
    // sizeof() instead of literal; only works cause filename is declared as filename[]
    for (int b = 0; b < sizeof(filename); b++) input_path[ptr++] = filename[b];

    ptr = open(input_path, O_RDONLY);
    if (ptr < 0) { printf("input file not found with main.c\n"); return 0; }

    fstat(ptr, &st);

    long bytes = read(ptr, buff, st.st_size);
    close(ptr);

    if (bytes < st.st_size) printf("Couldn't read file\n");

    return st.st_size;
}

void
clear_red(char* buf){
    int depth = 0;
    int target_depth = 0;
    char* c = buf;
    int skipping = 0;
    int back = 0;
    while(*c) {
        while(back) {
            if (c[0] == '{') {
                depth--;
                if (target_depth > depth) {
                    back = 0;
                    skipping = 1;
                    break;
                }
            }
            if (c[0] == '}') depth++;
            c--;
        }
        if (c[0] == '{') depth++;
        if (c[0] == '}') depth--;
        if (skipping) *c = '0';
        if (depth < target_depth) skipping = 0;
        if (c[0] == ':' && c[1]=='\"' && c[2] == 'r' && c[3] == 'e' && c[4] == 'd') {
            back = 1;
            target_depth = depth;
        }
        c++;
    }
}

