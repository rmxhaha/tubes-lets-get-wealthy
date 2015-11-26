/* Nama/ NIM		: Candra Ramsi/13514090
 * Nama file		: listlinier.c
 * Topik		    : list
 * Tanggal		    : 15 oktober 2015
 * Deskripsi		: list lanjar
*/

#include "listlinier.h"

/*
	LIST INI MERUPAKAN VARIASI 1 - FISIK POINTER DENGAN FIRST EKSPLISIT

	BEBERAPA DEFINISI
	1. List Kosong -> First(L) bernilai Nil
	2. Elemen terakhir, bila Next(P) adalah Nil, maka P merupakan alamat elemen terakhir pada list

	CATATAN TEKNIS TENTANG EXECUTION FAULIRE
	1. Autograder akan menangani stackoverflow. Stackoverflow maupun alokasi memori yang buruk akan menyebabkan execution failure.
	   Memori Limit adalah 16Mb. Test Case dijamin tidak akan melebihi 100 elemen, sehingga memori limit yang diberikan sudah SANGAT BERLEBIH untuk kondisi
	   tidak terjadi stackoverflow.
	2. Hati-hati terhadap segmentation fault, akseslah memori yang benar.
	3. Operasi terhadap pointer harus hati-hati, jangan mengakses pointer yang sudah di-free.
	4. Cek berbagai macam kondisi, misal saat prekon disebutkan kondisi sembarang, cek untuk kasus kosong dan kasus isi
	5. Untuk kesalahan umum pada C programming, bacalah http://www.cs.mun.ca/~michael/c/problems.html

	LAIN-LAIN
	1. Untuk penjelasan detail skema pemrosesan list serta fungsional list linear, silahkan melihat diktat/slide kuliah
	2. Bila terdapat perbedaan versi header asisten dengan modul, ikuti versi asisten. Informasi perbedaan ada pada tiap fungsi/prosedur
*/



boolean IsListEmpty (List L){
/* Mengirim true jika list kosong */
	return_boolean(First(L) == Nil);
}

void CreateList (List *L){
/*	I.S. sembarang
	F.S. Terbentuk list kosong
*/
	First(*L) = Nil;
}

Address Alokasi (Infotype X){
/*	Mengirimkan Address hasil alokasi sebuah elemen
	Jika alokasi berhasil, maka Address tidak Nil, dan misalnya menghasilkan P, maka
	Info(P) = X, Next(P) = Nil
	Jika alokasi gagal, mengirimkan Nil
*/

	Address P = (Address)malloc( sizeof( ElmtList ) );
	if( P == NULL ) return Nil;

	Info(P) = X;
	Next(P) = Nil;

	return P;
}

void Dealokasi (Address *P){
/*	I.S. P terdefinisi
	F.S. P dikembalikan ke sistem
	Melakukan dealokasi/pengembalian Address P
*/
	free( *P );
	*P = Nil;
}

// PENCARIAN SEBUAH ELEMEN LIST
Address Search (List L, Infotype X){
/*	Mencari apakah ada elemen list dengan Info(P) = X
	Jika ada, mengirimkan Address elemen tersebut
	Jika tidak ada, mengirimkan Nil
*/
	Address P;
	find_list( L, P, Info(P) == X );

	return P;
}

boolean FSearch (List L, Address P){
/*	Mencari apakah ada elemen list yang beralamat P
	Mengirimkan true jika ada, false jika tidak ada
*/
/*
	Address it;
	it = First(L);

	while( it != Nil ){
		if( it == P ) return it;
		it = Next(it);
	}

	return Nil;
	*/
	Address it;
	find_list( L, it, it == P );
	return_boolean( it != Nil );
}

Address SearchPrec (List L, Infotype X){
/*	Mengirimkan Address elemen sebelum elemen yang nilainya = X
	Mencari apakah ada elemen list dengan Info(P) = X
	Jika ada, mengirimkan Address Prec, dengan Next(Prec) = P dan Info(P) = X
	Jika tidak ada, mengirimkan Nil
	Jika P adalah elemen pertama, maka mengirimkan Nil
	Search dengan spesifikasi seperti ini menghindari traversal ulang jika setelah
	Search akan dilakukan operasi lain
*/
	Address P, Prec;
	P = First(L);
	Prec = Nil;

	while( P != Nil ){
		if( Info(P) == X ) return Prec;
		Prec = P;
		P = Next(P);
	}

	return Nil;
}

