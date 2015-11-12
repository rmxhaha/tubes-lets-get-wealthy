#include "dadu.h"


//dipanggil sekali aja di awal, jangan berulang.
void set_Random()
{
    srand((unsigned)time(NULL));
}


//kalo nggak pake set_random, rentetan angka akan sama
//mengeluarkan nilai random 1-6
int d6()
{
    int n;

    n = rand();
    return((n%6)+1);
}

// [masil blom ada yang buat pindah petak]
// menghasilkan 2 angka hasil lemparan dadu
void lempar_Dadu(int *n1, int *n2)
{
    char s;
    boolean redo;

    do
    {
        redo = false;
        *n1 = d6();
        *n2 = d6();

        printf("%d + %d = %d\n", *n1,*n2,*n1+*n2);

        //kalo snake eyes
         if(*n1==*n2)
        {
            printf("Snake Eyes   ");
            printf("Re-Roll? (y/n");

            do//diulang ampe input bener
            {
                scanf(" %c", &s);
            }while((s != 'y') && (s != 'n'));

            if(s == 'y')
            {
                redo = true;
            }

        }
    } while( redo );
}
