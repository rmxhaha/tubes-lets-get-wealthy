#include "MonopolyMap.h"

MonopolyMap load_map(FILE* stream){
	int i,k,N,M;
	BlockAddress P,Q,T,A;
	MonopolyMap map;
	char nama_kota[255];

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

	fscanf(stream,"%d",&N);
	for( i = 0; i < N; ++ i ){

		Q = NULL;
		fscanf(stream,"%d",&M);
		for( k = 0; k < M; ++ k ){

			fscanf(stream,"%s",nama_kota);

			P = map.first;
			do {
				if( strcmp( P->name, nama_kota ) == 0 ){
					if( Q == NULL ){
						Q = P;
					}
					else {
						Q->group_next = P;
						P->group_prev = Q;
					}

					break;
				}
				P = P->map_next;
			} while( P != map.first );
			
		}
	}


    return map;
}

