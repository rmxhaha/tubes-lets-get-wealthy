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
void pindah_player1(MonopolyMap map, void *Player );

//majuin player sesuai lemparan dadu
void pindah_player(MonopolyMap map, void *Player, int d );

void pick_jumlah_player(MonopolyMap map);



/**
	Spec :
		pada putaran pertama hanya bisa membeli hingga level 2
		pada putaran selanjutnya bisa membeli hingga level 3
		landmark bisa di beli jika gedung sudah level 3 dan di putaran setelah pembelian gedung level 3
		<Spec di atas tidak di temukan di file tugas>


*/

void process_buy(MonopolyMap,PlayerAddress);

void process_upgrade(MonopolyMap,PlayerAddress);

void pindah_player_ke(MonopolyMap,PlayerAddress, BlockAddress);

void do_chance (MonopolyMap *map, PlayerAddress *P);

//True wajib
//-jika terdapat 1 atau kurang pemain di map, dengan asumsi
// pemain yang uangnya habis di-remove dari map.
//
//True Opsional
//-apabila terdapat pemain yang memiliki semua petak rekreasi
//-apabila terdapat pemain yang memiliki seluruh petak di tiga blok
boolean is_game_finished(MonopolyMap);

#endif
