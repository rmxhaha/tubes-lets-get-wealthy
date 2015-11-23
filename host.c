#include "host.h"
void block_host (MonopolyMap (*map), PlayerAddress player, char *namatempat)
{
    BlockAddress here= search_block_by_name(*map,namatempat);

    (*map).world_cup_city = here;
    (*map).world_cup_city->tab_harga[(*map).world_cup_city->level] = 2* (*map).world_cup_city->tab_harga[(*map).world_cup_city->level];
    player->world_cup_holder = true;
   //player->world_cup_holder = true;
}

void cheat_block_host (MonopolyMap *map, PlayerAddress player)
{
    char kota[100];
    BlockAddress wc = (*map).first;
    BlockAddress tes;
    while (wc->type!=8)
    {
        wc = wc->map_next;
    }
    pindah_player_ke((map),player,wc);
}