#include "gamelogic.h"

boolean is_game_finished(MonopolyMap map ){
    if( NbElmt(map.ListPlayer) == 1 ) return true;
    return false;
}

//mengembalikan true apabila di block terdapat player(tidak spesifik player mana)
boolean is_player_on(BlockAddress B)
{
    if(!IsListEmpty(B->list_player))
        return true;
    else
        return false;
}

//=====================================================================================
//mengembalikan BlockAddress sesuai dengan nama input, atau NULL
BlockAddress search_block_by_name(MonopolyMap map, char* namatempat)
{
    BlockAddress b;
    boolean found;

    //mencari nama kota
    found = false;
    b = map.first;
    do
    {
        if(strcmp(namatempat,b->name)==0)
        {
            found = true;
        }
        else
        {
           b = b->map_next;
        }
    }
    while(!found && b != NULL);

    if(found)
    {
		return b;
    }
    else
    {
		return NULL;
    }
}

//=====================================================================================

void dapet_Bonust(PlayerAddress player)
{
    player->money += 150000;
    printf("Selamat, kamu mendapat bonus 150k\n");
    printf("Uang anda ");print_money(player->money);printf("\n");
    //printf("%d",player->money);
}

//=====================================================================================

//mengembalikan BlockAddress di mana player berada, atau NULL
BlockAddress search_player(MonopolyMap map,PlayerAddress player)
{
    BlockAddress B;
    void *PP;

    B = map.first;

    while(B!=NULL)
    {
        //nyari block mana yang ada playernya
        while((!is_player_on(B)) && (B!=NULL))
        {
            B = B->map_next;
        }

        //nentuin apakah player yang ada di block player yang dicari apa bukan
        if(B != NULL)
        {
            PP = Search(B->list_player, player);

            //ngecek ketemu apa kaga?
            if( PP != Nil )
                return B;
        }

        B = B->map_next;
    }
}

//=====================================================================================

//masukin player ke block
void place_player(BlockAddress B, PlayerAddress player)
{
	if (B != NULL) {
    InsVFirst(&B->list_player, player);
	}
}

//=====================================================================================

BlockAddress last_block(MonopolyMap map)
{
    BlockAddress last;
    last = map.first;

    while(last->map_next != NULL)
    {
        last = last->map_next;
    }

    return last;
}

//=====================================================================================

//majuin player 1 petak
//masih belom bisa, last masih salah
void pindah_player1(MonopolyMap map, PlayerAddress player)
{
    BlockAddress here,blackout;
    Address pemain,P;
    PlayerAddress ip;
    here = search_player(map, player);//hasilsearch
    char kotahost[100];

    //menghilangkan keberadaan player di petak
    DeleteP(&here->list_player, player);

    //printf("masuk pindah_player1\n");
    //ngubah posisi
    if(here->map_next == NULL) // last block
    {
        here = map.first;//startblock;
        place_player(here,player);
    }
    else
    {
        here = here->map_next;
        place_player(here,player);
    }


    //cek udah muter
    if(here == map.first)
    {
        player->revolution_count++;

        if(player->revolution_count > 1)
        {
            player->money += 150000;
        }
        //turn_on_light(&blackout,&map,player);
        P = First(map.ListBlackout);
        while(P!=NULL)
        {
            blackout = Info(P);
           if(blackout->owner==player)
            {
                printf("Kota %s punya %s sudah normal\n",blackout->name, blackout->owner);
                if(blackout==map.world_cup_city)
                {
                    blackout->multiplier=2;
                }
                else
                {
                    blackout->multiplier=1;
                }
            }
            /*if(blackout->blackoutguy==player)
            {
                blackout->multiplier = 1;
                //DeleteP(&map.ListBlackout, blackout);
            }*/
                P = Next(P);
        }
    }

    //cek lewat worldcup
    if(here->type == 8)
    {
       if(player->world_cup_holder)
        {
            //ubah harga
            map.world_cup_city->multiplier = 1;
       }
        //ubah jadi false parameter player pemegang worldcup
        //semua jadi false statusnya
        pemain = First(map.ListPlayer);
        ip = Info(pemain);
        do
        {
            ip->world_cup_holder = false;
            pemain = Next(pemain);
        }
        while ((pemain) != NULL);
    }
}

