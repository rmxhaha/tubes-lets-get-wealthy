#include "Block.h"

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
	CreateList(&P->list_player);
}

void block_load_from_bin( FILE* stream, BlockAddress block ){
	int i = 0;

	block_init(block);

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

int block_cost( Block b ){
/*    int i = 0;
    int cost = 0;

    for( i = 0; i <= b.level; ++ i )
        cost += b.tab_harga[i];

    return cost;
    */

    return b.tab_harga[b.level];
}

int block_upgrade_cost(){
    if( b.level == 4 )
        return b.tab_harga[4];
    else
        return b.tab_harga[b.level+1];
}
