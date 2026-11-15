#ifndef TECHSTOCK_H
#define TECHSTOCK_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

typedef struct elmAkun *adrAkun;
typedef struct elmProduk *adrProduk;

struct infotypeAkun {
    string username;
    string password;
    string role;
    string nama;
};

struct elmAkun {
    infotypeAkun info;
    adrAkun next;
};

struct ListAkun {
    adrAkun first;
};

struct infotypeProduk {
    string idProduk;
    string namaProduk;
    string kategori;
    long harga;
    int stok;
};

struct elmProduk {
    infotypeProduk info;
    adrProduk next;
    adrProduk prev;
};

struct ListProduk {
    adrProduk first;
    adrProduk last;
};

void createListAkun(ListAkun &LA);
adrAkun alokasiAkun(string user, string pass, string role, string nama);
void insertLastAkun(ListAkun &LA, adrAkun P);
adrAkun cariAkun(ListAkun LA, string user, string pass);
adrAkun cariUsername(ListAkun LA, string user);
void printAkun(ListAkun LA);
void simpanAkun(ListAkun LA, string namaFile);
void muatAkun(ListAkun &LA, string namaFile);

void createListProduk(ListProduk &LP);
adrProduk alokasiProduk(infotypeProduk data);
void dealokasiProduk(adrProduk &P);
bool isEmptyProduk(ListProduk LP);
void insertLastProduk(ListProduk &LP, adrProduk P);
void deleteLastProduk(ListProduk &LP, adrProduk &P);
adrProduk cariProduk(ListProduk LP, string id);
void printProdukMaju(ListProduk LP);
void printProdukMundur(ListProduk LP);
void simpanProduk(ListProduk LP, string namaFile);
void muatProduk(ListProduk &LP, string namaFile);

#endif