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
	List ListTurn; // giliran
	List ListOffered; // list barang lelang
} MonopolyMap;

MonopolyMap load_map(FILE*);

void print_map(MonopolyMap);

void print_leaderboard(MonopolyMap);

#endif
