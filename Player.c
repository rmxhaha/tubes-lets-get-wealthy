#include "Player.h"

void player_init(PlayerAddress Padd)
{
    (*Padd).name[0] = '\0';
    (*Padd).money = 0;
    (*Padd).revolution_count = 0;
    (*Padd).save_chance = 0;
}

void player_alokasi(PlayerAddress Padd)
{
    Padd = (Player*) malloc(sizeof(Player));
}

