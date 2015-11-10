#ifndef PLAYER_H
#define PLAYER_H

#include "Block.h"
// jika bank maka Player *player adalah NULL

typedef struct TPlayer *PlayerAddress;
typedef struct TPlayer {
	char name[5];
	int revolution_count;
	struct Block* cblock;
	PlayerAddress next;
} Player;

#endif
