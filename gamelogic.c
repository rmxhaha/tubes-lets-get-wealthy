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
            B = B->line_next;
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

        B = B->line_next;
    }
}

//=====================================================================================

//masukin player ke block
void place_player(BlockAddress *B, void *Player)
{
    InsVFirst(&(*B)->list_player, Player);
}

//=====================================================================================

//majuin player 1 petak
void pindahPlayer1(MonopolyMap map, void *Player )
{
    BlockAddress here;
    BlockAddress last;

    here = search_player(map, Player);//hasilsearch

    //kotak terakhir
    find_last_in_line(last,map.first);
    while(last->map_next != NULL)
    {
        last= last->map_next;
    }



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

void pindahPlayer(MonopolyMap map, void *Player, int d )
{
    int i;
    BlockAddress pencarian;

    for(i=1; i<=d; i++)
    {
        pindahPlayer1(map, Player );
        pencarian = search_player(map, Player);
        printf("kalo dicari A ada di: %s\n", pencarian->name);
    }
}

//=====================================================================================















