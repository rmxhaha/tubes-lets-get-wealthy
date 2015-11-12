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
} MonopolyMap;

MonopolyMap load_map(FILE*);

void print_map(MonopolyMap);

#endif
