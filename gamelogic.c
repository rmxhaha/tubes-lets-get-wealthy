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
    InsVFirst(&B->list_player, player);
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
void pindah_player1(MonopolyMap map, PlayerAddress player )
{
    BlockAddress here;

    here = search_player(map, player);//hasilsearch

    //menghilangkan keberadaan player di petak
    DeleteP(&here->list_player, player);


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
    }

    //cek lewat worldcup
    if(here->type == 8)
    {
        //ubah jadi false parameter player pemegang worldcup
    }



}

//=====================================================================================

void pindah_player(MonopolyMap map, PlayerAddress player, int d )
{
    int i;

    for(i=1; i<=d; i++)
    {
        pindah_player1(map, player );
    }

    //cek masuk worldcup
    BlockAddress here;
    here = search_player(map, player);

    if(here->type == 8)
    {
        //ubah jadi true status pemegang world cup
    }
}

//=====================================================================================


void pick_jumlah_player(MonopolyMap *map){
	int N,i;
	PlayerAddress PA;


	do{
		printf("Jumlah player = ");scanf("%d",&N);
		if( N < 2 || 4 < N ){
			printf("Jumlah player tidak wajar (tolong pilih dari 2-4 player)\n");
		}
	} while( N < 2 || 4 < N );

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

//=====================================================================================

void process_buy(MonopolyMap,PlayerAddress);

//=====================================================================================

void process_upgrade(MonopolyMap,PlayerAddress);

//=====================================================================================

void pindah_player_ke(MonopolyMap *map,PlayerAddress player, BlockAddress bpindah)
{
    //cari blockaddress player
    BlockAddress here = search_player(*map, player);
    //hapus keberadaan player di situ
    DeleteP(&here->list_player, player);
    //taroh di tempat baru
    place_player(bpindah,player);
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



void sell(MonopolyMap* map,Block* b){
    if( b->owner == NULL ) return;

    // insert kalau belum ada
    if( Search(map->ListOffered,b) == NULL )
        InsVFirst(&map->ListOffered,b);
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

    if(P->money >= B->tab_harga[B->level])
    {
        P->money -= (B->tab_harga[B->level]);
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
