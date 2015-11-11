#include "MonopolyMap.h"

MonopolyMap load_map(FILE* stream){
	int i,k,N;
	BlockAddress P,T,A;
	MonopolyMap map;

	N = 32;

	/**Load Block data*/
	// bulk allocate
	// asumsi malloc selalu berhasil
	A = malloc(sizeof(Block)*N);

	P = NULL;
	T = NULL;

	for( i = 0; i < N; ++ i )
	{
		T = A + i;
		T->id = i + 1;

        block_init(T);
		block_load_from_bin(stream, T);


		if( i == 0 ){
			map.first = T;
		}
		else {
			P->map_next = T;

			// last
			if( i == N-1 ){
				T->map_next = map.first;
			}
		}

		if( i % 8 != 0 )
		{
			P->line_next = T;
			T->line_prev = P;
		}

		P = T;
	}

	/**load group data*/

    return map;
}

