// ====================================================================
//  $File: main.c $
//  $Date: 05-07-2025 @ 14-27-41 $
//  $Revision: 0.0.0 $
//  $Creator: aeternatrix $
//  $Notice: (C) Copyright 2025 by aeternatrix. All Rights Reserved. $
// ===================================================================

#include "input.h"
#include <stdio.h>

#define LOCS 10

typedef struct {
    const char* start, *end;
} whomst;

whomst vertex[LOCS] = {};
int graph[LOCS * LOCS] = {};

void read_into_graph();
int ts(int mask, int pos, int* arr, int sz);
int min(int a, int b);
int max(int a, int b);
/*
 * In years past, the holiday feast with your family hasn't gone so well. Not everyone gets along! This year, you resolve, will be different. You're going to find the optimal seating arrangement and avoid all those awkward conversations.
 * 
 * You start by writing up a list of everyone invited and the amount their happiness would increase or decrease if they were to find themselves sitting next to each other person. You have a circular table that will be just big enough to fit everyone comfortably, and so each person will have exactly two neighbors.
 * 
 * For example, suppose you have only four attendees planned, and you calculate their potential happiness as follows:
 * 
 * - `Alice would gain 54 happiness units by sitting next to Bob.`
 * - `Alice would lose 79 happiness units by sitting next to Carol.`
 * - `Alice would lose 2 happiness units by sitting next to David.`
 * - `Bob would gain 83 happiness units by sitting next to Alice.`
 * - `Bob would lose 7 happiness units by sitting next to Carol.`
 * - `Bob would lose 63 happiness units by sitting next to David.`
 * - `Carol would lose 62 happiness units by sitting next to Alice.`
 * - `Carol would gain 60 happiness units by sitting next to Bob.`
 * - `Carol would gain 55 happiness units by sitting next to David.`
 * - `David would gain 46 happiness units by sitting next to Alice.`
 * - `David would lose 7 happiness units by sitting next to Bob.`
 * - `David would gain 41 happiness units by sitting next to Carol.`
 * Then, if you seat Alice next to David, Alice would lose `2` happiness units (because David talks so much), but David would gain `46` happiness units (because Alice is such a good listener), for a total change of `44`.
 * 
 * If you continue around the table, you could then seat Bob next to Alice (Bob gains `83`, Alice gains `54`). Finally, seat Carol, who sits next to Bob (Carol gains `60`, Bob loses `7`) and David (Carol gains `55`, David gains `41`). The arrangement looks like this:
 * 
 * - `     +41 +46     `
 * - `+55   David    -2`
 * - `Carol       Alice`
 * - `+60    Bob    +54`
 * - `     -7  +83     `
 * After trying every other seating arrangement in this hypothetical scenario, you find that this one is the most optimal, with a total change in happiness of `330`.
 * 
 * What is the total change in happiness for the optimal seating arrangement of the actual guest list?
 */
int part_one(int sz) {
    int solution[LOCS*LOCS] = {};
    for (int i=0;i<LOCS*LOCS;i++) solution[i] = -1;

    for (int a = 0; a < sz; a++) {
        for (int b = 0; b < sz; b++) {
            solution[a*LOCS + b] = graph[a*LOCS + b] + graph[b*LOCS + a];
            solution[b*LOCS + a] = solution[a*LOCS + b];
        }
    }
    for (int i=0;i<LOCS*LOCS;i++) solution[i] *= -1;
    return -ts(1, 0, solution, sz);
}

int part_two(int sz) {
    int solution[LOCS*LOCS] = {};
    for (int i=0;i<LOCS*LOCS;i++) solution[i] = -1;

    // Add myself
    for (int i = 0; i<LOCS; i++) {
        graph[i*LOCS+sz] = 0;
        graph[sz*LOCS+i] = 0;
    }

    for (int a = 0; a <= sz; a++) {
        for (int b = 0; b <= sz; b++) {
            solution[a*LOCS + b] = graph[a*LOCS + b] + graph[b*LOCS + a];
            solution[b*LOCS + a] = solution[a*LOCS + b];
        }
    }
    for (int i=0;i<LOCS*LOCS;i++) solution[i] *= -1;
    return -ts(1, 0, solution, sz+1);
}

int main() {
    read_into_graph();
    int sz = 0;
    whomst* a = vertex;
    while ((*a++).start) sz++;
    printf("The total change in happiness for the optimal seating is: %d.\n", part_one(sz));
    printf("The total change in happiness for the optimal seating (inlcuding myself) is: %d.\n", part_two(sz));
}



int ts(int mask, int pos, int* arr, int sz) {
    if (mask == (1 << sz) - 1) {
        return arr[pos*LOCS];
    }

    int dist = 0x7FFFFFFF;

    for (int i = 0; i < sz; i++) {
        if ((mask & (1 << i)) == 0) {
            dist = min(dist, arr[pos * LOCS + i] + ts((mask | (1 << i)), i, arr, sz));
        }
    }

    return dist;

}

int
m_strcmp(const char* a, int alen, const char* b, int blen) {
    if (alen != blen) return 0;
    for (int itr=0;itr < alen; itr++) if (a[itr] != b[itr]) return 0;
    return 1;
}


int
get_whomst_id(whomst loc) {
    for (int i = 0; i < LOCS*LOCS; i++) {
        if (!vertex[i].start) return LOCS;
        if (m_strcmp(vertex[i].start, vertex[i].end-vertex[i].start, loc.start, loc.end - loc.start))
            return i;
    }
    return LOCS;
}

void
read_into_graph() {
    for (int i=0;i<LOCS*LOCS;i++) graph[i] = -1;
    const char* c = input;
    int rec;
    int vert = 0;
    int happiness = 0;
    int neg = 1;
    whomst a = {};
    whomst b = {};
    do {
        if (c[0] <= 'Z' && c[0] >= 'A') {
            if (c[-1] <= 'z' && c[-1] >= 'a') {} // do nothing if mid-word
            else if (a.start) b.start = c;
            else a.start = c;
            rec = 1;
        }
        if (rec && (c[0] == ' ' || c[0] == '.')) {
            rec = 0;
            if (a.end) b.end = c;
            else a.end = c;
        }
        if (c[0] == 'l' && c[1] == 'o' && c[2] == 's' && c[3] == 'e') {
            neg = -1;
        }
        if (c[0] <= '9' && c[0] >= '0') {
            happiness = happiness * 10 + c[0] - '0';
        }

        if (c[0] == '\n' || c[0] == '\0') {
            int aid = get_whomst_id(a);
            int bid = get_whomst_id(b);

            if (aid == LOCS) { vertex[vert] = a; aid = vert++; }
            if (bid == LOCS) { vertex[vert] = b; bid = vert++; }

            graph[aid + bid * LOCS] = happiness * neg;
            graph[aid + aid * LOCS] = 0;
            graph[bid + bid * LOCS] = 0;

            a = (whomst){};
            b = (whomst){};
            happiness = 0;
            neg = 1;
        }

    } while(*c++);
}

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}
