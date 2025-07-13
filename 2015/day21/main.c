// ====================================================================
//  $File: main.c $
//  $Date: 13-07-2025 @ 13-27-45 $
//  $Revision: 0.0.0 $
//  $Creator: aeternatrix $
//  $Notice: (C) Copyright 2025 by aeternatrix. All Rights Reserved. $
// ===================================================================

#include <stdio.h>
typedef struct { int hp, dmg, arm; } entity_t;

entity_t input = {100, 8, 2};

typedef struct { int cost, damage, arm; float value; } item_t;
typedef struct { item_t weapons[5], armours[5], rings[6]; } shop_t;

shop_t shop = {{{   8, 4, 0 },{  10, 5, 0 },{  25, 6, 0 },{  40, 7, 0 },{  74, 8, 0 }},
               {{  13, 0, 1 },{  31, 0, 2 },{  53, 0, 3 },{  75, 0, 4 },{ 102, 0, 5 }},
               {{  25, 1, 0 },{  50, 2, 0 },{ 100, 3, 0 },{  20, 0, 1 },{  40, 0, 2 },{  80, 0, 3 }}};


int killtime(entity_t *a, entity_t *b);
int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }
int min_not0(int a, int b) { return (a == 0 ? b : min(a, b)); }

int damage[10] = {};
int armour[11] = {};
void compute(int (*fn) (int, int));
/*
 * Little Henry Case got a new video game for Christmas. It's an RPG, and he's stuck on a boss. He needs to know what equipment to buy at the shop. He hands you the controller.
 * 
 * In this game, the player (you) and the enemy (the boss) take turns attacking. The player always goes first. Each attack reduces the opponent's hit points by at least `1`. The first character at or below `0` hit points loses.
 * 
 * Damage dealt by an attacker each turn is equal to the attacker's damage score minus the defender's armor score. An attacker always does at least `1` damage. So, if the attacker has a damage score of `8`, and the defender has an armor score of `3`, the defender loses `5` hit points. If the defender had an armor score of `300`, the defender would still lose `1` hit point.
 * 
 * Your damage score and armor score both start at zero. They can be increased by buying items in exchange for gold. You start with no items and have as much gold as you need. Your total damage or armor is equal to the sum of those stats from all of your items. You have `100 hit points`.
 * 
 * Here is what the item shop is selling:
 * 
 * - Weapons:    Cost  Damage  Armor
 * - Dagger        8     4       0
 * - Shortsword   10     5       0
 * - Warhammer    25     6       0
 * - Longsword    40     7       0
 * - Greataxe     74     8       0
 * - 
 * - Armor:      Cost  Damage  Armor
 * - Leather      13     0       1
 * - Chainmail    31     0       2
 * - Splintmail   53     0       3
 * - Bandedmail   75     0       4
 * - Platemail   102     0       5
 * - 
 * - Rings:      Cost  Damage  Armor
 * - Damage +1    25     1       0
 * - Damage +2    50     2       0
 * - Damage +3   100     3       0
 * - Defense +1   20     0       1
 * - Defense +2   40     0       2
 * - Defense +3   80     0       3
 * You must buy exactly one weapon; no dual-wielding. Armor is optional, but you can't use more than one. You can buy 0-2 rings (at most one for each hand). You must use any items you buy. The shop only has one of each item, so you can't buy, for example, two rings of Damage +3.
 * 
 * For example, suppose you have `8` hit points, `5` damage, and `5` armor, and that the boss has `12` hit points, `7` damage, and `2` armor:
 * 
 * - The player deals `5-2 = 3` damage; the boss goes down to 9 hit points.
 * - The boss deals `7-5 = 2` damage; the player goes down to 6 hit points.
 * - The player deals `5-2 = 3` damage; the boss goes down to 6 hit points.
 * - The boss deals `7-5 = 2` damage; the player goes down to 4 hit points.
 * - The player deals `5-2 = 3` damage; the boss goes down to 3 hit points.
 * - The boss deals `7-5 = 2` damage; the player goes down to 2 hit points.
 * - The player deals `5-2 = 3` damage; the boss goes down to 0 hit points.
 * In this scenario, the player wins! (Barely.)
 * 
 * You have 100 hit points. The boss's actual stats are in your puzzle input. What is the least amount of gold you can spend and still win the fight?
 * 
 * 
 */
