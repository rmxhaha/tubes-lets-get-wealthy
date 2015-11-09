#ifndef MONOPOLY_MAP_H
#define MONOPOLY_MAP_H

#include "Block.h"

typedef struct {
	BlockAddress first;
} MonopolyMap;

void loadMap(FILE*);


#endif