#ifndef PLAYER_H
#define PLAYER_H
#include "Chance.h"
#include "stdlib.h"

// jika bank maka Player *player adalah NULL


typedef struct TPlayer *PlayerAddress;
typedef struct TPlayer {
	char name[5];
	int money;
	int revolution_count;
	Chance save_chance;
	boolean world_cup_holder;
}Player;

void player_init(PlayerAddress *Padd);

void player_alokasi(PlayerAddress *Padd);

void player_dealokasi(PlayerAddress *Padd);

#endif
