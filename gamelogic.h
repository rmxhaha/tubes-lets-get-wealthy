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
void pindahPlayer(MonopolyMap, Player*, int d );


#endif