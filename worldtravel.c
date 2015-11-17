#include "worldtravel.h"
void player_travel(MonopolyMap map, PlayerAddress player,char* namatempat)
{
    //syarat: orang sampe di petak travel
    BlockAddress b;
    //cari travel itu blockaddress nya berapa
    b = search_block_by_name(map,namatempat);
    if(b!=Nil)
    {
       pindah_player_ke(&map, player,b);
       printf("Selamat! Sekarang anda berada di %s\n",b->name);
    }
    else
    {
        printf("anda tidak bisa ke sana\n"); /*di deskripsi soal tulisannya nama kota, jd asumsi gaboleh ke start chance lalala cuma bole ke rekreasi / kota.*/
    }
}
