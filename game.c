#include "Player.h"
#include "Block.h"
#include "MonopolyMap.h"
#include "infopetak.h"

int main(){
	MonopolyMap map;
	Block block;
	FILE *f = fopen("mapdata.txt","r");


    map = load_map(f);

    pick_jumlah_player(&map);

    printf("%s\n", ((Player*)Info(First(map.first->list_player)))->name);

    BlockAddress addr = map.first;
    addr = map.first->map_next;

    do {
//        printf("%d\n", addr->id );
        printf("ad : %s\n", addr->name);
        addr = addr->map_next;
    }while( addr != NULL );

    fclose(f);

    print_map(map);
    // print info petak: block_info_petak(map);
//	save( cplayer, map );



	return 0;
}
