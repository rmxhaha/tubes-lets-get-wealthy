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

typedef struct TBlock *BlockAddress;
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
	BlockAddress group_next;
	BlockAddress group_prev;

	BlockAddress line_prev;
	BlockAddress line_next;

	Block *map_next;
} Block;

#define iterate_group(P,Begin, End, todo)\
	P = Begin\
	do {\
		todo;\
	} while( P -> group_next != End )\

#define iterate_line(P,Begin, End, todo)\
	P = Begin\
	do {\
		todo;\
	} while( P -> line_next != End )\

#define find_first_in_group(P,Current)\
	P = Current\
	while( P->group_prev != NULL ) P = P->group_prev;
	

#define find_first_in_line(P,Current)\
	P = Current\
	while( P->line_prev != NULL ) P = P->line_prev;
	

	
	
void block_init( BlockAddress );

Block block_load_from_bin( char * );

char* block_convert_to_bin( Block );




#endif
