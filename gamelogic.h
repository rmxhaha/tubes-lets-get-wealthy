#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "Block.h"
#include "Player.h"
#include "MonopolyMap.h"

/**
	Spec :
		kalau di nyampe ujung map
		- mulai dari map.first lagi
		kalau melewati start maka
		- revolution_count di tambah
		- jika revolution_count != 1 maka duit di tambah 150k
*/


//mengembalikan true apabila di block terdapat player(tidak spesifik player mana)
boolean is_player_on(BlockAddress B);

//mengembalikan BlockAddress di mana player berada, atau NULL
BlockAddress search_player(MonopolyMap map,void* player);

//masukin player ke block
void place_player(BlockAddress *B, void *Player);

//majuin player 1 petak
void pindahPlayer1(MonopolyMap map, void *Player );

//majuin player sesuai lemparan dadu
void pindahPlayer(MonopolyMap map, void *Player, int d );
#endif
