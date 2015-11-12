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

    switch( block->type ){
    case TANAH:
		fscanf(stream, "%s", &block->name );
		for( i = 0; i < 5; ++ i )
			fscanf(stream, "%d", block->tab_harga + i);

		for( i = 0; i < 5; ++ i )
			fscanf(stream, "%d", block->tab_denda + i);
        break;
    case PARIWISATA:
		fscanf(stream, "%s", &block->name );
        fscanf(stream, "%d", &block->tab_harga + 0);
        fscanf(stream, "%d", &block->tab_denda + 0);
        break;
    case KESEMPATAN:
        strcpy(block->name,"Kesemp.");
        break;
    case PAJAK:
        strcpy(block->name,"Pajak");
        break;
    case START:
        strcpy(block->name,"Start");
        break;
    case KELILING_DUNIA:
        strcpy(block->name,"KelDun");
        break;
    case BONUS:
        strcpy(block->name,"Bonus");
        break;
    case DESERTED_ISLAND:
        strcpy(block->name,"Deser.Isl.");
        break;
    case WORLD_CUP:
        strcpy(block->name,"World Cup");
        break;
    }
}
