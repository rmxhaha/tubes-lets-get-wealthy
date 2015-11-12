#include<time.h>


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
void lempar_Dadu(int *n1, *n2)
{
    char s;
    boolean redo;
    *n = 0; // *n adalah akumulasi jumlah dadu.

    do
    {
        redo = false;
        *n1 = dadu();
        *n2 = dadu();

        printf("%d + %d = %d\n", d1, d2, d1+d2);

        //kalo snake eyes
         if(d1==d2)
        {
            printf("Snake Eyes   ");
            printf("Re-Roll? (y/n");

            do//diulang ampe input bener
            {
                scanf(" %c", &s);
            }while((s != y) && (s != n))

            if(s == 'y')
            {
                redo = true;
            }

        }
    }
}
