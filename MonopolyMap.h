#ifndef MONOPOLY_MAP_H
#define MONOPOLY_MAP_H

#include "string.h"
#include "stdio.h"
#include "Block.h"
#include "Player.h"

typedef struct TBlock *BlockAddress;
typedef struct TPlayer *PlayerAddress;

typedef struct {
	BlockAddress first;
	List ListPlayer; // giliran (List of Player)
	List ListOffered; // list barang lelang (List of BlockAddr)
	BlockAddress world_cup_city;
	List ListBlackout; // List of BlockAddr
	Address cplayer;
} MonopolyMap;

MonopolyMap load_map(FILE*);

void print_map(MonopolyMap);

void save_game(FILE*,MonopolyMap map, boolean reroll, boolean upgraded);

void load_game(FILE*,MonopolyMap* map, boolean* reroll, boolean *upgraded);

#endif
