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
    do {
//        printf("%d\n", addr->id );
        printf("ad : %d\n", addr->type);
        addr = addr->map_next;
    }while( addr != map.first );

    fclose(f);

//	save( cplayer, map );



	return 0;
}
