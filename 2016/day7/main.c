// ====================================================================
//  $File: main.c $
//  $Date: 07-08-2025 @ 12-54-47 $
//  $Revision: 0.0.0 $
//  $Creator: aeternatrix $
//  $Notice: (C) Copyright 2025 by aeternatrix. All Rights Reserved. $
// ===================================================================

#include <stdio.h>

#include "day7_input.h"

#define PAGE 4096

typedef struct {const char* start, *end; } string;
typedef unsigned char   uint8;
typedef uint8           bool8;

string addrs[PAGE] = {};
void read_addrs();

int part_one() {
    string* str = addrs;
    int count = 0;
    while(str->start) {
        bool8 in_hypernet = 0;
        bool8 valid = 0;
        bool8 detected = 1;
        for (const char* c = str->start; c < str->end-3; c++) {
            if (c[0] == c[3] && c[1] == c[2] && c[0] != c[1]) {
                valid = 1 && !in_hypernet && detected;
                detected = valid;
            }
            if (*c == '[') in_hypernet = 1;
            if (*c == ']') in_hypernet = 0;
        }
        count += valid;
        str++;
    }
    return count;
}

bool8 cstr_in_str(char* a, string b) {
    bool8 in_hypernet = 0;
    for (const char* c = b.start-2; c < b.end; c++) {
        if (*c == '[') in_hypernet = 1;
        if (*c == ']') in_hypernet = 0;
        if (in_hypernet && c[0] == a[0] && c[1] == a[1] && c[2] == a[2]) {
            return 1;
        }
    }
    return 0;
}

int part_two() {
    string* str = addrs;
    int count = 0;
    while(str->start) {
        bool8 in_hypernet = 0;
        bool8 valid = 0;
        char bab[3] = {};
        for (const char* c = str->start; c < str->end-2; c++) {
            if (c[0] == c[2] && c[0] != c[1] && !in_hypernet) {
                bab[0] = c[1];
                bab[1] = c[0];
                bab[2] = c[1];
                valid = cstr_in_str(bab, *str) || valid;
            }
            if (*c == '[') in_hypernet = 1;
            if (*c == ']') in_hypernet = 0;
        }
        count += valid;
        str++;
    }
    return count;
}


int main() {
    read_addrs();
    printf("%d addresses support TLS\n", part_one());
    printf("%d addresses support SSL\n", part_two());
}

void read_addrs() {
    const char* c = day7_input;
    int ptr = 0;
    addrs[ptr].start = c;

    while (*c++) {
        if (*c == '\n') {
            addrs[ptr++].end = c;
            addrs[ptr].start = ++c;
        }
    }
    addrs[ptr++].end = c-1;

}
