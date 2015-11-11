#include "Block.h"
#include "string.h"

void block_init( Block* P ){
    int i;
    P->name[0] = '\0';

    memset(P->tab_harga,0,sizeof(P->tab_harga));
    memset(P->tab_denda,0,sizeof(P->tab_denda));

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
	fscanf(stream, "%d", &block->type);

	if( block->type == TANAH ){
		fscanf(stream, "%s", &block->name );
		for( i = 0; i < 5; ++ i )
			fscanf(stream, "%d", &block->tab_harga + i);

		for( i = 0; i < 5; ++ i )
			fscanf(stream, "%d", &block->tab_denda + i);
	}
	if( block->type == PARIWISATA ){
		fscanf(stream, "%s", &block->name );
        fscanf(stream, "%d", &block->tab_harga + 0);
        fscanf(stream, "%d", &block->tab_denda + 0);
	}
}

