#include <stdlib.h>
#include "Chance.h"

Chance get_chance() {
	//Memilih kartu chance secara random
	int x;

	x = rand()%11;
	return x;
}