//PENAMBAHAN ELEMEN
void InsVFirst (List *L, Infotype X){
/*	I.S. L mungkin kosong
	F.S. X ditambahkan sebagai elemen pertama L
	Proses : Melakukan alokasi sebuah elemen dan menambahkan elemen pertama dengan
	nilai X jika alokasi berhasil.
	Jika alokasi gagal: I.S.= F.S.
*/
    Address front = Alokasi(X);

    Next(front) = First(*L);
    First(*L) = front;
}

void InsVLast (List *L, Infotype X){
/*	I.S. L mungkin kosong
	F.S. X ditambahkan sebagai elemen terakhir L
	Proses : Melakukan alokasi sebuah elemen dan menambahkan elemen list di akhir :
	elemen terakhir yang baru bernilai X jika alokasi berhasil.
	Jika alokasi gagal: I.S.= F.S.
*/
    Address P;
    Address T = Alokasi(X);

    // kosong
    if( First(*L) == Nil )
        First(*L) = T;
    else {
		loop_list(*L,P,if(Next(P)==Nil) break;/*kosong*/);

        Next(P) = T;
    }
}

//PENGHAPUSAN ELEMEN
void DelVFirst (List *L, Infotype *X){
/*	I.S. List L tidak kosong
	F.S. Elemen pertama list dihapus : nilai info disimpan pada X
	dan alamat elemen pertama di-dealokasi
*/
    *X = Info(First(*L));
    First(*L) = Next(First(*L));
}

void DelVLast (List *L, Infotype *X){
/*	I.S. list tidak kosong
	F.S. Elemen terakhir list dihapus : nilai info disimpan pada X
	dan alamat elemen terakhir di-dealokasi
*/
    Address P = First(*L);
    Address Prec = Nil;

    while( Next(P) != Nil ){
        Prec = P;
        P = Next(P);
    }

    if( Prec == Nil ){
		*X = Info(First(*L));
        First(*L) = Nil;
    }
    else {
		*X = Info(P);
        Dealokasi(&P);
		Next(Prec) = Nil;
    }
}

//PRIMITIF BERDASARKAN ALAMAT
//PENAMBAHAN ELEMEN BERDASARKAN ALAMAT
void InsertFirst (List *L, Address P){
/*	I.S. Sembarang, P sudah dialokasi
	F.S. Menambahkan elemen ber-Address P sebagai elemen pertama
*/
    Next(P) = First(*L);
    First(*L) = P;
}

void InsertAfter (List *L, Address P, Address Prec){
/*	I.S. Prec pastilah elemen list dan bukan elemen terakhir,
	P sudah dialokasi
	F.S. Insert P sebagai elemen sesudah elemen beralamat Prec
*/
    Next(P) = Next(Prec);
    Next(Prec) = P;
}

void InsertLast (List *L, Address T){
/*	I.S. Sembarang, P sudah dialokasi
	F.S. P ditambahkan sebagai elemen terakhir yang baru
*/
    Address P = First(*L);

    // kosong
    if( P == Nil )
        First(*L) = T;
    else {
        while( Next(P) != Nil )
            P = Next(P);

        Next(P) = T;
    }
}

//PENGHAPUSAN SEBUAH ELEMEN
void DeleteFirst (List *L, Address *P){
/*	I.S. List tidak kosong
	F.S. P adalah alamat elemen pertama list sebelum penghapusan
	Elemen list berkurang satu (mungkin menjadi kosong)
	First element yang baru adalah suksesor elemen pertama yang lama
*/
    *P = First(*L);
    First(*L) = Next(First(*L));
}

void DeleteP (List *L, Infotype X){
/*	I.S. Sembarang
	F.S. Jika ada elemen list ber-Address P, dengan Info(P) = X
	Maka P dihapus dari list dan di-dealokasi
	Jika tidak ada elemen list dengan Info(P) = X, maka list tetap
	List mungkin menjadi kosong karena penghapusan
*/
    Address P;
    Address Prec;

	if( IsListEmpty(*L) ){
		return;
	}

	if( Info(First(*L)) == X ){
		DeleteFirst(L,&P);
		Dealokasi(&P);
	}
	else {
		Prec = SearchPrec(*L,X);
		if( Prec != Nil ){
			P = Next(Prec);
			Next(Prec) = Next(P);

			Dealokasi(&P);
		}
	}
}

