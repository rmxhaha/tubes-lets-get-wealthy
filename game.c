#include "Player.h"
#include "Block.h"
#include "MonopolyMap.h"
#include "infopetak.h"
#include "gamelogic.h"
#include "worldtravel.h"
#include "host.h"
#include "unistd.h"
#include "stdio.h"

#define ifCommand(cmd)\
	if( strcmp( command, cmd) == 0 )

int main(){
	MonopolyMap map;
	Block block;
	BlockAddress here;
	boolean roll, reroll;  //buat ngecek reroll, jadiin true pas ganti player
	boolean upgraded; //untuk cek sudah upgrade. jadi false pas ganti player
	char command[100];
	char tmp[100];
    PlayerAddress PA;
    Address P;
    BlockAddress blackout;

	int dadu1, dadu2;
	set_Random(); // init random

	FILE *f = fopen("mapdata.txt","r");
	map = load_map(f);
	fclose(f);

    roll = true;
    reroll = false;
    upgraded = false;

    if( access("savedata.dat", F_OK ) == -1){
        tmp[0] = 'n'; // no save game by default
    }
    else {
        printf("Mau load save game ?(y/n)");
        scanf("%c",&tmp[0]);

        if( tmp[0] == 'y' )
        {
            f = fopen("savedata.dat","r");
			if( f == NULL ){
				printf("fail to load\n");
			}
			else {
				load_game(f,&map,&roll,&reroll,&upgraded);
				fclose(f);
				printf("loaded\n");
			}
        }
    }

    // if no load save
    if( tmp[0] != 'y' )
        pick_jumlah_player(&map);



/*

    here = Info(First(map.ListOffered));
    printf("%d\n",here);
    printf("%d\n",here->id);


*/
	// repeat until game is won
	do {
        PA = Info(map.cplayer);

        printf("> ");
		scanf("%s", command );
		ifCommand("save"){
            f = fopen("savedata.dat","w+");
			if( f == NULL ){
				printf("fail to save\n");
			}
			else {
				save_game(f,map,roll,reroll,upgraded);
				fclose(f);
				printf("saved\n");
			}
		}
		else ifCommand("rolldice"){
		    //jalanin player & lempar dadu
		    if(roll || reroll)
            {
                roll = false;

                lempar_Dadu(&dadu1,&dadu2);
                pindah_player(&map, PA, dadu1+dadu2);
                here = search_player(map, PA);

                reroll = dadu1 == dadu2;

                if(reroll)
                {
                    printf("re-roll\n");
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
            buy(map, PA, &upgraded);

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
            scanf("%s", &tmp);
            here = search_block_by_name(map, tmp);
            sell_bank(PA, &here);
		}
		else ifCommand("showoffered"){
            showoffered(&map);
		}
		else ifCommand("buyoffered"){
            char wi[50];
            scanf("%s", &wi);
            buyoffered(&map, PA, wi,&upgraded);
		}
		else ifCommand("upgrade"){
            if(!upgraded)
            {
                upgrade(map, &PA,&upgraded);
            }
            else
            {
                printf("Gaboleh tamak, anda sudah upgrade.\n");
            }
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
            if( roll || reroll ){
                printf("anda belum rolldice sehingga anda tidak bisa endturn\n");
            } else {
                roll = true;
                reroll = false;
                upgraded = false;
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
            scanf("%d", &PA->save_chance);
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
        else ifCommand("maju")
        {
            pindah_player(&map, PA, 1);
        }
        else ifCommand("protect")
        {
            scanf("%s",tmp);
            if(PA->save_chance==8)//kalau punya kartu perlindungan
            {
                here = search_block_by_name(map,tmp);
                if(tmp!=NULL)
                {
                    protect(&blackout,&map,PA,tmp);
                }
            }
            else
            {
                printf("Anda tidak punya kartu perlindungan.\n");
            }

        }
		else {
			printf("perintah tidak diketahui\n");
		}

		updateBlockStatus( map );
		
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


