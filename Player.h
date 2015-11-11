#ifndef PLAYER_H
#define PLAYER_H
#include "Chance.h"

#include "Block.h"
// jika bank maka Player *player adalah NULL

typedef struct TPlayer *PlayerAddress;
typedef struct TPlayer {
	char name[5];
	int money;
	int revolution_count;
	struct Block* cblock;
	Chance save_chance;
	BlockAddress cblock;
	PlayerAddress next;
} Player;

#endif