void DeleteLast (List *L, Address *P){
/*	I.S. List tidak kosong
	F.S. P adalah alamat elemen terakhir list sebelum penghapusan
	Elemen list berkurang satu (mungkin menjadi kosong)
	Last element baru adalah predesesor elemen pertama yang lama, jika ada

	CATATAN
	P adalah parameter Input/Output
*/
	Address T;
	Address Prec;
	loop_list(*L, T, if(Next(T) == Nil) break; Prec = T; );

	Next(Prec) = Nil;
	*P = T;
}

void DeleteAfter (List *L, Address *Pdel, Address Prec){
/*	I.S. List tidak kosong. Prec adalah anggota list L.
	F.S. Menghapus Next(Prec) : Pdel adalah alamat elemen list yang dihapus
*/
	*Pdel = Next(Prec);
	Next(Prec) = Next(Next(Prec));
}

//PROSES SEMUA ELEMEN LIST
void PrintInfo (List L){
/*	I.S. List mungkin kosong
	F.S. Jika list tidak kosong,
	Semua info yg disimpan pada elemen list diprint dengan format [elemen-1, elemen-2, elemen-3, ...]
	Jika list kosong, hanya menuliskan "[]"
*/
	Address P;
	if( IsListEmpty(L) )
		printf("[]");
	else{
		printf("[");
		P = First( L );
		while( P != Nil ){
			printf("%d", Info(P));
			if( Next(P) != Nil ) printf(", ");
			P = Next(P);
		}
		printf("]");
	}

	printf("\n");
}

int NbElmt (List L){
/*	Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
	int c = 0;
	Address P;
	loop_list( L, P, c++ );

	return c;
}

// Prekondisi untuk Max/Min/rata-rata : List tidak kosong
Infotype Max (List L){
/*	Mengirimkan nilai Info(P) yang maksimum */
	Address P;
	Infotype max = Info( First(L) );
	loop_list( L, P, if( Info(P) > max ) max = Info(P) );

	return max;
}

Address AdrMax (List L){
/*	Mengirimkan Address P, dengan Info(P) yang bernilai maksimum */
	Address P;
	Address MP = First(L);
	loop_list( L, P, if( Info(P) > Info(MP) ) MP = P; );

	return MP;
}

Infotype Min (List L){
/*	Mengirimkan nilai Info(P) yang minimum */
	Address P;
	Infotype min = Info( First(L) );
	loop_list( L, P, if( Info(P) < min ) min = Info(P) );

	return min;
}

Address AdrMin (List L){
/*	Mengirimkan Address P, dengan Info(P) yang bernilai minimum */
	Address P;
	Address MP = First(L);
	loop_list( L, P, if( Info(P) < Info(MP) ) MP = P; );

	return MP;
}

//PROSES TERHADAP LIST
void DeleteAll (List *L){
/*	Delete semua elemen list dan alamat elemen di-dealokasi
	I.S. : L terdefinisi, boleh kosong
	F.S. : Jika L tidak kosong, semua elemen list di-delete dan didealokasi
*/
	Address P;
	Address T;

	P = First(*L);
	while( P != Nil){
		T = Next(P);
		Dealokasi(&P);
		P = T;
	}

	First(*L) = Nil;
}

void InversList (List *L){
/*	I.S. L terdefinisi, boleh kosong
	F.S. Elemen list L dibalik :
	Elemen terakhir menjadi elemen pertama, dan seterusnya.
	Membalik elemen list, tanpa melakukan alokasi/dealokasi.
*/
	Address T = Nil,Prec = Nil;
	Address P = Nil;

	if( NbElmt(*L) >= 2 ){
		Prec = Nil;
		P = First(*L);

		while( Next(P) != Nil ){
			T = Next(P);
			Next(P) = Prec;

			Prec = P;
			P = T;
		}

		Next(P) = Prec;
		First(*L) = P;
	}
}

List FInversList (List L){
/*	Mengirimkan list baru, hasil invers dari L dengan menyalin semua elemen list.
	Alokasi mungkin gagal. Jika alokasi gagal, hasilnya list kosong dan semua elemen
	yang terlanjur di-alokasi, harus didealokasi.
*/
	List L2;
	Address P;
	CreateList(&L2);
	loop_list( L, P, InsVFirst(&L2,Info(P)));

	return L2;
}

