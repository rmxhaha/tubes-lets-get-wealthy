#include <stdlib.h>
#include "Chance.h"

Chance get_chance() {
	//Memilih kartu chance secara random
	int x;

	x = rand()%10;
	return (x + 1);
}
