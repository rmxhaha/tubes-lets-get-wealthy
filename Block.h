#ifndef BLOCK_H
#define BLOCK_H

#include "Player.h"
#include "List.h"
#include "boolean.h"

typedef enum {
	TANAH,
	KESEMPATAN,
	PAJAK,
	START,
	KELILING_DUNIA
} BlockType;

typedef struct  {
	char name[255];
	int tab_harga[5];
	int tab_denda[5];
	boolean tab_own[5];
	Player *owner;
	List list_player;
	BlockType type;
	int id;
	int multiplier;
	int revolution_count;
	Block *group_next;
	Block *group_prev;

	Block *line_prev;
	Block *line_next;

	Block *map_next;
} Block;


void block_init( Block* );

Block block_load_from_bin( char * );

char* block_convert_to_bin( Block );




#endif
