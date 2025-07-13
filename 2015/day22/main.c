// ====================================================================
//  $File: main.c $
//  $Date: 13-07-2025 @ 16-38-25 $
//  $Revision: 0.0.0 $
//  $Creator: aeternatrix $
//  $Notice: (C) Copyright 2025 by aeternatrix. All Rights Reserved. $
// ===================================================================

#include <stdio.h>
#include <stdlib.h>

typedef enum { NOTHING, MAGIC_MISSILE, DRAIN, SHIELD, POSION, RECHARGE } action_e;

#define PAGE 4096
#define EASY 0
#define HARD 1

typedef struct { int p_hp, p_mp, p_shield; int b_hp, b_dmg; int tr_shield, tr_poison, tr_recharge; int used_mp; }
state_t;

state_t initial = { 50, 500, 0, 51, 9 };

typedef struct node { state_t state; int g; int f; struct node* parent; }
node;

typedef struct { node** data; int size; }
pqueue;

node* astar(state_t start, int diff);
state_t perform_action(action_e action, state_t *current, int pt);
node* pop(pqueue* pq);
void push(pqueue* pq, node* n);
node* create_node(state_t state, int g, int f, node* parent);

// The prompt is, I feel, way too long to copy-paste here.
int part_one() {
    node* path = astar(initial, EASY);
    if (!path) return -1;
    return path[0].state.used_mp;
}

/*
 * On the next run through the game, you increase the difficulty to hard.
 * 
 * At the start of each player turn (before any other effects apply), you lose `1` hit point. If this brings you to or below `0` hit points, you lose.
 * 
 * With the same starting stats for you and the boss, what is the least amount of mana you can spend and still win the fight?
 */
int part_two() {
    node* path = astar(initial, HARD);
    if (!path) return -1;
    return path[0].state.used_mp;
}

int main() {
    printf("The least amount of mana you can spend is %d.\n", part_one());
    printf("The least amount of mana you can spend is %d on hard mode.\n", part_two());
}


int max(int a, int b) { return a > b ? a : b; }

state_t
perform_action(action_e action, state_t *current, int pt) {
    state_t next = *current;
    if (next.tr_poison) {
        next.b_hp -= 3;
        next.tr_poison--;
        if (next.b_hp <= 0) return next;
    }
    if (next.tr_recharge) { next.tr_recharge--; next.p_mp += 101; }

    if (pt) {
        switch (action) {
            case MAGIC_MISSILE:
                next.b_hp -= 4;
                next.p_mp -= 53;
                next.used_mp += 53;
                break;
            case DRAIN:
                next.b_hp -= 2;
                next.p_hp += 2;
                next.p_mp -= 73;
                next.used_mp += 73;
                break;
            case SHIELD:
                next.p_shield = 7;
                next.tr_shield = 6;
                next.p_mp -= 113;
                next.used_mp += 113;
                break;
            case POSION:
                next.tr_poison = 6;
                next.p_mp -= 173;
                next.used_mp += 173;
                break;
            case RECHARGE:
                next.tr_recharge = 5;
                next.p_mp -= 229;
                next.used_mp += 229;
                break;
            default: break;
        }
    } else {
        int shield = next.tr_shield ? 7 : 0;
        next.p_hp -= max(1, next.b_dmg - shield);
    }
    if (next.tr_shield) { next.tr_shield--; }

    return next;
}

node*
astar(state_t start, int diff) {
    pqueue pq = {};
    pq.data = calloc(128*PAGE, sizeof(state_t*));
    push(&pq, create_node(start, 0, start.used_mp, 0));

    while(pq.size) {
        node* n = pop(&pq);
        state_t curr = n->state;
        if (curr.b_hp <= 0) {
            free(pq.data);
            return n;
        }

        int nstep = n->g + 1;
        if (nstep % 2 == 1) {
            curr.p_hp-=diff;
            state_t next[5] = { 
                perform_action(MAGIC_MISSILE,   &curr, 1),
                perform_action(DRAIN,           &curr, 1),
                perform_action(SHIELD,          &curr, 1),
                perform_action(POSION,          &curr, 1),
                perform_action(RECHARGE,        &curr, 1),
            };
            for (int i = 0; i < 5; i++) {
                state_t next_state = next[i];
                if (next_state.p_hp <= 0 || next_state.p_mp < 0) continue;
                push(&pq, create_node(next_state, nstep, next_state.used_mp, n));
            }
        } else {
            state_t next_state = perform_action(NOTHING,   &curr, 0);
            if (next_state.p_hp <= 0 || next_state.p_mp < 0) continue;
            push(&pq, create_node(next_state, nstep, next_state.used_mp, n));
        }
    }

    free(pq.data);
    return 0;
}

node*
create_node(state_t state, int g, int f, node* parent) {
    node*n = malloc(sizeof(node));
    n->state = state;
    n->f = f;
    n->g = g;
    n->parent = parent;
    return n;
}

void
push(pqueue* pq, node* n) {
    int i = pq->size++;
    while(i) {
        int p = (i - 1) / 2;
        if (pq->data[p]->f <= n->f) break;
        pq->data[i] = pq->data[p];
        i = p;
    }
    pq->data[i] = n;
}

node*
pop(pqueue* pq) {
    node* ret = pq->data[0];
    node* last = pq->data[--pq->size];
    int i = 0;

    while(i*2 + 1 < pq->size) {
        int a = i * 2 + 1, b = i * 2 + 2, c = a;
        if (b < pq->size && pq->data[b]->f < pq->data[a]->f) c = b;
        if (last->f <= pq->data[c]->f) break;
        pq->data[i] = pq->data[c];
        i=c;
    }
    pq->data[i] = last;
    return ret;
}