//=====================================================================================

void pindah_player(MonopolyMap *map, PlayerAddress player, int d )
{
    int i;


    for(i=1; i<=d; i++)
    {
        pindah_player1(*map, player );
    }

    //cek masuk worldcup
    BlockAddress here;
    here = search_player(*map, player);

    habispindah(map, here, &player);

}

//=====================================================================================

void habispindah(MonopolyMap *map, BlockAddress here, PlayerAddress *player)
{
    char perintah[100];
    char namatempat[100];
    printf("player sekarang di petak %s\n", here->name);
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    if(here->type == TANAH)
    {
        //bayar sewa
        if(!(here->owner == NULL) && (here->owner != *player))
        {
            printf("Kasian bayar sewa!\n");
            if ((*player)->save_chance == BEBAS_SEWA)
            {
                do
                {
                    scanf("%s",perintah);
                    if(strcmp(perintah,"free_penalty")!=0)
                    {
                        printf("Anda punya kartu bebas sewa. Tulis 'free_penalty'\n");
                    }

                }while(strcmp(perintah,"free_penalty")!=0);
                (*player)->save_chance =0;
            }
            else if ((*player)->money >= (here->multiplier * here->tab_denda[here->level])) { //bayar pajak
                (*player)->money -= (here->multiplier * here->tab_denda[here->level]);
            }
            else { //bangkrut
                    printf("bangkrut kasian\n");
                player_bangkrut(map,player);
            }
        }
    }
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    else if(here->type == KESEMPATAN)
    {
        // do chance
        do_chance(map,player);
    }
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    else if(here->type == PAJAK)
    {
        bayar_pajak(map,player);
    }
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    else if(here->type == KELILING_DUNIA)
    {
        scanf("%s",&namatempat);
        player_travel(*map,*player,&namatempat);
    }
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    else if(here->type == BONUS)
    {
       dapet_Bonust(*player);
    }
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    else if(here->type == PARIWISATA)
    {
        //bayar sewa
        if(!(here->owner == NULL) && (here->owner != *player))
        {
            printf("Kasian bayar sewa!\n");
            if ((*player)->save_chance == BEBAS_SEWA)
            {
                do
                {
                    scanf("%s",perintah);
                    if(strcmp(perintah,"free_penalty")!=0)
                    {
                        printf("Anda punya kartu bebas sewa. Tulis 'free_penalty'\n");
                    }

                }while(strcmp(perintah,"free_penalty")!=0);
                (*player)->save_chance =0;
            }
            else if ((*player)->money >= (here->multiplier * here->tab_denda[here->level])) { //bayar pajak
                (*player)->money -= (here->multiplier * here->tab_denda[here->level]);
            }
            else { //bangkrut
                    printf("bangkrut kasian\n");
                player_bangkrut(map,player);
            }
        }
    }
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    else if(here->type == DESERTED_ISLAND)
    {
        printf("Kasian masuk penjara!\n");
        if ((*player)->save_chance == BEBAS_PENJARA)
        {
            puts("tes masuk penjara\n");
            do
            {
                scanf(" %[^\n]s",&perintah);
                if(strcmp(perintah,"free me")!=0)
                {
                    printf("Anda punya kartu bebas penjara. Tulis 'free me'.\n");
                }

            }while(strcmp(perintah,"free me")!=0);
         (*player)->save_chance =0;
        }
        else if ((*player)->money >= 1000000)
        {
            printf("Uang anda berkurang 1M\n");
            (*player)->money -= 1000000;
        }
        else {
            player_bangkrut(map,player);
        }
    }
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    else if(here->type == WORLD_CUP)
   {
        //ubah jadi true status pemegang world cup
        (*player)->world_cup_holder = true;
        printf("Anda di world cup\n");
        do {
            printf("> ");
            scanf("%s",perintah);
            if (strcmp(perintah,"host")!=0) {
                printf("perintah salah, ulangi\n");
            }
            else {
                scanf("%s",namatempat);
                if (search_block_by_name(*map, namatempat) == NULL) {
                printf("tidak ada block %s, ulangi\n", namatempat);
                }
            }
        } while (strcmp(perintah,"host")!=0 || (search_block_by_name(*map, namatempat) == NULL));

        if((*map).world_cup_city!=NULL)
        {
            //harga kota dijadiin normal dulu
            (*map).world_cup_city->multiplier = 1;
        }
        block_host(map,player,namatempat);
        if((*map).world_cup_city!=NULL)
        {
            printf("Kota %s berhasil menjadi world cup\n",(*map).world_cup_city->name);
        }
    }


}

