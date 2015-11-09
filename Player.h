#ifndef PLAYER_H
#define PLAYER_H

// jika bank maka Player *player adalah NULL

typedef struct TPlayer *PlayerAddress;
typedef struct TPlayer {
	char name[5];
	int money;
	int revolution_count;
	BlockAddress cblock;
	PlayerAddress next;
} Player;

#endif
