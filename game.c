#include "Player.h"
#include "Block.h"
#include "MonopolyMap.h"
#include "stdio.h"



int main(){
	MonopolyMap map;
	Block block;
	FILE *f = fopen("mapdata.txt","r");

    map = load_map(f);

    BlockAddress addr = map.first;
    addr = map.first->map_next;

    do {
//        printf("%d\n", addr->id );
        printf("ad : %s\n", addr->name);
        addr = addr->group_next;
    }while( addr != NULL );

    fclose(f);

    print_map(map);

//	save( cplayer, map );



	return 0;
}
