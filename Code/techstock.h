#ifndef TECHSTOCK_H
#define TECHSTOCK_H

#include <iostream>
#include <string>

using namespace std;

typedef struct elmKategori *adrKategori;
typedef struct elmProduk *adrProduk;
typedef struct elmRelasi *adrRelasi;
typedef struct elmQueue *adrQueue;
typedef struct elmStack *adrStack;
typedef struct nodeBST *adrBST;

struct infotypeKategori {
    string idKategori;
    string namaKategori;
};

struct elmKategori {
    infotypeKategori info;
    adrKategori next;
};

struct ListKategori {
    adrKategori first;
};

struct infotypeProduk {
    string idProduk;
    string namaProduk;
    string merek;
    long harga;
    int stok;
    int stokMinimum;
};

struct elmRelasi {
    adrProduk targetProduk;
    string keterangan;
    adrRelasi next;
};

struct ListRelasi {
    adrRelasi first;
};

struct elmProduk {
    infotypeProduk info;
    adrProduk next;
    adrProduk prev;
    adrKategori nextKategori;
    ListRelasi relasiBundling;
};

struct ListProduk {
    adrProduk first;
    adrProduk last;
};

struct nodeBST {
    string keyId;
    adrProduk refProduk;
    adrBST left;
    adrBST right;
};

typedef adrBST BinTree;

struct infotypePelanggan {
    string nomorAntrean;
    string namaPelanggan;
    string keperluan;
};

struct elmQueue {
    infotypePelanggan info;
    adrQueue next;
    adrQueue prev;
};

struct QueuePelanggan {
    adrQueue head;
    adrQueue tail;
};

struct infotypeAksi {
    string jenisAksi;
    string idProduk;
    string namaProduk;
    int jumlah;
    long hargaSatuan;
};

struct elmStack {
    infotypeAksi info;
    adrStack next;
};

struct StackAksi {
    adrStack top;
};

const int MAX_ARRAY = 100;

struct ArrayTerurutProduk {
    adrProduk tab[MAX_ARRAY];
    int n;
};

void createListKategori(ListKategori &LK);
adrKategori alokasiKategori(string id, string nama);
void dealokasiKategori(adrKategori &P);
bool isEmptyKategori(ListKategori LK);
void insertFirstKategori(ListKategori &LK, adrKategori P);
void insertLastKategori(ListKategori &LK, adrKategori P);
void deleteFirstKategori(ListKategori &LK, adrKategori &P);
void deleteAfterKategori(ListKategori &LK, adrKategori Prec, adrKategori &P);
adrKategori searchKategori(ListKategori LK, string id);
void printKategori(ListKategori LK);

void createListProduk(ListProduk &LP);
adrProduk alokasiProduk(infotypeProduk data);
void dealokasiProduk(adrProduk &P);
bool isEmptyProduk(ListProduk LP);
void insertFirstProduk(ListProduk &LP, adrProduk P);
void insertLastProduk(ListProduk &LP, adrProduk P);
void insertAfterProduk(ListProduk &LP, adrProduk Prec, adrProduk P);
void deleteFirstProduk(ListProduk &LP, adrProduk &P);
void deleteLastProduk(ListProduk &LP, adrProduk &P);
void deleteAfterProduk(ListProduk &LP, adrProduk Prec, adrProduk &P);
void printProdukMaju(ListProduk LP);
void printProdukMundur(ListProduk LP);

void setKategoriProduk(ListProduk &LP, ListKategori LK, string idProduk, string idKategori);
void printProdukPerKategori(ListProduk LP, ListKategori LK, string idKategori);
void hapusKategoriBesertaRelasi(ListProduk &LP, ListKategori &LK, string idKategori);

void createListRelasi(ListRelasi &LR);
adrRelasi alokasiRelasi(adrProduk target, string ket);
void dealokasiRelasi(adrRelasi &R);
void insertLastRelasi(ListRelasi &LR, adrRelasi R);
void emptyListRelasi(ListRelasi &LR);
void tambahRelasiBundling(ListProduk &LP, string idUtama, string idPasangan, string ket);
void printRekomendasiBundling(ListProduk LP, string idProduk);

void createBST(BinTree &root);
adrBST createNodeBST(string id, adrProduk ref);
void insertBST(BinTree &root, string id, adrProduk ref);
adrBST findNodeBST(BinTree root, string id);
adrBST findMinBST(BinTree root);
void inOrderBST(BinTree root);

adrProduk searchProdukByIdSequential(ListProduk LP, string id);
void searchProdukByNamaSequential(ListProduk LP, string kataKunci);
adrProduk findMaxHargaProduk(ListProduk LP);
adrProduk findMinStokProduk(ListProduk LP);

void createArrayTerurut(ArrayTerurutProduk &A);
void insertSortedArray(ArrayTerurutProduk &A, adrProduk P);
int binarySearchArray(ArrayTerurutProduk A, string targetId);
void bangunArrayTerurutDariList(ListProduk LP, ArrayTerurutProduk &A);

void createQueue(QueuePelanggan &Q);
adrQueue alokasiQueue(string nomor, string nama, string keperluan);
void dealokasiQueue(adrQueue &P);
bool isEmptyQueue(QueuePelanggan Q);
void enqueue(QueuePelanggan &Q, adrQueue P);
void dequeue(QueuePelanggan &Q, adrQueue &P);
adrQueue frontQueue(QueuePelanggan Q);
int sizeQueue(QueuePelanggan Q);
void printQueue(QueuePelanggan Q);

void createStack(StackAksi &S);
adrStack alokasiStack(infotypeAksi data);
void dealokasiStack(adrStack &P);
bool isEmptyStack(StackAksi S);
void push(StackAksi &S, adrStack P);
void pop(StackAksi &S, adrStack &P);
infotypeAksi peek(StackAksi S);
void printStackKeranjang(StackAksi S);

void muatDataAwal(ListKategori &LK, ListProduk &LP, BinTree & pohonID, QueuePelanggan &Q);

#endif