//=====================================================================================

void pick_jumlah_player(MonopolyMap *map){
	int N,i;
	PlayerAddress PA;


	do{
		printf("Jumlah player = ");scanf("%d",&N);
		if( N < MIN_PLAYER || MAX_PLAYER < N ){
			printf("Jumlah player tidak wajar (tolong pilih dari 2-4 player)\n");
		}
	} while( N < MIN_PLAYER || MAX_PLAYER < N );

	for( i = 0; i < N; ++ i ){
		player_alokasi(&PA);
		player_init(&PA);

		PA->name[0] = 'A' + (char)i; // a b c d
		PA->name[1] = '\0';

		InsVLast(&(map->first->list_player),PA);
		InsVLast(&(map->ListPlayer), PA);
	}

	map->cplayer = First(map->ListPlayer);
}

/**
	Spec :
		pada putaran pertama hanya bisa membeli hingga level 2
		pada putaran selanjutnya bisa membeli hingga level 3
		landmark bisa di beli jika gedung sudah level 3 dan di putaran setelah pembelian gedung level 3
	Note :
		putaran player selesai setelah buy process
*/

void pindah_player_ke(MonopolyMap *map,PlayerAddress player, BlockAddress bpindah)
{
    //cari blockaddress player
    BlockAddress here = search_player(*map, player);
    char perintah[100];
    char namatempat[100];

    while (here!=bpindah)
    {
        pindah_player1(*map, player);
        here = search_player(*map, player);
    }

    here = search_player(*map, player);
    habispindah(map, here, &player);

}
//=====================================================================================

void do_chance (MonopolyMap *map, PlayerAddress *P)
{
/*	Player menerima kartu kesempatan secara random, melakukan aksi berdasarkan kartu
	yang diterima.*/
	//BELUM SELESAI...
	//KAMUS
	Chance c;
	char input[10];
	BlockAddress B;

	//ALGORITMA
	c = get_chance();
	printf("Kartu kesempatan : %d\n", c);
	if (c==6 || c==7 || c==8 || c==9 || c==10) {
		printf("Ingin simpan kartu?\n");
		scanf(" %s", input);
		if (strcmp(input, "simpan")== 0) {
			printf("Simpan kartu.\n");
			(*P)->save_chance = c;
		}
		else {
			printf("Buang kartu.\n");
		}
	}
	else { /* 1, 2, 3, 4, 5 (GOTO_PAJAK, GOTO_PENJARA,
		GOTO_START, GOTO_KELILING_DUNIA, MATI_LAMPU,) */
        switch(c) {
			case 1 : //GOTO_PAJAK
				B = search_block_by_name(*map, "Pajak");
				pindah_player_ke(&(*map), *P, B);
				break;
			case 2 : //GOTO_PENJARA
				B = search_block_by_name(*map, "Deser.Isl.");
				pindah_player_ke(&(*map), *P, B);
				break;
			case 3 : //GOTO_START
				B = search_block_by_name(*map, "Start");
				pindah_player_ke(&(*map), *P, B);
				break;
			case 4 : //GOTO_KELILING_DUNIA
				B = search_block_by_name( *map, "KelDun");
				pindah_player_ke(&(*map), *P, B);
				break;
			case 5 : //MATI_LAMPU
				do {
					scanf("%s", input);
					B = search_block_by_name( *map, input);
					if (B == NULL) {
						printf("Kota tidak ada, ulangi\n");
					}
					else if (B->owner ==NULL)
                    {
                        printf("Kota ini tidak ada yang punya, gimana sih\n");
                    }
					else {
						//Set multiplier kota jadi 0 selama 3 turn
                        InsVLast(&(*map).ListBlackout,B);
                        B->multiplier = 0;
                        //B->blackoutguy = *P;
                        if(((B->owner)->save_chance==PERLINDUNGAN))
                        {
                            printf("Player yang punya petak itu punya kartu perlindungan \n");
                        }
					}
				} while (B == NULL);
				break;
			default :
				break;
		}
	}
}