int part_one() {
    compute(min_not0);
    entity_t player = {100, 0, 0};

    int min_gold = 0;

    for (int dmg = 4; dmg <= 13; dmg++) {
        player.dmg = dmg;
        for (int arm = 0; arm <= 10; arm++) {
            player.arm = arm;
            int bosswintime = killtime(&input, &player);
            int playerwintime = killtime(&player, &input);
            if (playerwintime <= bosswintime) {
                min_gold = min_not0(min_gold, damage[dmg-4] + armour[arm]);
            }
        }
    }
    return min_gold;
}

/*
 * Turns out the shopkeeper is working with the boss, and can persuade you to buy whatever items he wants. The other rules still apply, and he still only has one of each item.
 * 
 * What is the most amount of gold you can spend and still lose the fight?
 */
int part_two() {
    compute(max);
    entity_t player = {100, 0, 0};

    int max_gold = 0;

    for (int dmg = 4; dmg <= 13; dmg++) {
        player.dmg = dmg;
        for (int arm = 0; arm <= 10; arm++) {
            player.arm = arm;
            int bosswintime = killtime(&input, &player);
            int playerwintime = killtime(&player, &input);
            if (playerwintime > bosswintime) {
                max_gold = max(max_gold, damage[dmg-4] + armour[arm]);
            }
        }
    }
    return max_gold;
}

int main() {
    printf("The least amount of gold you can spend and still win is %d.\n", part_one());
    printf("The most amount of gold you can spend and still lose is %d.\n", part_two());
}

// Just for readability of compute()
void update(item_t item, int cost, int didx, int table[], int (*fn)(int, int)) {
    int c = cost + item.cost;
    int i = didx + item.damage + item.arm;
    table[i] = fn(table[i], c);
}

void compute(int (*fn) (int, int)) {
    for (int i = 0; i < 10; i++) damage[i] = 0;
    for (int i = 0; i < 11; i++) armour[i] = 0;

    for (int weap=0; weap < 5; weap++) {
        item_t weapon = shop.weapons[weap];
        int wpn_dmg = weapon.damage - 4;
        damage[wpn_dmg] = fn(damage[wpn_dmg], weapon.cost);

        for (int ring1 = 0; ring1 < 3; ring1++) {
            item_t r1 = shop.rings[ring1];
            update(r1, weapon.cost, wpn_dmg, damage, fn);

            for (int ring2 = 0; ring2 < 3; ring2++) {
                if (ring1 == ring2) continue;
                item_t r2 = shop.rings[ring2];
                update(r2, weapon.cost + r1.cost, wpn_dmg + r1.damage, damage, fn);
            }
        }
    }

    for (int arm = 0; arm < 5; arm++) {
        item_t ar = shop.armours[arm];
        armour[ar.arm] = fn(armour[ar.arm], ar.cost);

        for (int ring1 = 0; ring1 < 3; ring1++) {
            item_t r1 = shop.rings[ring1+3];
            update(r1, ar.cost, ar.arm, armour, fn);

            for (int ring2 = 0; ring2 < 3; ring2++) {
                if (ring1 == ring2) continue;
                item_t r2 = shop.rings[ring2+3];
                update(r2, ar.cost + r1.cost, ar.arm + r1.arm, armour, fn);
            }
        }
    }
}

int killtime(entity_t *a, entity_t *b) {
    float t;
    if (a->dmg == b->arm) return 0x7FFFFFFF;
    else t = (float)b->hp / (a->dmg - b->arm);
    if (t <= 0) return 0x7FFFFFFF;
    if (t == (int)t) return t;
    else return t+1;
}
