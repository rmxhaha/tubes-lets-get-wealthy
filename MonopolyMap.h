#ifndef MONOPOLY_MAP_H
#define MONOPOLY_MAP_H

#include "Block.h"

typedef struct {
	BlockAddress first;
} MonopolyMap;

MonopolyMap load_map(FILE*);


#endif