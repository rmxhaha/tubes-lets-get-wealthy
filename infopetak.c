#include "infopetak.h"

void block_info_petak(MonopolyMap map)
{
    BlockAddress b;
    char nameinput[255], nametemp[255];
    char c;
    boolean found;
    int i = 0;
    int a = 0 ;
    //printf("masuk");
    scanf("%c",&c);
    while(c!='>')
    {
        nameinput[i]=c;
        //printf("%c",nameinput[i]);
        i++;
        scanf("%c",&c);
    }
    nameinput[i] = '>';
    nametemp[i++] = '\0';
    //ambil nama kotanya saja
    if((nameinput[0]=='i')&&(nameinput[1]=='n')&&(nameinput[2]=='f')&&(nameinput[3]=='o')&&(nameinput[4]=='<')&&(nameinput[strlen(nameinput)-1]=='>'))
    {
        for(i=5; i<strlen(nameinput)-1;i++)
        {
            nametemp[a]=nameinput[i];
            a++;
        }
    }
    nametemp[a]='\0';
    //printf("tess %s\n",nametemp);
    found = false;
    b = map.first;
    do
    {
        if(strcmp(nametemp,b->name)==0)
        {
            found = true;
        }
        else
        {
           b = b->map_next;
        }
    }
    while(!found && b != map.first);
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
        if(b->level==5)
        {
            printf("di landmark\n");
        }
        else
        {
            printf("%d\n",(b->level++));
        }
        printf("Biaya sewa: %d\n",b->tab_harga[b->level]);
        printf("Biaya ambil alih : %d\n",b->tab_harga[b->level]);
        printf("Biaya upgrade bangunan : %d\n",(2*b->tab_harga[b->level]));
    }
    else
    {
        printf("tidak ditemukan\n");
    }
}
