#include "Player.h"
#include "Block.h"
#include "MonopolyMap.h"
#include "infopetak.h"
#include "gamelogic.h"
#include "worldtravel.h"
#include "host.h"

#define ifCommand(cmd)\
	if( strcmp( command, cmd) == 0 )

int main(){
	MonopolyMap map;
	Block block;
	BlockAddress here;
	boolean roll, reroll;  //buat ngecek reroll, jadiin true pas ganti player
	char command[100];
	char tmp[100];
    PlayerAddress PA;

	int dadu1, dadu2;
	set_Random(); // init random

	FILE *f = fopen("mapdata.txt","r");
    map = load_map(f);
    fclose(f);
    roll = true;
    reroll = false;

    pick_jumlah_player(&map);
	// repeat until game is won
	do {
        PA = Info(map.cplayer);

        printf("> ");
		scanf("%s", command );
		ifCommand("rolldice"){
		    //jalanin player & lempar dadu
		    if(roll || reroll)
            {
                roll = false;
                reroll = false;

                lempar_Dadu(&dadu1,&dadu2);
                pindah_player(&map, PA, dadu1+dadu2);
                here = search_player(map, PA);

                if(dadu1 == dadu2)
                {
                    printf("re-roll\n");
                    reroll = true;
                }
            }
            else
            {
                printf("sudah jalan\n");
            }


		}
		else ifCommand("info"){
            scanf("%s", tmp);
            block_info_petak(map,tmp);
		}
		else ifCommand("buy"){
            buy(map, PA);

            here = search_player(map, PA);
            if(here->owner == PA)
            {
                printf("kebeli\n");
            }
            else
            {
                printf("kaga kebeli\n");
            }
		}
		else ifCommand("sell"){
            char wa[50];
            scanf("%s", &wa);
            sell(&map, PA, wa);
		}
		else ifCommand("sellbank"){
            sell_bank(PA, &here);
		}
		else ifCommand("showoffered"){
            showoffered(&map);
		}
		else ifCommand("buyoffered"){
            char wi[50];
            scanf("%s", &wi);
            buyoffered(&map, PA, wi);
		}
		else ifCommand("upgrade"){
            upgrade(map, &PA);
		}
		else ifCommand("board"){
            print_map(map);
		}
		else ifCommand("leaderboard"){
			print_leaderboard( map );
		}
		/*tambah cheat buat travel*/
		else ifCommand("travel"){
            scanf("%s", &tmp);
            player_travel(map,PA, &tmp);
		}
		else ifCommand("cheathost"){
            cheat_block_host(&map,PA);
        }
        else ifCommand("host"){
            if( search_player(map,PA)->type != WORLD_CUP){
                printf("Anda tidak berada di world cup.\n");
            }
            else {
                scanf("%s", &tmp);
                block_host( &map,PA,tmp);
            }
        }
        else ifCommand("whoami"){
            printf("current player: %s\n",PA->name);
        }
        else ifCommand("endturn"){
            if( roll ){
                printf("anda belum rolldice sehingga anda tidak bisa endturn\n");
            } else {
                roll = true;
                reroll = false;
                endturn(&map);
            }
        }
        else ifCommand("bangkrut"){
            PA->money = 1;
            print_money(PA->money);
        }
        /*cheat langsung ke petak bayar pajak*/
        else ifCommand("cheattax"){
            bayar_pajak(&map,&PA);
        }
        else ifCommand("cheat_rolll_travel"){
            strcpy(tmp, "KelDun");
            here = search_block_by_name(map, tmp);
            pindah_player_ke(&map, PA, here);
        }
        else ifCommand("cheatchance")
        {
            strcpy(tmp, "Kesemp.");
            here = search_block_by_name(map, tmp);
            pindah_player_ke(&map, PA, here);
        }
        else ifCommand("gotojail")
        {
            strcpy(tmp, "Deser.Isl.");
            here = search_block_by_name(map, tmp);
            pindah_player_ke(&map, PA, here);
        }
        else ifCommand("gototax")
        {
            strcpy(tmp, "Pajak");
            here = search_block_by_name(map, tmp);
            pindah_player_ke(&map, PA, here);
        }
		else {
			printf("perintah tidak diketahui\n");
		}

	} while( !is_game_finished(map) );


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


