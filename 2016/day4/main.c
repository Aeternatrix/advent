// ====================================================================
//  $File: main.c $
//  $Date: 06-08-2025 @ 06-21-41 $
//  $Revision: 0.0.0 $
//  $Creator: aeternatrix $
//  $Notice: (C) Copyright 2025 by aeternatrix. All Rights Reserved. $
// ===================================================================

#include <stdio.h>

#include "day4_input.h"
//	const char day4_input[] = {
//	    "aaaaa-bbb-z-y-x-123[abxyz]\n"
//	    "a-b-c-d-e-f-g-h-987[abcde]\n"
//	    "not-a-real-room-404[oarel]\n"
//	    "totally-real-room-200[decoy]"
//	};

#define PAGE 4096
#define ALPHA 26
#define CHK_LN 5


typedef struct { const char* start, *end; } string;
typedef struct { string encrypted, checksum; } room;
typedef struct { int part_one, part_two; } answers;
typedef unsigned char   byte;
typedef byte            bool8;

room rooms[PAGE] = {};

void read_rooms();
int m_strlen(string s) { return s.end - s.start; }
bool8 is_num(char c) {return c <= '9' && c >= '0'; }
bool8 str_contains(char* a, int alen, char* b, int blen);

answers
challenge() {
    answers ans = {};
    for (room* r = rooms; r->encrypted.start; r++) {
        int str_len = m_strlen(r->encrypted);
        int id = 0;

        int counts[ALPHA] = {};
        int check[CHK_LN] = {-1, -1, -1, -1, -1};

        for (const char* c = r->encrypted.start; c < r->encrypted.end; c++) {
            int count = 0;
            if (*c == '-') continue;
            if (is_num(*c)) {
                id = id * 10 + *c - '0';
                continue;
            }
            counts[*c - 'a']++;
        }

        int ptr=0;
        for (int i = 0; i < ALPHA; i++) {
            if (!counts[i]) continue;
            int tmp = 0, new_val = i;

            for (int it=0;it<CHK_LN;it++) {
                if (check[it] == -1) {
                    check[it] = new_val;
                    break;
                } else if (counts[new_val] == counts[check[it]]) {
                    if (new_val < check[it]) {
                        tmp = check[it];
                        check[it] = new_val;
                        new_val = tmp;
                    }
                } else if (counts[new_val] > counts[check[it]]) {
                    tmp = check[it];
                    check[it] = new_val;
                    new_val = tmp;
                }
            }
        }
        bool8 valid = 1;
        for (int i=0; i<CHK_LN && valid;i++) valid = r->checksum.start[i] == check[i] + 'a';
        if (!valid) continue;
        ans.part_one+=id;
        if (ans.part_two) continue;

        char buf[128] = {};
        int i = 0;
        for (; i < str_len; i++) {
            char c=r->encrypted.start[i];
            if (c == '-') buf[i] = ' ';
            else if (is_num(c)) continue;
            else buf[i] = ((c - 'a' + id) % 26) + 'a';
        }
        char term[5] = "north";
        if (str_contains(buf, i, term, sizeof(term))) {
            ans.part_two = id;
        }
    }
    return ans;
}

int main() {
    read_rooms();
    answers ans = challenge();
    printf("The sector IDs of real rooms sum to %d\n", ans.part_one);
    printf("The sector ID of the North Pole storage room is %d\n", ans.part_two);
}

void
read_rooms() {
    const char* c = day4_input;

    int ptr = 0;
    string* w = (string*)rooms;
    w->start = c;
    do {
        if (*c == '[' || *c == ']') {
            w->end = c;
            c++;
            if (*c == '\0') break;
            if (*c == '\n') c++;
            w++;
            w->start = c;
        }
    } while (*c++);
}

bool8
str_contains(char* a, int alen, char* b, int blen) {
    bool8 contained = 0;
    for (int i=0;i<alen-blen;i++) {
        if (a[i] == b[0]) {
            contained = 1;
            for (int it=0; contained && it < blen;it++) contained = a[i+it] == b[it];
            if (contained) return contained;
        }
    }
    return contained;
}

