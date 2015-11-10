#include "MonopolyMap.h"

MonopolyMap load_map(FILE* stream){
	int i,k,N;
	BlockAddress P,T,A;
	MonopolyMap map;
	
	N = 34;
	
	/**Load Block data*/
	// bulk allocate
	// asumsi malloc selalu berhasil
	A = malloc(sizeof(Block)*N);
	
	P = NULL;
	T = NULL;
	
	for( i = 1; i <= N; ++ i ){
		T = A + i - 1;
		T->id = i;
		
		block_load_from_bin(stream, T);
		
		
		if( i == 1 ){
			map.first = T;
		}
		else {
			P->map_next = T;

			// last
			if( i == N ){
				T->map_next = map.first;
			}
		}
		
		P = T;
	}
	
	/**load group data*/
	
	
}

