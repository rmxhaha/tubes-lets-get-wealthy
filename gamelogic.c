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

//mengembalikan BlockAddress di mana player berada, atau NULL
BlockAddress search_player(MonopolyMap map,void* player)
{
    BlockAddress B;
    B = map.first;
    boolean found=false;

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
            found = FSearch(B->list_player, Search(B->list_player, player));
        }

        //ngecek ketemu apa kaga?
        if(found)
        {
            return B;
        }

        B = B->map_next;
    }
}

//=====================================================================================

//masukin player ke block
void place_player(BlockAddress *B, void *Player)
{
    InsVFirst(&(*B)->list_player, Player);
}

//=====================================================================================

BlockAddress last_block(MonopolyMap map)
{
    BlockAddress last;
    last = map.first;

    while(last != NULL)
    {
        last = last->map_next;
    }
}

//=====================================================================================

//majuin player 1 petak
//masih belom bisa, last masih salah
void pindah_player1(MonopolyMap map, void *Player )
{
    BlockAddress here;
    BlockAddress last;

    here = search_player(map, Player);//hasilsearch


        last = last_block(map);



    //menghilangkan keberadaan player di petak
    DeleteP(&here->list_player, Player);


    //ngubah posisi
    if(here == last)
    {
        here = map.first;//startblock;
        InsVFirst(&here->list_player, Player);
    }
    else
    {
        here = here->map_next;
        InsVFirst(&here->list_player, Player);
    }

}

//=====================================================================================

void pindah_player(MonopolyMap map, void *Player, int d )
{
    int i;

    for(i=1; i<=d; i++)
    {
        pindah_player1(map, Player );
    }
}

//=====================================================================================


void pick_jumlah_player(MonopolyMap map){
	int N,i;
	PlayerAddress PA;


	do{
		printf("Jumlah player = ");scanf("%d",&N);
		if( N < 2 || 4 < N ){
			printf("Jumlah player tidak wajar (tolong pilih dari 2-4 player)\n");
		}
	} while( N < 2 || 4 < N );

    CreateList(&map.first->list_player);

	for( i = 0; i < N; ++ i ){
		player_alokasi(&PA);
		player_init(&PA);

		PA->name[0] = 'A' + (char)i; // a b c d
		PA->name[1] = '\0';

		InsVLast(&map.first->list_player,PA);
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

void pindah_player_ke(MonopolyMap,PlayerAddress, BlockAddress);

//=====================================================================================










