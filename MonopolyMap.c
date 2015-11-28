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


List ListPlayer; // giliran
List ListOffered; // list barang lelang
BlockAddress world_cup_city;
Address cplayer;



#define idx_player(arr,i,n,name_)\
	for( i = 0; i < n; ++ i )\
		if( name_[0] == arr[i].name[0] ) \
			break;

#define loop_map(map,BA,todo)\
	BA = map.first;\
	do {\
		todo;\
		BA = BA->map_next;\
	} while(BA != NULL);

typedef struct {
	int level;
	int owner_idx;
	int multiplier;
} BlockGameData;

#define ListBlockToArrayOfId(LB,P,BA,kotaIds,i)\
    n = NbElmt(LB);\
    i = 0;\
    loop_list(LB,P,\
        BA = Info(P);\
        kotaIds[i++] = BA->id; \
    );\

#define ArrayOfIdToListBlock(kotaIds,i,n,map,LB,BA)\
    CreateList(&(LB));\
	\
    for( i = 0; i < n; ++ i ){\
        BA = map->first;\
        do {\
            if( BA->id == kotaIds[i] ) break;\
            BA = BA->map_next;\
        } while( BA != NULL );\
		\
        InsVLast(&LB,BA);\
    }	

// make sure permission file is w+
void save_game(FILE* f,MonopolyMap map,boolean roll, boolean reroll, boolean upgraded){
    Player arr[MAX_PLAYER];
    int kotaIds[50];
	BlockGameData blocksData[50];

    int i,k;
    int n, nPlayer;
    Address P;
    PlayerAddress PA;
    BlockAddress BA;

    nPlayer = NbElmt(map.ListPlayer);
    i = 0;
    loop_list(map.ListPlayer,P,
        PA = Info(P);
        if( map.cplayer == P ) k = i;
        arr[i++] = *PA;
    );


    fwrite(&roll,sizeof(boolean),1,f);
    fwrite(&reroll,sizeof(boolean),1,f);
    //sudah upgrade?
    fwrite(&upgraded,sizeof(boolean),1,f);
	// num of player
    fwrite(&nPlayer,sizeof(int),1,f);

	// cplayer
    fwrite(&k,sizeof(int),1,f);

	// player data
    fwrite(&arr,sizeof(Player),nPlayer,f); // player meta data

    // player locations
    BA = map.first;
    do {
        if( !IsListEmpty(BA->list_player) ){
            loop_list(BA->list_player,P,
                PA = Info(P);
				idx_player(arr,i,nPlayer,PA->name);
                kotaIds[i] = BA->id;
            );
        }
        BA = BA->map_next;
    }while(BA!=NULL);


    fwrite(&kotaIds,sizeof(int),nPlayer,f);


	// ListOffered

	ListBlockToArrayOfId(map.ListOffered,P,BA,kotaIds,i);

    fwrite(&n,sizeof(int),1,f);
    fwrite(&kotaIds,sizeof(int),n,f);
	
	// List Blackout
	ListBlockToArrayOfId(map.ListBlackout,P,BA,kotaIds,i);

    fwrite(&n,sizeof(int),1,f);
    fwrite(&kotaIds,sizeof(int),n,f);


	// data block
	n = 0;
	loop_map(map,BA,
		blocksData[n].level = BA->level;
		if( BA->owner != NULL ){
            idx_player(arr,i,nPlayer,BA->owner->name);
            blocksData[n].owner_idx = i;
		}
		else {
            blocksData[n].owner_idx = -1;
		}
		blocksData[n].multiplier = BA->multiplier;
		n++;
	);

	// num of block
	fwrite(&n,sizeof(int),1,f);
	fwrite(&blocksData, sizeof(BlockGameData),n,f);

	
	// world_cup_city
	if( map.world_cup_city != NULL )
		k = map.world_cup_city->id;
	else
		k = -1;

	fwrite(&k, sizeof(int),1,f);

    fflush(f);
}


// make sure permission file is w+
void load_game(FILE* f,MonopolyMap* map,boolean *roll,  boolean *reroll, boolean *upgraded){
    Player *arr;
    int i,id, n,k, nPlayer;
    int kotaIds[50];
    BlockAddress BA;
    Address P;
	BlockGameData blocksData[50];


    fread(roll,sizeof(boolean),1,f);
    fread(reroll,sizeof(boolean),1,f);
    //sudah upgrade?
    fread(upgraded,sizeof(boolean),1,f);

	// num of player
    fread(&nPlayer,sizeof(int),1,f);

	// cplayer
    fread(&k,sizeof(int),1,f);


    // bulk allocate untuk players
    arr = malloc( sizeof(Player)*nPlayer );

	// player data
    fread(arr,sizeof(Player),nPlayer,f);

	// player locations
    fread(kotaIds,sizeof(int),nPlayer,f);

    CreateList(&(map->ListPlayer));
    for( i = 0; i < nPlayer; ++i )
    {
		// player data
        InsVLast(&map->ListPlayer,&arr[i]);

		// player location
		BA = map->first;
        do {
            if( BA->id == kotaIds[i] )
            {
                InsVFirst(&BA->list_player,&arr[i]);
                break;
            }

            BA = BA->map_next;
        } while( BA != NULL );
    }

	// cplayer
    P = First(map->ListPlayer);
    for( i = 0; i < k; ++ i ) P = Next(P);
    map->cplayer = P;



	// ListOffered
    fread(&n,4,1,f);
    fread(&kotaIds,sizeof(int),n,f);

	ArrayOfIdToListBlock(kotaIds,i,n,map,map->ListOffered,BA);

	// ListBlackout
	fread(&n,4,1,f);
    fread(&kotaIds,sizeof(int),n,f);
	ArrayOfIdToListBlock(kotaIds,i,n,map,map->ListBlackout,BA);


	// data block
	fread(&n,sizeof(int),1,f);
	fread(&blocksData, sizeof(BlockGameData),n,f);

	i = 0;
	loop_map((*map),BA,
		BA->level = blocksData[i].level;
		BA->multiplier = blocksData[i].multiplier;
		if( blocksData[i].owner_idx != -1 )
            BA->owner = &arr[ blocksData[i].owner_idx ];
        else
            BA->owner = NULL;
		++i;
	);
	
	// world_cup_city
	fread(&k,sizeof(int),1,f);
	
	map->world_cup_city = NULL;
	if( k != -1 )
	{
		BA = map->first;
		do {
			if( BA->id == k ){
				map->world_cup_city = BA;
				break;
			}
			BA = BA->map_next;
		} while( BA != NULL );
	}

}

