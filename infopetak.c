#include "infopetak.h"

void block_info_petak(MonopolyMap map, char* namatempat)
{
    BlockAddress b;
    boolean found;

    //mencari nama kota
    found = false;
    b = (map).first;
    do
    {
        if(strcmp(namatempat,b->name)==0)
        {
            found = true;
        }
        else
        {
           b = b->map_next;
        }
    }
    while(!found && b != NULL);

    if(found)
    {
        printf("%s, pemilik properti ",b->name);
        if((b->owner->name)==NULL)
        {
            printf("tidak ada, ");
        }
        else
        {
            printf("%s, ",b->owner->name);
        }
        printf("bangunan level: ");
        if(b->level==4)
        {
            printf("di landmark\n");
        }
        else
        {
            printf("%d\n",(b->level));
        }
        printf("Biaya sewa: %d\n",(b->multiplier)*(b->tab_harga[b->level]));
        printf("Biaya ambil alih : %d\n",b->tab_harga[b->level]);
        printf("Biaya upgrade bangunan : %d\n",(2*b->tab_harga[b->level]));
    }
    else
    {
        printf("tidak ditemukan\n");
    }
}
