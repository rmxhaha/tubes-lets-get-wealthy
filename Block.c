#include "Block.h"

void block_init( BlockAddress P ){
	P->name = "";
	memset(&P->tab_harga, 0, sizeof(P->tab_harga));
	memset(&P->tab_denda, 0, sizeof(P->tab_denda));
	
	P->owner = NULL;
	P->type = TANAH;
	P->id = -1;
	P->level = 0;
	P->multiplier = 1;
	P->group_next = NULL;
	P->group_prev = NULL;

	P->line_next = NULL;
	P->line_prev = NULL;

	P->map_next = NULL;
}

void block_load_from_bin( FILE* stream, BlockAddress block ){
	int i = 0;
	fscanf(stream, "%d", block->type);
	
	if( block->type == TANAH ){
		fscanf(stream, "%s", block->name );
		for( i = 0; i < 5; ++ i ) 
			fscanf(stream, "%d", block->tab_harga + i);

		for( i = 0; i < 5; ++ i ) 
			fscanf(stream, "%d", block->tab_denda + i);
	}
}