void bayar_pajak(MonopolyMap *map,PlayerAddress *P)
/*Datang ke kantor pajak, player membayar pajak sebesar 100K*,
  kalau tidak bisa bayar, bangkrut.*/
{
	char perintah[100];
	printf("Kasian bayar pajak!\n");
    if ((*P)->save_chance == BEBAS_PAJAK)
    {
        do
        {
            scanf("%s",perintah);
            if(strcmp(perintah,"free_tax")!=0)
            {
                printf("Anda punya kartu bebas pajak. Tulis 'free_tax'\n");
            }

        }while(strcmp(perintah,"free_tax")!=0);
        (*P)->save_chance =0;
    }
	else if ((*P)->money >= 100000) { //bayar pajak
		(*P)->money -= 100000;
	}
	else { //bangkrut
            printf("bangkrut kasian\n");
        player_bangkrut(map,P);
	}
}

void sell_bank (PlayerAddress P, BlockAddress *B)
/*Jual tanah ke bank*/
{
	if (P == (*B)->owner) {
		(*B)->owner = NULL;
		P->money += block_cost(**B);
		printf("Tanah berhasil dijual\n");
		printf("Uang anda ");print_money(P->money);printf("\n");
	}
	else {
		printf("Tanah bukan milik anda, tidak bisa dijual.\n");
	}
}

void print_money( int money ){
	int b = money / 1000000000 % 1000;
	int m = money / 1000000 % 1000;
	int k = money / 1000 % 1000;
	int r = money % 1000;

	if( b != 0 ){
        if( m != 0 )
            printf("%dB%d", b,m);
        else
            printf("%dB", b);
	}
	else if( m != 0 ){
        if( k != 0 )
            printf("%dM%d", m,k);
        else
            printf("%dM", m);
	}
	else if( k != 0 ){
        if( r != 0 )
            printf("%dK%d", k,r);
        else
            printf("%dK", k);
	}
	else
        printf("%d", r);
}

void print_leaderboard(MonopolyMap map){
	Address PP;
	PlayerAddress PA;
	boolean first = true;

	loop_list( map.ListPlayer,PP,
		if( first ){
			printf("> ");
			first = false;
		}
		else
			printf("  ");

		PA = Info(PP);
		printf("Player %s ", PA->name );
		print_money(PA->money);
		printf("\n");
	);
}



void sell(MonopolyMap* map,Player* cplayer, char *nama_petak){

    BlockAddress BA = search_block_by_name( *map, nama_petak );

    if( BA == NULL )
        printf("> Kota tidak ditemukan\n");
    else if( BA->owner != cplayer )
        printf("> Anda bukan pemilik kota tersebut\n");
    else if( Search(map->ListOffered,BA) == NULL )
        InsVFirst(&map->ListOffered,BA);
}

void buyoffered(MonopolyMap* map, Player* player, char* nama_petak, boolean *upgraded){
    Address PP;
    BlockAddress BA;

    loop_list(map->ListOffered,PP,
        BA = Info(PP);
        if( strcmp( BA->name, nama_petak) == 0 ){
            break;
        }
    );

    if( BA == NULL )
        printf("> kota tidak ada di list penjualan");
    else if( BA->owner == player )
        printf("> kota yang ingin anda beli adalah milik anda");
    else if( block_cost(*BA) <= player->money ){
            /*init upgrade jadi false supaya pas beli bisa upgrade sekali. kynya harus tambah parameter:(*/
            *upgraded = false;
        (BA->owner)->money += block_cost(*BA);
        BA->owner = player;
        player->money -= block_cost(*BA);
        printf("> terbeli, sisa uang anda "); print_money(player->money);
    }
    else {
        printf("> uang anda tidak cukup");
    }

    printf("\n");
}

void showoffered(MonopolyMap* map){
    Address PP;
    BlockAddress BP;
    boolean first = true;

    loop_list(map->ListOffered,PP,
        if( first ){
            printf("> ");
            first = false;
        }
        else
            printf("  ");

        BP = Info(PP);

        printf("%s, harga ", BP->name ); print_money( block_cost(*BP));
        printf("\n");
    );
}

