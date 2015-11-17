#ifndef BLOCK_H
#define BLOCK_H

#include "listlinier.h"
#include "boolean.h"
#include "stdio.h"
#include "stdlib.h"
#include "Player.h"
#include "string.h"




typedef enum {
	TANAH, //0
	KESEMPATAN,//1
	PAJAK, //2
	START, //3
	KELILING_DUNIA,//4
	BONUS, // 5
	PARIWISATA, //6
	DESERTED_ISLAND, //7
	WORLD_CUP//8
} BlockType;


typedef struct TBlock *BlockAddress;
typedef struct TBlock{
	char name[255];
	int tab_harga[5];
	int tab_denda[5];
	Player* owner;
	List list_player;
	BlockType type;
	int id;
	int level;
	int multiplier;
	BlockAddress group_next;
	BlockAddress group_prev;

	BlockAddress line_prev;
	BlockAddress line_next;

	BlockAddress map_next;
} Block;

#define iterate_map(P,Begin,End,todo)\
	P = Begin;\
	do {\
		todo;\
		P = P->map_next;\
	} while( P != End );\

#define iterate_group(P,Begin, End, todo)\
	P = Begin;\
	do {\
		todo;\
		P = P->group_next;\
	} while( P != End )\


#define iterate_line(P,Begin, End, todo)\
	P = Begin;\
	do {\
		todo;\
		P = P->line_next;\
	} while( P != End )\

#define find_first_in_group(P,Current)\
	P = Current;\
	while( P->group_prev != NULL ) P = P->group_prev;


#define find_first_in_line(P,Current)\
	P = Current;\
	while( P->line_prev != NULL ) P = P->line_prev;


#define find_last_in_line(P,Current)\
	P = Current;\
	while( P->line_next != NULL ) P = P->line_next;

void block_init( BlockAddress );

void block_load_from_bin( FILE*, BlockAddress );

int block_cost( Block b );

#endif
