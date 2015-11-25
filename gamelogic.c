#include "gamelogic.h"

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
    BlockAddress here;
    Address pemain;
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
    }

    //cek lewat worldcup
    if(here->type == 8)
    {
       if(player->world_cup_holder)
        {
            //ubah harga
            map.world_cup_city->tab_harga[map.world_cup_city->level] = (map.world_cup_city->tab_harga[map.world_cup_city->level]) / 2;
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

    habispindah(here, player);

}

//=====================================================================================

void habispindah(MonopolyMap *map, BlockAddress here, PlayerAddress player)
{
    char perintah[100];
    char namatempat[100];
    printf("player sekarang di petak %s\n", here->name);

    if(here->type == TANAH)
    {
        //bayar pajak
        if(!(here->owner == NULL) && !(here->owner == player))
        {

        }
    }
    else if(here->type == KESEMPATAN)
    {

    }
    else if(here->type == PAJAK)
    {

    }
    else if(here->type == KELILING_DUNIA)
    {

    }
    else if(here->type == BONUS)
    {

    }
    else if(here->type == PARIWISATA)
    {

    }
    else if(here->type == DESERTED_ISLAND)
    {

    }
    else if(here->type == WORLD_CUP)
    {
        //ubah jadi true status pemegang world cup
        player->world_cup_holder = true;
        printf("> ");
        scanf("%s",perintah);
        if(strcmp(perintah,"host")==0)
        {
            if((*map).world_cup_city!=NULL)
            {
                //harga kota dijadiin normal dulu
                (*map).world_cup_city->tab_harga[(*map).world_cup_city->level] = ((*map).world_cup_city->tab_harga[(*map).world_cup_city->level]) / 2;
            }
            scanf("%s",namatempat);
            block_host(map,player,namatempat);
            printf("Kota %s berhasil menjadi world cup\n",(*map).world_cup_city->name);
        }
        else
        {
            printf("perintah salah\n");
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

    if(here->type == 8)
    {
        //ubah jadi true status pemegang world cup
        (player)->world_cup_holder = true;
         printf("> ");
        scanf("%s",perintah);
        if(strcmp(perintah,"host")==0)
        {
           if((*map).world_cup_city!=NULL)
            {
                //harga kota dijadiin normal dulu
                (*map).world_cup_city->tab_harga[(*map).world_cup_city->level] = ((*map).world_cup_city->tab_harga[(*map).world_cup_city->level]) / 2;
            }
            scanf("%s",namatempat);
            block_host(map,player,namatempat);
            printf("Kota %s berhasil menjadi world cup\n",(*map).world_cup_city->name);

       }
        else
        {
            printf("perintah salah\n");
        }
    }

}
//=====================================================================================
/*
void do_chance (MonopolyMap *map, PlayerAddress *P)
{
/*	Player menerima kartu kesempatan secara random, melakukan aksi berdasarkan kartu
	yang diterima.*/
	//BELUM SELESAI...
	//KAMUS
	Chance c;
	char input[10];
	BlockAddress B;
/*
	//ALGORITMA
	c = get_chance();
	printf("Kartu kesempatan : %d\n", c);
	if (c==6 || c==7 || c==8 || c==9 || c==10) {
		printf("Ingin simpan kartu?");
		scanf("%s", input);
		if (strcmp(input, "simpan")== 0) {
			printf("Simpan kartu.");
			(*P)->save_chance = c;
		}
		else {
			printf("Buang kartu.");
		}
	}
	else { /* 1, 2, 3, 4, 5 (GOTO_PAJAK, GOTO_PENJARA,
		GOTO_START, GOTO_KELILING_DUNIA, MATI_LAMPU,) */
/*		switch(c) {
			case 1 : //GOTO_PAJAK
				B = search_block_by_name(*map, "Pajak");
				pindah_player_ke(*map, *P, B);
				break;
			case 2 : //GOTO_PENJARA
				B = search_block_by_name(*map, "Penjara");
				pindah_player_ke(*map, *P, B);
				break;
			case 3 : //GOTO_START
				B = search_block_by_name(*map, "Start");
				pindah_player_ke(*map, *P, B);
				break;
			case 4 : //GOTO_KELILING_DUNIA
				B = search_block_by_name( *map, "World_Travel");
				pindah_player_ke(*map, *P, B);
				break;
			case 5 : //MATI_LAMPU
				do {
					scanf("%s", input);
					B = search_block_by_name( *map, input);
					if (B == NULL) {
						printf("Kota tidak ada, ulangi");
					}
					else {
						//Set multiplier kota jadi 0 selama 3 turn
					}
				} while (B == NULL);
				break;
			default :
				break;
		}
	}
}
*/
void bayar_pajak(PlayerAddress *P)
/*Datang ke kantor pajak, player membayar pajak sebesar 100K*,
  kalau tidak bisa bayar, bangkrut.*/
{
	if ((*P)->money >= 100000) { //bayar pajak
		(*P)->money -= 100000;
	}
	else { //bangkrut

	}
}

void sell_bank (PlayerAddress P, BlockAddress *B)
/*Jual tanah ke bank*/
{
	if (P == (*B)->owner) {
		//Jual tanah
	}
	else {
		printf("Tanah bukan milik anda, tidak bisa dijual.");
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

void buyoffered(MonopolyMap* map, Player* player, char* nama_petak){
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
    );
}

void buy(MonopolyMap map, PlayerAddress P)
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

                    printf("Selamat, kota %s kini menjadi milikmu!\n", B->name);
                    printf("level bangunan %d\n", B->level);
                    printf("sisa uangmu: ");print_money(P->money);printf("\n");
                }
                else
                {
                    printf("Uangmu tidak cukup untuk membeli kota ini\n");
                }
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

void upgrade(MonopolyMap map, PlayerAddress *P)
{
    BlockAddress B;
    B = search_player(map, *P);

    if((*P)->money >= B->tab_harga[B->level + 1])
    {
        if(B->owner == *P)
        {
            (*P)->money -= (B->tab_harga[B->level + 1]);
            B->level++;


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
        printf("Uangmu tidak cukup untuk upgrade\n");
    }
}
