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
	List ListPlayer; // giliran
	List ListOffered; // list barang lelang
	BlockAddress world_cup_city;
	Address cplayer;
} MonopolyMap;

MonopolyMap load_map(FILE*);

void print_map(MonopolyMap);

void save_game(FILE*,MonopolyMap map, boolean roll);

void load_game(FILE*,MonopolyMap* map, boolean* roll);

#endif
