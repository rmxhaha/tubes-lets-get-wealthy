#ifndef PLAYER_H
#define PLAYER_H

// jika bank maka Player *player adalah NULL
typedef enum {
	GOTO_PAJAK,
	GOTO_PENJARA,
	GOTO_START,
	GOTO_KELILING_DUNIA,
	BEBAS_PENJARA,
	MATI_LAMPU,
	PERLINDUNGAN,
	BEBAS_SEWA
} Chance;

typedef struct TPlayer *PlayerAddress;
typedef struct TPlayer {
	char name[5];
	int money;
	int revolution_count;
	Chance save_chance;
	BlockAddress cblock;
	PlayerAddress next;
} Player;

#endif
