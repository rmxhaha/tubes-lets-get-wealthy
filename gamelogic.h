#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "Block.h"
#include "Player.h"
#include "MonopolyMap.h"


/**
	cari lokasi player pada peta
*/
BlockAddress search_player(MonopolyMap,PlayerAddress);

/**
	Spec :
		kalau di nyampe ujung map 
		- mulai dari map.first lagi 
		kalau melewati start maka  
		- revolution_count di tambah
		- jika revolution_count != 1 maka duit di tambah 150k
*/
void pindah_player(MonopolyMap, PlayerAddress, int d );

/**
	Spec :
		input jumlah player kalau lebih dr 4 atau kurang dari 2 maka input ulang
		inisialisasi MapPlayer dengan jumlah player sesuai input
*/
void pick_jumlah_player(MonopolyMap* map);

/**
	Spec : 
		pada putaran pertama hanya bisa membeli hingga level 2 
		pada putaran selanjutnya bisa membeli hingga level 3 
		landmark bisa di beli jika gedung sudah level 3 dan di putaran setelah pembelian gedung level 3
	Note :
		putaran player selesai setelah buy process
*/

void process_buy(MonopolyMap,PlayerAddress);
	
#endif