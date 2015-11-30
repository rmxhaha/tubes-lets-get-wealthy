#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "Block.h"
#include "Player.h"
#include "MonopolyMap.h"



#define BONUS_MONEY_PER_REVOLUTION 150000

boolean is_tourism (MonopolyMap map);
//mengembalikan true apabila di block terdapat player(tidak spesifik player mana)
boolean is_player_on(BlockAddress B);

//mengembalikan true apabila seorang player belum punya tanah
boolean is_player_belum_punya_tanah(MonopolyMap map, PlayerAddress player);

//true kalo semua pemain belum ada yang punya tanah
boolean is_semua_player_belum_punya_tanah (MonopolyMap map);

//true kalo semua pemain lainnya belum ada yang punya tanah
boolean is_semua_player_lainnya_belum_punya_tanah (MonopolyMap map, PlayerAddress current_player);

//mengembalikan BlockAddress berdasarkan input nama block, atau NULL
BlockAddress search_block_by_name(MonopolyMap map, char* namatempat);

//mengembalikan BlockAddress di mana player berada, atau NULL
BlockAddress search_player(MonopolyMap map,PlayerAddress player);

//masukin player ke block
void place_player(BlockAddress B, PlayerAddress player);

//majuin player 1 petak
void pindah_player1(MonopolyMap *map, PlayerAddress player );


/**
    kalau di nyampe ujung map
    - mulai dari map.first lagi
    kalau melewati start maka
    - revolution_count di tambah
    - jika revolution_count != 1 maka duit di tambah 150k
*/

//majuin player sesuai lemparan dadu
void pindah_player(MonopolyMap *map, PlayerAddress player, int d );

void pick_jumlah_player(MonopolyMap* map);


/**
    Meningkatkan level gedung
    jika gedung bukan milik player atau uang tidak cukup tampilkan pesan kesalahan
*/

void process_upgrade(MonopolyMap,PlayerAddress);


/**
    memindahkan player dari satu tempat ke block tujuan
    I.S. bpindah harus ada dalam map
*/
void pindah_player_ke(MonopolyMap *map,PlayerAddress player, BlockAddress bpindah);

void do_chance (MonopolyMap *map, PlayerAddress *P);
void bayar_pajak(MonopolyMap *map,PlayerAddress *P);
void sell_bank (PlayerAddress P, BlockAddress *B);

void player_bangkrut(MonopolyMap *map, PlayerAddress *player);
//True wajib
//-jika terdapat 1 atau kurang pemain di map, dengan asumsi
// pemain yang uangnya habis di-remove dari map.
//
//True Opsional
//-apabila terdapat pemain yang memiliki semua petak rekreasi
//-apabila terdapat pemain yang memiliki seluruh petak di tiga blok
boolean is_game_finished(MonopolyMap);


/**
    menulis uang dengan format
        4B242
        4M500
        200K300
*/
void print_money( int money );

/**
    menulis ListPlayer ke layar dengan format
    > nama1 jumlah_uang1
      nama2 jumlah_uang2
*/
void print_leaderboard(MonopolyMap);

/**
    memasukan block pada List Penjualan (ListOffered)
    1. jika block tidak ditemukan berikan pesan kesalahan
    2. jika block bukan milik player penjual beri pesan kesalahan
    3. jika block belum ada pada list penjualan tambahkan ke list penjualan
*/
void sell(MonopolyMap* map,Player* cplayer, char *nama_petak);

/**
    membeli dari list penjualan  (ListOffered)
    1. jika nama petak yang disebutkan tidak ada maka
*/
void buyoffered(MonopolyMap*, Player* buyer, char* nama_petak,boolean *upgraded);

/**

*/
void showoffered(MonopolyMap*);


/**
    membeli tanah jika
    1. masih kosong gunakan tab_harga[0]
        cek apakah uang cukup
        tampilkan pesan berhasil atau gagal
    2. tidak kosong, beli paksa dengan harga  kumulatif (tab_harga[level]) * 2

*/
void buy(MonopolyMap *map, PlayerAddress P,boolean *upgraded);

/**
    upgrade gedung pada tanah
    1. menambah level gedung jika uang mencukupi
    2. memberikan pesan jika uang tidak cukup
*/
void upgrade(MonopolyMap map, PlayerAddress *P,boolean *upgraded);


void endturn (MonopolyMap* map);

void dapet_Bonust(PlayerAddress player);

void protect(BlockAddress protect_target, MonopolyMap *map, PlayerAddress player);

void updateBlockStatus(MonopolyMap map);

void heal_blackout_status( MonopolyMap* map, BlockAddress target);

int total_aset_player(MonopolyMap map, PlayerAddress player);
#endif
