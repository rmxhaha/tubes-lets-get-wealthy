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
        printf("Biaya sewa: ");
        print_money((b->multiplier)*(b->tab_denda[b->level]));
        printf("\n");
        printf("Biaya ambil alih : ");
        print_money(2*b->tab_harga[b->level]);
        printf("\n");
        if(b->level == 4)
        {
            printf("Biaya upgrade bangunan : upgrade sudah maksimum\n");
        }
        else
        {
            printf("Biaya upgrade bangunan : ");
            print_money(b->tab_harga[b->level+1]);
            printf("\n");
        }
    }
    else
    {
        printf("tidak ditemukan\n");
    }
}
