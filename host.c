#include "host.h"
void block_host (MonopolyMap (*map), PlayerAddress player, char *namatempat)
{
    BlockAddress here= search_block_by_name(*map,namatempat);

    (*map).world_cup_city = here;
    (*map).world_cup_city->tab_harga[(*map).world_cup_city->level] = 2* (*map).world_cup_city->tab_harga[(*map).world_cup_city->level];
    player->world_cup_holder = true;
    printf("berhasil ganti harga\n");
    printf("nanana harga%d\n",(*map).world_cup_city->tab_harga[(*map).world_cup_city->level]);
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
    //tes sekarang di mana
    tes = search_player((*map),player);
    if (tes->type==8)
    {
        printf("hoho wc\n");
    }
    else
    {
        printf("nay\n");
    }
    //printf("input nama kota \n");
    //scanf("%s",kota);
    //printf("a\n");
    //block_host(map,player,kota);
    if(player->world_cup_holder)
    {
        printf("status player: world cup holder\n");
    }
    else
    {
        printf("status player: NOT world cup holder\n");
    }
    printf("map world cup city\n");
    printf("%s\n",(*map).world_cup_city->name);
    printf("harga tes masuk cheathost: %d\n",(*map).world_cup_city->tab_harga[(*map).world_cup_city->level]);
}