void buy(MonopolyMap map, PlayerAddress P, boolean *upgraded)
{
    BlockAddress B;
    B = search_player(map, P);

    if((B->type == TANAH) || (B->type == PARIWISATA))
    {
        if(P->revolution_count>=1)
        {
            //cek kepemilikan
            if(B->owner == NULL)
            {
                if(P->money >= block_cost(*B))
                {
                    P->money -= block_cost(*B);
                    B->owner = P;
                    /*init upgrade jadi false supaya pas beli bisa upgrade sekali. kynya harus tambah parameter:(*/
                    *upgraded = false;
                    printf("Selamat, kota %s kini menjadi milikmu!\n", B->name);
                    printf("level bangunan %d\n", B->level);
                    printf("sisa uangmu: ");print_money(P->money);printf("\n");
                }
                else
                {
                    printf("Uangmu tidak cukup untuk membeli kota ini\n");
                }
            }
            else if(B->owner == P)
            {
                printf("properti anda\n");
            }
            else
            {
                printf("Properti player lain\n");
                if(P->money >= block_cost(*B)*2)
                {
                    P->money -= block_cost(*B)*2;
                    B->owner = P;

                    printf("Selamat, kota %s kini menjadi milikmu!\n", B->name);
                    printf("level bangunan %d\n", B->level);
                    printf("sisa uangmu: ");print_money(P->money);printf("\n");
                }
                else
                {
                    printf("Uangmu tidak cukup untuk membeli kota ini\n");
                }
            }
        }
        else
        {
            printf("Belum muter\n");
        }
    }
    else
    {
        printf("Petak tidak diperjualbelikan\n");
    }
}

void upgrade(MonopolyMap map, PlayerAddress *P,boolean *upgraded)
{
    BlockAddress B;
    B = search_player(map, *P);
    if((*P)->money >= block_upgrade_cost(*B))
    {
    if((((B->type == TANAH)&&(B->level <= 4))|| ((B->type == PARIWISATA)&&(B->level <= 0))))
        {
            if(B->owner == *P)
            {
                (*P)->money -= block_upgrade_cost(*B);
                B->level++;
                *upgraded = true;
                printf("Selamat, bangunanmu di %s memiliki level %d!\n", B->name, B->level);
                printf("sisa uangmu: ");print_money((*P)->money);printf("\n");
            }
            else
            {
                printf("Bukan properti anda\n");
            }
        }
        else
        {
            printf("Anda tidak bisa upgrade.\n");
        }
    }
    else
    {
        printf("Uangmu tidak cukup untuk upgrade\n");
    }
}

void endturn (MonopolyMap *map)
{
    map->cplayer = Next(map->cplayer);
    if (map->cplayer==NULL)
    {
        map->cplayer= First(map->ListPlayer);
    }
}

void player_bangkrut(MonopolyMap *map, PlayerAddress *player)
{

    BlockAddress B = (*map).first;
    do
    {
        if((B->owner)==*player)
        {
            B->owner = NULL;
            B->level = 0;
            B->multiplier = 1;
            printf("Tanah %s bukan milik anda lagi.\n",B->name);
        }
        B = B->map_next;
    } while (B!=NULL);

    endturn(map);

    BlockAddress here = search_player(*map,*player);
    DeleteP(&(here->list_player),*player);
    DeleteP(&map->ListPlayer,*player);
    printf("Anda sudah bangkrut dan kalah dan menghilang\n");
}

void protect(BlockAddress *blackout, MonopolyMap *map, PlayerAddress player,char* tempat)
{

    Address P = First((*map).ListBlackout);
    boolean stop = false;
    BlockAddress tes = Info(P);
    //tempat pasti ada karna di cek di game.c
    while((P!=NULL)&&(!stop))
    {
        *blackout = Info(P);
        if(strcmp(((*blackout)->name),tempat)==0)
        {
            stop = true;
        }
        else
        {
            P = Next(P);
        }
    }
    if(stop)
    {
        if(((*blackout)->owner==player))
        {
            printf("Kota %s punya %s sudah normal\n",(*blackout)->name, (*blackout)->owner);
            if((*blackout)==(*map).world_cup_city)
            {
                (*blackout)->multiplier=2;
            }
            else
            {
                (*blackout)->multiplier=1;
            }
        }
    }
    else
    {
        printf("Tidak bisa pakai protect\n");
    }
}


