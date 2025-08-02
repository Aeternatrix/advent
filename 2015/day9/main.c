// ====================================================================
//  $File: main.c $
//  $Date: 03-07-2025 @ 00-46-40 $
//  $Revision: 0.0.0 $
//  $Creator: aeternatrix $
//  $Notice: (C) Copyright 2025 by aeternatrix. All Rights Reserved. $
// ===================================================================

#include <stdio.h>

#include "input.h"

#define LOCS 10

typedef struct { const char* start, *end; } location;
location vertex[LOCS] = {};
int graph[LOCS * LOCS] = {};

void read_into_graph();
int ts(int mask, int pos, int* arr, int sz);
int min(int a, int b) { return a < b ? a : b; }

/*
 * Every year, Santa manages to deliver all of his presents in a single night.
 * 
 * This year, however, he has some new locations to visit; his elves have provided him the distances between every pair of locations. He can start and end at any two (different) locations he wants, but he must visit each location exactly once. What is the shortest distance he can travel to achieve this?
 * 
 * For example, given the following distances:
 * 
 * - `London to Dublin = 464`
 * - `London to Belfast = 518`
 * - `Dublin to Belfast = 141`
 * The possible routes are therefore:
 * 
 * - `Dublin -> London -> Belfast = 982`
 * - `London -> Dublin -> Belfast = 605`
 * - `London -> Belfast -> Dublin = 659`
 * - `Dublin -> Belfast -> London = 659`
 * - `Belfast -> Dublin -> London = 605`
 * - `Belfast -> London -> Dublin = 982`
 * The shortest of these is `London -> Dublin -> Belfast = 605`, and so the answer is `605` in this example.
 * 
 * What is the distance of the shortest route?
 */
int part_one(int sz) {
    return ts(0, 0, graph, sz);
}

/*
 * The next year, just to show off, Santa decides to take the route with the longest distance instead.
 * 
 * He can still start and end at any two (different) locations he wants, and he still must visit each location exactly once.
 * 
 * For example, given the distances above, the longest route would be 982 via (for example) Dublin -> London -> Belfast.
 * 
 * What is the distance of the longest route?
 */
int part_two(int sz) {
    int solution[LOCS*LOCS] = {};
    for (int i=0;i<LOCS*LOCS;i++) solution[i] = graph[i] * -1;
    int longest = 0;
    for (int i=0;i<sz;i++) {
        longest = min(longest, ts(1 << i, i, solution, sz));
    }
    return -longest;
}


int main() {
    read_into_graph();
    int sz = 0;
    location* a = vertex;
    while ((*a++).start) sz++;
    printf("The shortest distance is: %d.\n", part_one(sz));
    printf("The longest distance is: %d.\n", part_two(sz));
    return 0;
}

int
m_strcmp(const char* a, int alen, const char* b, int blen) {
    if (alen != blen) return 0;
    for (int itr=0;itr < alen; itr++) if (a[itr] != b[itr]) return 0;
    return 1;
}


int
get_location_id(location loc) {
    for (int i = 0; i < LOCS; i++) {
        if (!vertex[i].start) return LOCS;
        if (m_strcmp(vertex[i].start, vertex[i].end-vertex[i].start, loc.start, loc.end - loc.start))
            return i;
    }
    return LOCS;
}

void
read_into_graph() {
    for (int i=0;i<LOCS*LOCS;i++) graph[i] = -1;
    char c;
    int rec;
    int vert = 0;
    int dist = 0;
    int itr = 0;
    location a = {};
    location b = {};
    do {
        c = input[itr];

        if (c <= 'Z' && c >= 'A') {
            if (input[itr-1] <= 'z' && input[itr-1] >= 'a') {} // do nothing if mid-word
            else if (a.start) b.start = &input[itr];
            else a.start = &input[itr];
            rec = 1;
        }
        if (rec && c == ' ') {
            rec = 0;
            if (a.end) b.end = &input[itr];
            else a.end = &input[itr];
        }
        if (c <= '9' && c >= '0') {
            dist = dist * 10 + c - '0';
        }

        if (c == '\n') {
            int aid = get_location_id(a);
            int bid = get_location_id(b);

            if (aid == LOCS) { vertex[vert] = a; aid = vert++; }
            if (bid == LOCS) { vertex[vert] = b; bid = vert++; }

            graph[aid + bid * LOCS] = dist;
            graph[bid + aid * LOCS] = dist;
            graph[aid + aid * LOCS] = 0;
            graph[bid + bid * LOCS] = 0;

            a = (location){};
            b = (location){};
            dist = 0;
        }

        itr++;
    } while(c);
}

int
ts(int mask, int pos, int* arr, int sz) {
    if (mask == (1 << sz) - 1) {
        return 0;
    }

    int dist = 0x7FFFFFFF;

    for (int i = 0; i < sz; i++) {
        if ((mask & (1 << i)) == 0) {
            dist = min(dist, arr[pos * LOCS + i] + ts((mask | (1 << i)), i, arr, sz));
        }
    }

    return dist;
}
