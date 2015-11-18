#include "Player.h"

void player_alokasi(PlayerAddress *Padd)
{
    *Padd = (Player*)malloc(sizeof(Player));
}

void player_dealokasi(PlayerAddress *Padd)
{
	free(*Padd);
    *Padd = NULL;
}

void player_init(PlayerAddress *Padd)
{
    *Padd = (Player*)malloc(sizeof(Player));

    (*Padd)->name[0] = '\0';
    (*Padd)->money = 2000000;
    (*Padd)->revolution_count = 0;
    (*Padd)->save_chance = 0;
    (*Padd)->world_cup_holder = false;
}



