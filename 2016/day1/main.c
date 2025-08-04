// ====================================================================
//  $File: main.c $
//  $Date: 04-08-2025 @ 07-03-47 $
//  $Revision: 0.0.0 $
//  $Creator: aeternatrix $
//  $Notice: (C) Copyright 2025 by aeternatrix. All Rights Reserved. $
// ===================================================================

#include <stdio.h>

const char input[] = "L5, R1, L5, L1, R5, R1, R1, L4, L1, L3, R2, R4, L4, L1, L1, R2, R4, R3, L1, R4, L4, L5, L4, R4, L5, R1, R5, L2, R1, R3, L2, L4, L4, R1, L192, R5, R1, R4, L5, L4, R5, L1, L1, R48, R5, R5, L2, R4, R4, R1, R3, L1, L4, L5, R1, L4, L2, L5, R5, L2, R74, R4, L1, R188, R5, L4, L2, R5, R2, L4, R4, R3, R3, R2, R1, L3, L2, L5, L5, L2, L1, R1, R5, R4, L3, R5, L1, L3, R4, L1, L3, L2, R1, R3, R2, R5, L3, L1, L1, R5, L4, L5, R5, R2, L5, R2, L1, L5, L3, L5, L5, L1, R1, L4, L3, L1, R2, R5, L1, L3, R4, R5, L4, L1, R5, L1, R5, R5, R5, R2, R1, R2, L5, L5, L5, R4, L5, L4, L4, R5, L2, R1, R5, L1, L5, R4, L3, R4, L2, R3, R3, R3, L2, L2, L2, L1, L4, R3, L4, L2, R2, R5, L1, R2";
//	const char input[] = "R5, L5, R5, R3";

typedef enum { UNDEF, NORTH, EAST, SOUTH, WEST, LEFT, RIGHT } dir_t;
typedef struct { dir_t dir; int dist; } instruction_t;
typedef struct { int x, y; } vec2;
typedef vec2 point;
typedef struct { point a, b; } segment;
vec2* add(vec2* a, vec2* b) { a->x += b->x; a->y += b->y; return a; }
void read_instructions();
int intersect(segment a, segment b, point* out);

instruction_t instructions[256] = {};

int
part_one() {
    vec2 distance = {};
    dir_t dir_c = NORTH;

    instruction_t* curr = instructions;
    while(curr->dir != UNDEF) {
        switch(dir_c) {
            case NORTH:
                if (curr->dir == RIGHT) { dir_c = EAST; add(&distance, &(vec2){0,  curr->dist}); }
                if (curr->dir == LEFT)  { dir_c = WEST; add(&distance, &(vec2){0, -curr->dist}); }
                break;
            case EAST:
                if (curr->dir == RIGHT) { dir_c = SOUTH; add(&distance, &(vec2){-curr->dist, 0}); }
                if (curr->dir == LEFT)  { dir_c = NORTH; add(&distance, &(vec2){ curr->dist, 0}); }
                break;
            case SOUTH:
                if (curr->dir == RIGHT) { dir_c = WEST; add(&distance, &(vec2){0, -curr->dist}); }
                if (curr->dir == LEFT)  { dir_c = EAST; add(&distance, &(vec2){0,  curr->dist}); }
                break;
            case WEST:
                if (curr->dir == RIGHT) { dir_c = NORTH; add(&distance, &(vec2){ curr->dist, 0}); }
                if (curr->dir == LEFT)  { dir_c = SOUTH; add(&distance, &(vec2){-curr->dist, 0}); }
                break;

            default:
                return -1;
        }
        curr++;
    }
    int rt = distance.x + distance.y;
    if (rt < 0) rt *= -1;
    return rt;
}

int
part_two() {
    vec2 distance = {};
    point position = {};
    dir_t dir_c = NORTH;

    segment segments[256] = {};

    int ptr = 0;
    int rt = 0;

    instruction_t* curr = instructions;
    while(curr->dir != UNDEF) {
        segment seg_c = {distance};
        switch(dir_c) {
            case NORTH:
                if (curr->dir == RIGHT) { dir_c = EAST; add(&distance, &(vec2){0,  curr->dist}); }
                if (curr->dir == LEFT)  { dir_c = WEST; add(&distance, &(vec2){0, -curr->dist}); }
                break;
            case EAST:
                if (curr->dir == RIGHT) { dir_c = SOUTH; add(&distance, &(vec2){-curr->dist, 0}); }
                if (curr->dir == LEFT)  { dir_c = NORTH; add(&distance, &(vec2){ curr->dist, 0}); }
                break;
            case SOUTH:
                if (curr->dir == RIGHT) { dir_c = WEST; add(&distance, &(vec2){0, -curr->dist}); }
                if (curr->dir == LEFT)  { dir_c = EAST; add(&distance, &(vec2){0,  curr->dist}); }
                break;
            case WEST:
                if (curr->dir == RIGHT) { dir_c = NORTH; add(&distance, &(vec2){ curr->dist, 0}); }
                if (curr->dir == LEFT)  { dir_c = SOUTH; add(&distance, &(vec2){-curr->dist, 0}); }
                break;

            default:
                return -1;
        }
        seg_c.b = distance;
        for (int i = 0; i < ptr-1; i++) {
            if (intersect(seg_c, segments[i], &position)) {
                if (position.x < 0) position.x *= -1;
                if (position.y < 0) position.y *= -1;
                rt = position.x + position.y;
                return rt;
            }
        }
        segments[ptr++] = seg_c;
        curr++;
    }
    rt = distance.x + distance.y;
    if (rt < 0) rt *= -1;
    return rt;
}

int main() {
    read_instructions();
    printf("Easter Bunny HQ is %d blocks away.\n", part_one());
    printf("Easter Bunny HQ is actually %d blocks away.\n", part_two());
}

void
read_instructions() {
    const char* c = input;

    int dist = 0;
    dir_t dir = UNDEF;
    int ptr = 0;

    do {
        if (*c == 'R') dir = RIGHT;
        if (*c == 'L') dir = LEFT;
        if (*c <= '9' && *c >= '0') dist = dist * 10 + *c - '0';
        if (*c == ',' || *c == '\0') {
            instructions[ptr++] = (instruction_t){dir, dist};
            dir = UNDEF;
            dist = 0;
        }
    } while (*c++);

}

int intersect(segment a, segment b, point* out) {
    point A = a.a;
    point B = a.b;

    point C = b.a;
    point D = b.b;

    int AB_horz = A.y == B.y;
    int CD_horz = C.y == D.y;
    if (AB_horz == CD_horz) return 0; // parallel

    if (((A.x <= C.x && C.x <= B.x) || (B.x <= C.x && C.x <= A.x)) &&
        ((C.y <= A.y && A.y <= D.y) || (D.y <= A.y && A.y <= C.y))) {
        out->x = AB_horz ? C.x : A.x;
        out->y = AB_horz ? A.y : C.y;
        return 1;
    }

    out->x = 0;
    out->y = 0;
    return 0;
}
