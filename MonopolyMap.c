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

        block_init(T);
		block_load_from_bin(stream, T);

		T -> id = i + 1; // jangan pernah di rubah bahaya !!!

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
	CreateList(&map.ListPlayer);

	/*List offered*/
	CreateList(&map.ListOffered);
    /*List blackout*/
    CreateList(&map.ListBlackout);
    /*init world cup*/
    map.world_cup_city = NULL;
    return map;
}

void print_map(MonopolyMap map ){
	BlockAddress tpeta[9][9];
	Address PP; // Player

	memset(tpeta,0,sizeof(tpeta)); // fill with NULL
	int i,k;
	char tmpstr[100];
	char *s;

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
				tmpstr[0] = '\0';
				strcat(tmpstr, P->owner->name );
				s = tmpstr + strlen(tmpstr);
                /*print level bangunan*/
                if(P->level!=0)
                {
					sprintf(s,"%d",P->level);
				}

				printf("%10s", tmpstr);
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

#define loop_map(map,BA,todo)\
	BA = (map).first;\
	do {\
		todo;\
		BA = BA->map_next;\
	} while(BA != NULL);

typedef struct {
	int level;
	int owner_idx;
	int multiplier;
} BlockGameData;


char name[5];
int money;
int revolution_count;
Chance save_chance;
boolean world_cup_holder;

#define PrintPlayer(f,PA)\
    fprintf(f,"%c ",PA->name[0]);\
    fprintf(f,"%d ",PA->money);\
    fprintf(f,"%d ",PA->revolution_count);\
    fprintf(f,"%d ",PA->save_chance);\
    fprintf(f,"%u\n",PA->world_cup_holder);

#define SearchBlockById(map,BA,idx)\
	loop_map(map,BA, if( BA->id == idx ) break; );
#define SearchPlayerById(map,P,PA,id, i)\
	i = 0;\
	loop_list((map).ListPlayer,P, PA = Info(P); if( i == id ) break; ++i );

// make sure permission file is w+
void save_game(FILE* f,MonopolyMap map,boolean reroll, boolean upgraded){
    Player arr[MAX_PLAYER];
    int kotaIds[50];
	BlockGameData blocksData[50];

    int i,k;
    int n, nPlayer;
    Address P,Q;
    PlayerAddress PA;
    BlockAddress BA;

    nPlayer = NbElmt(map.ListPlayer);
    i = 0;
    loop_list(map.ListPlayer,P,
        if( map.cplayer == P ){ k = i; break; }
        ++ i;
    );

    fprintf(f,"%u %u\n",reroll,upgraded);
    fprintf(f,"%d\n",nPlayer);

    fprintf(f,"%d\n",k);

	// player data
	loop_list(map.ListPlayer,P,
        PA = Info(P);
        PrintPlayer(f,PA);
    );

    // player locations
    BA = map.first;
    do {
        if( !IsListEmpty(BA->list_player) )
        {
            loop_list(BA->list_player,P,
                PA = Info(P);

                i = 0;
                loop_list(map.ListPlayer,Q,
                    if(Info(P) == Info(Q)) break;
                    ++i;
                );
                kotaIds[i] = BA->id;
            );
        }
        BA = BA->map_next;
    }while(BA!=NULL);

    for( i = 0; i < nPlayer; ++ i ){
        fprintf(f,"%d ",kotaIds[i]);
    }
    fprintf(f,"\n");


	// ListOffered
	fprintf(f,"%d\n",NbElmt(map.ListOffered));
    loop_list(map.ListOffered,P,
        BA = Info(P);
        fprintf(f,"%d ",BA->id);
    );
	fprintf(f,"\n");


	// List Blackout
	fprintf(f,"%d\n",NbElmt(map.ListBlackout));
    loop_list(map.ListBlackout,P,
        BA = Info(P);
        fprintf(f,"%d ",BA->id);
    );
	fprintf(f,"\n");


	// data block
	loop_map(map,BA,
		if( BA->owner != NULL ){
            loop_list(map.ListPlayer,Q,
                if(BA->owner == Info(Q)) break;
                ++i;
            )
		}
		else {
            i = -1;
		}

        fprintf(f,"%d %d %d\n",
                i,
                BA->level,
                BA->multiplier
            );
		n++;
	);


	// world_cup_city
	if( map.world_cup_city != NULL )
		k = map.world_cup_city->id;
	else
		k = -1;

    fprintf(f,"%d\n",k);
}


// make sure permission file is w+
void load_game(FILE* f,MonopolyMap* map,boolean *reroll, boolean *upgraded){
    Player *arr;
    int kotaIds[50];
	BlockGameData blocksData[50];

    int i, k, j;
    int n, nPlayer;
    Address P,Q;
    PlayerAddress PA;
    BlockAddress BA;


    fscanf(f,"%u%u",reroll,upgraded);
    fscanf(f,"%d",&nPlayer); // number of player
    fscanf(f,"%d",&k); // cplayer
	arr = malloc( nPlayer* sizeof(Player) );

	// player data
	for( i = 0; i < nPlayer; ++ i ){
		PA = arr+i;

        fscanf(f,"%s",&PA->name);
        fscanf(f,"%d",&PA->money);
        fscanf(f,"%d",&PA->revolution_count);
        fscanf(f,"%d",&PA->save_chance);
        fscanf(f,"%u",&PA->world_cup_holder);

		InsVLast(&map->ListPlayer,arr + i);

		if( i == k ){
            P = First(map->ListPlayer);
            while( Next(P) != Nil ) { P = Next(P); }
			map->cplayer = P;
		}
	}

    // player locations
    for( i = 0; i < nPlayer; ++ i ){
        fscanf(f,"%d",&j);

		printf("%d\n",j);
		SearchBlockById(*map,BA,j);
		InsVFirst( &BA->list_player, arr+i );
    }

	// ListOffered
	fscanf(f,"%d",&n);
    for( i = 0; i < n; ++ i ){
        fscanf(f,"%d",&j);
		SearchBlockById(*map,BA,j);
		InsVFirst(&map->ListOffered,BA);
    }

	// List Blackout
	fscanf(f,"%d",&n);
    for( i = 0; i < n; ++ i ){
        fscanf(f,"%d",&j);
		SearchBlockById(*map,BA,j);
		InsVFirst(&map->ListBlackout,BA);
    }




	// data block
	loop_map(*map,BA,
		fscanf(f,"%d%d%d",&i,&BA->level,&BA->multiplier);
		printf("%d %d %d\n", i, BA->level, BA->multiplier );
		// i is id
		if( i == -1 ){
			BA->owner = NULL;
		}
		else {
			SearchPlayerById(*map,P,PA,i,k);
			BA->owner = PA;
		}
	);


	// world_cup_city
	fscanf(f,"%d",&k);
	if( k == -1 ){
		map->world_cup_city = NULL;
	}
	else {
		SearchBlockById(*map,BA,k);
		map->world_cup_city = BA;
	}

}
