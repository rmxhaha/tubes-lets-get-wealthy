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
    *n1 = d6();
    *n2 = d6();

    printf("%d + %d = %d\n", *n1,*n2,*n1+*n2);
}
