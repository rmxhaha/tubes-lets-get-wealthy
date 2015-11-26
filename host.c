#include "host.h"
void block_host (MonopolyMap *map, PlayerAddress player, char *namatempat)
{
    BlockAddress here= search_block_by_name(*map,namatempat);

    (*map).world_cup_city = here;
    (*map).world_cup_city->multiplier = 2;
    player->world_cup_holder = true;
   //player->world_cup_holder = true;
}

void cheat_block_host (MonopolyMap *map, PlayerAddress player)
{
    char kota[100];
    BlockAddress wc = (*map).first;
    BlockAddress tes;
    while (wc->type!=WORLD_CUP)
    {
        wc = wc->map_next;
    }
    pindah_player_ke((map),player,wc);
}
