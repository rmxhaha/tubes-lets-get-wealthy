#include "MonopolyMap.h"

MonopolyMap load_map(FILE* stream){
	int i,k,N,M;
	BlockAddress P,Q,T,A;
	PlayerAddress PA;
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
				T->map_next = NULL;
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
			} while( P != NULL );

		}
	}

	/*List Player */
	CreateList(&map.ListTurn);

	/*List offered*/
	CreateList(&map.ListOffered);


    return map;
}

void print_map(MonopolyMap map ){
	BlockAddress tpeta[9][9];
	Address PP; // Player

	memset(tpeta,0,sizeof(tpeta)); // fill with NULL
	int i,k;
	char tmpstr[100];

	BlockAddress
		P,T,
		L1,L2,L3,L4;

	L1 = map.first;
	find_last_in_line(P,L1);
	L2 = P->map_next;
	find_last_in_line(P,L2);
	L3 = P->map_next;
	find_last_in_line(P,L3);
	L4 = P->map_next;

	i = 0;
	iterate_line(P,L1,NULL,tpeta[0][i++] = P;);
	i = 0;
	iterate_line(P,L2,NULL,tpeta[i++][8] = P;);
	i = 8;
	iterate_line(P,L3,NULL,tpeta[8][i--] = P;);
	i = 8;
	iterate_line(P,L4,NULL,tpeta[i--][0] = P;);

	for( i = 0; i < 9; ++ i ){
		for( k = 0; k < 9; ++ k ){
			P = tpeta[i][k];
			if( P == NULL )
				printf("          ");
			else
				printf("%10s", P->name );
		}
		printf("\n");

		for( k = 0; k < 9; ++ k ){
			P = tpeta[i][k];
			if( P == NULL )
				printf("          ");
			else{
                switch(P->type){
                case TANAH:
                case PARIWISATA:
                    printf("%10d", P->tab_harga[P->level] );
                    break;
                default:
                    printf("          ");
                }
			}
		}
		printf("\n");

		for( k = 0; k < 9; ++ k ){
			P = tpeta[i][k];
			if( P == NULL || P->owner == NULL )
				printf("          ");
			else{
				printf("%10s", P->owner->name );

			}
		}

		printf("\n");

		for( k = 0; k < 9; ++ k ){
			P = tpeta[i][k];
			if( P == NULL )
				printf("          ");
			else{

//				printf("          ");

				tmpstr[0] = '\0';
				loop_list(P->list_player,PP,
					strcat(tmpstr,((Player*)Info(PP))->name);
				);
				printf("%10s",tmpstr);
			}
		}
		printf("\n");
	}
}
