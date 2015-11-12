#ifndef PLAYER_H
#define PLAYER_H
#include "Chance.h"

// jika bank maka Player *player adalah NULL


typedef struct TPlayer *PlayerAddress;
typedef struct TPlayer {
	char name[5];
	int money;
	int revolution_count;
	Chance save_chance;
	PlayerAddress next;
} Player;

void player_init( PlayerAddress );

void player_alokasi( PlayerAddress );

#endif
