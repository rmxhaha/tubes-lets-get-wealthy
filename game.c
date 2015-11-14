#include "Player.h"
#include "Block.h"
#include "MonopolyMap.h"
#include "infopetak.h"

#define ifCommand(cmd)\
	if( strcmp( command, cmd) == 0 )

int main(){
	MonopolyMap map;
	Block block;
	Address cplayer; // current player
	char command[100];

	FILE *f = fopen("mapdata.txt","r");
    map = load_map(f);
    fclose(f);

    pick_jumlah_player(map);
	cplayer = First(map.ListTurn);

	// repeat until game is won
	do {
		scanf("%s", command );
		ifCommand("rolldice"){

		}
		else ifCommand("info"){

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

		}
		else ifCommand("leaderboard"){

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
