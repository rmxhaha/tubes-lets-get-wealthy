#include "Player.h"
#include "Block.h"
#include "MonopolyMap.h"
#include "infopetak.h"
#include "gamelogic.h"
#include "worldtravel.h"

#define ifCommand(cmd)\
	if( strcmp( command, cmd) == 0 )

int main(){
	MonopolyMap map;
	Block block;
	Address cplayer; // current player
	char command[100];
	char tmp[100];
    PlayerAddress PA;

	int dadu1, dadu2;
	set_Random(); // init random

	FILE *f = fopen("mapdata.txt","r");
    map = load_map(f);
    fclose(f);

    pick_jumlah_player(&map);
	cplayer = First(map.ListPlayer);
	// repeat until game is won
	do {
        PA = Info(cplayer);

        printf("> ");
		scanf("%s", command );
		ifCommand("rolldice"){
            lempar_Dadu(&dadu1,&dadu2);
		}
		else ifCommand("info"){
            scanf("%s", tmp);
            block_info_petak(map,tmp);
		}
		else ifCommand("buy"){

		}
		else ifCommand("sell"){

		}
		else ifCommand("sellbank"){

		}
		else ifCommand("showoffered"){

		}
		else ifCommand("upgrade"){

		}
		else ifCommand("board"){
            print_map(map);
		}
		else ifCommand("leaderboard"){
			print_leaderboard( map );
		}
		/*tambah cheat buat travel*/
		else ifCommand("travel"){
            scanf("%s",tmp);
            player_travel(map,PA,tmp);
		}
		else {
			printf("perintah tidak diketahui\n");
		}

	} while( true );


    BlockAddress addr = map.first;
    addr = map.first->map_next;

    do	 {
//        printf("%d\n", addr->id );
        printf("ad : %s\n", addr->name);
        addr = addr->map_next;
    }while( addr != NULL );


    print_map(map);
    // print info petak: block_info_petak(map);
//	save( cplayer, map );



	return 0;
}
