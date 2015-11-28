#ifndef PLAYER_H
#define PLAYER_H
#include "Chance.h"
#include "stdlib.h"
#include "boolean.h"

// jika bank maka Player *player adalah NULL


typedef struct TPlayer *PlayerAddress;
typedef struct TPlayer {
	char name[5];
	int money;
	int revolution_count;
	Chance save_chance;
	boolean world_cup_holder;
}Player;


#define MIN_PLAYER 2
#define MAX_PLAYER 4


void player_init(PlayerAddress *Padd);

void player_alokasi(PlayerAddress *Padd);

void player_dealokasi(PlayerAddress *Padd);

#endif