void CopyList (List L1, List *L2){
/*	I.S. L1 terdefinisi, L2 sembarang. F.S. L2 = L1
	L1 dan L2 "menunjuk" kepada list yang sama.
	Tidak ada alokasi/dealokasi elemen baru.
*/
	Address P;
/*
	CreateList(L2);
	loop_list( L1, P, InsVLast(L2,Info(P)));
*/
	First(*L2) = First(L1);
}

List FCopyList (List L){
/*	Mengirimkan list yang merupakan salinan L dengan melakukan alokasi elemen baru.
	Jika ada alokasi gagal, hasilnya list kosong dan semua elemen yang terlanjur dialokasi,
	harus didealokasi.
*/
	List L2;
	Address P;
	/*
	CreateList(&L2);
	loop_list( L, P, InsVLast(&L2,Info(P)));
	*/
	CpAlokList(L,&L2);
	return L2;
}

void CpAlokList (List Lin, List *Lout){
/*	I.S. Lout sembarang, Lin terdefinisi.
	F.S. Jika semua alokasi berhasil, maka Lout berisi hasil copy Lin
	Jika ada alokasi yang gagal, maka Lout = Nil dan semua elemen yang terlanjur
	dialokasi, didealokasi
*/
    Address P = Nil;
    Address P2 = Nil;
    Address Back = Nil;

    CreateList(Lout);

    loop_list(Lin,P,
        P2 = Alokasi(Info(P));
        if( P2 == Nil ) break;
        if( Back == Nil ){
            First(*Lout) = P2;
        }
        else {
			Next(Back) = P2;
        }
		Back = P2;
    );

    if( NbElmt(Lin) != NbElmt(*Lout))
        DeleteAll(Lout);
}

void Concat (List L1, List L2, List *L3){
/*	I.S. L1 dan L2 terdefinisi, boleh kosong.
	F.S. L1 dan L2 tetap, L3 adalah hasil konkatenasi L1 dan L2
	Jika semua alokasi berhasil, maka L3 adalah hasil konkatenasi L1 dan L2.
	Jika ada alokasi yang gagal, semua elemen yang sudah dialokasi harus didealokasi
	dan L3 = Nil.
	Konkatenasi dua buah list : L1 dan L2 menghasilkan L3 yang "baru".
	Elemen L3 adalah hasil alokasi elemen yang "baru".
	Jika ada alokasi yang gagal, maka L3 harus bernilai Nil dan semua elemen yang
	pernah dialokasi harus didealokasi.
*/
    List L1c,L2c;
	CreateList(L3);
    CpAlokList(L1, &L1c);
    if( IsListEmpty(L1c) && !IsListEmpty(L1) )
		return;

    CpAlokList(L2, &L2c);
    if( IsListEmpty(L2c) && !IsListEmpty(L2) ){
		DeleteAll(&L1c);
		return;
	}

    InsertLast(&L1c,First(L2c));

    *L3 = L1c;
}

void PecahList (List *L1, List *L2, List L){
/*	I.S. L mungkin kosong
	F.S. Berdasarkan L, dibentuk dua buah list L1 dan L2
	L tidak berubah : untuk membentuk L1 dan L2 harus alokasi.
	L1 berisi separuh elemen L dan L2 berisi sisa elemen L.
	Jika elemen L ganjil, maka separuh adalah NbElmt(L) div 2.
	Jila alokasi gagal, semua elemen yang sudah dialokasikan harus di-dealokasi (bisa L1, L2 atau keduanya)
*/
    Address P, P2;
    int Len = NbElmt(L);
    int separuh = Len / 2;
    int i = 0;

    CreateList(L1);
    CreateList(L2);

    loop_list(L,P,
        P2 = Alokasi(Info(P));
        if( P2 == Nil )break;

        if( i <= separuh ){
            InsertLast(L1,P2);
        }
        else {
            InsertLast(L2,P2);
        }
        ++i;
    );

    if( NbElmt(*L1) != separuh || NbElmt(*L2) != Len - separuh ){
        DeleteAll(L1);
        DeleteAll(L2);
    }

}

