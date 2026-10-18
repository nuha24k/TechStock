# Evaluasi Proyek, Source Code Progress 1 (45%), dan Bedah Konsep Struktur Data — TechStock POS

**Mata Kuliah:** Struktur Data (CDK2AAB4)  
**Kelompok 2:**
- Yudwitama Ahlan Putra H.B (109082530016 / S1IF-13-01)
- Sofwan Nuha Al Faruq (109082500032 / S1IF-13-02)
- Rachma Agustina Yassin (109082500046 / S1IF-13-03)
- Zhafif Iqbal Kurniawan (109082500051 / S1IF-13-04)

---

## Bagian 1: Evaluasi Menyeluruh Berdasarkan Masukan Dosen & Materi Perkuliahan (Slide 01 – 07)

Setelah meninjau kembali dokumen **Proposal**, **Slide Presentasi Proposal**, dan **PRD awal** lalu membandingkannya dengan **7 Slide Materi Kuliah Struktur Data (CDK2AAB4)** serta **6 poin evaluasi dosen**, ditemukan beberapa ketidaksinkronan di rancangan awal yang membuat dosen memberikan catatan kritis. Berikut adalah hasil bedah evaluasi beserta solusi perbaikannya:

### 1. Evaluasi Penggunaan Struktur Data & Pendekatan Tiap Masalah
- **Masalah pada Rancangan Sebelumnya:**
  1. Di dokumen PRD awal tertulis banyak istilah di luar cakupan materi semester tiga seperti *AVL Tree (Rotasi LL, RR, LR, RL)*, *Min-Heap (Floyd's Build-Heap)*, *N-ary Tree (First-Child/Next-Sibling)*, *Undirected Weighted Graph*, hingga konsep *RAII / Rule of Five*.
  2. Sebaliknya, pada dokumen Proposal PDF (Bab 4) dan Slide Presentasi, struktur data yang dicantumkan justru menyempit hanya menjadi **BST** dan **Multi Linked-List** (yang dipecah menjadi MLL-00, MLL-01, MLL-02), sementara *Stack*, *Queue*, *Singly Linked List*, dan *Doubly Linked List* tidak dijabarkan secara utuh di bagian pemetaan. Hal inilah yang membuat dosen menilai **"Terkait struktur data terlalu sedikit"** dan menekankan syarat **"Minimal empat model Struktur Data"** dengan pendekatan masalah yang jelas.
- **Solusi Penyempurnaan (6 Model Struktur Data Murni Sesuai Slide 01–07):**
  Tanpa mengubah ide utama aplikasi kasir toko komputer **TechStock**, kita memetakan ulang setiap masalah operasional toko ke **6 model Struktur Data** yang 100% sesuai dengan materi perkuliahan:

| No | Masalah Operasional di Toko Komputer TechStock | Model Struktur Data yang Dipakai | Referensi Materi Kuliah |
|---|---|---|---|
| 1 | Katalog produk jumlahnya dinamis (bisa tambah/hapus kapan saja) dan kasir butuh melihat daftar barang dari terlama ke terbaru (`first` ke `last`) maupun terbaru ke terlama (`last` ke `first`), serta hapus elemen akhir dengan cepat. | **Doubly Linked List (DLL)** (`ListProduk` dengan pointer `first`, `last`, `next`, `prev`) | **Slide 03 - Doubly Linked List** |
| 2 | Pengelompokan banyak produk ke dalam satu kategori komponen (misal *Processor*, *RAM*, *Storage*) tanpa menduplikasi data kategori di setiap produk. | **Multi-Linked List (MLL) Relasi 1-to-N** (`ListKategori` berjenis SLL, ditunjuk oleh pointer `nextKategori` dari elemen produk) | **Slide 06 - MLL (Example 4: Student – Class)** |
| 3 | Satu produk (misal CPU Intel i5) memiliki banyak rekomendasi pasangan/bundling (Motherboard + RAM + Cooler), dan sebaliknya produk lain juga bisa direkomendasikan ke banyak produk. | **Multi-Linked List (MLL) Relasi M-to-N** (Sub-list `ListRelasi` di dalam setiap elemen `elmProduk`) | **Slide 06 - MLL (Example 5: Student – Course)** |
| 4 | Pencarian produk berdasarkan kode ID unik (misal `PRD-0042`) harus cepat tanpa menelusuri seluruh katalog dari awal, sekaligus bisa menampilkan produk terurut otomatis berdasarkan ID. | **Binary Search Tree (BST)** (`BinTree` dengan pointer `left`, `right`, dan `refProduk`) | **Slide 07 - Tree & BST** |
| 5 | Pelanggan yang datang ke meja kasir saat jam ramai harus dilayani secara adil sesuai urutan kedatangan (*First-In First-Out*). | **Queue (Doubly Linked Queue)** (`QueuePelanggan` dengan pointer `head` dan `tail`, operasi `enqueue` & `dequeue`) | **Slide 05 - Queue** |
| 6 | Kasir sering salah input barang ke keranjang sehingga butuh fitur pembatalan aksi terakhir (*Undo*) dan pengulangan aksi (*Redo*) secara instan (*Last-In First-Out*). | **Stack (Linked List Stack ×2)** (`StackAksi` `undoStack` dan `redoStack` dengan pointer `top`, operasi `push`, `pop`, `peek`) | **Slide 04 - Stack** |

### 2. Evaluasi Metode Pencarian: Sequential Search vs Binary Search
- **Masalah pada Rancangan Sebelumnya:**
  Pada PRD lama (Bagian 3.7.2), tertulis bahwa untuk mencari produk dengan *Binary Search*, sistem menyalin seluruh isi *Linked List* ke array sementara, melakukan *Sorting*, lalu menjalankan *Binary Search*. Dari sudut pandang Struktur Data, pendekatan tersebut keliru karena menyalin data memakan waktu $O(N)$ dan mengurutkannya memakan $O(N \log N)$, sehingga lebih lambat daripada langsung mencari satu per satu dengan *Sequential Search* $O(N)$. Selain itu, *Binary Search* tidak bisa diterapkan langsung pada *Linked List* karena *Linked List* tidak memiliki indeks akses langsung (*random access*).
- **Solusi Hasil Riset Sesuai Slide 02 (Hal. 96 – 108):**
  1. **Sequential (Linear) Search pada Linked List (`U-DLL` / `U-SLL`):** Digunakan ketika mencari **Nama Produk** (pencarian kata kunci sebagian/substring) atau mencari di dalam Linked List yang tidak memiliki indeks array. Kompleksitasnya adalah **$O(N)$** karena harus menelusuri pointer `P = P->next` dari `first` sampai `NULL`.
  2. **Binary Search pada Ordered Array (`O-Array`):** Sesuai **Slide 02 hal. 100–102 & 107**, *Binary Search* **HANYA** benar dan efisien ($O(\log N)$) apabila diterapkan pada **Array yang sudah terurut (`Ordered Array`)** karena elemen tengah `tab[tengah]` dapat diakses langsung dalam waktu $O(1)$. Pada TechStock, kita menyediakan struktur `ArrayTerurutProduk` yang menjaga urutan elemen saat penyisipan menggunakan algoritma **Insert into a Sorted Array** (**Slide 02 hal. 2–5**), lalu dicari menggunakan **Binary Search** murni dalam waktu **$O(\log N)$**.
  3. **BST Search (`findNodeBST`) pada Struktur Dinamis Pointer:** Untuk pencarian cepat berbasis pointer tanpa array, struktur yang tepat bukanlah memaksakan Binary Search di Linked List, melainkan menggunakan **Binary Search Tree (BST)** (**Slide 07 hal. 47**) yang membagi arah pencarian ke cabang kiri (`id < root->keyId`) atau kanan (`id > root->keyId`) dengan rata-rata waktu **$O(\log N)$**.

### 3. Evaluasi Analisis Kompleksitas
Sesuai **Slide 02 hal. 107–108** (*Array vs. SLL Worst Case Comparison*) dan **Slide 07 hal. 27–35**, berikut adalah perbandingan kompleksitas waktu (*Time Complexity*) yang menjadi dasar pemilihan struktur data di TechStock:

| Operasi Primitif | Unordered Array (`U-Array`) | Ordered Array (`O-Array`) | Unordered SLL (`U-SLL`) | Ordered SLL (`O-SLL`) | Doubly Linked List (`DLL` dengan `first` & `last`) | Binary Search Tree (`BST`) |
|---|---|---|---|---|---|---|
| **Search** | $O(N)$ | **$O(\log N)$** *(Binary Search)* | $O(N)$ | $O(N)$ *(Tidak bisa Binary Search karena tanpa indeks)* | $O(N)$ | Rata-rata **$O(\log N)$**, Terburuk $O(N)$ jika *Skewed Tree* |
| **FindMax / FindMin** | $O(N)$ | **$O(1)$** *(Indeks ujung)* | $O(N)$ | $O(N)$ *(atau $O(1)$ di ujung)* | $O(N)$ *(jika belum urut)* | Rata-rata **$O(\log N)$** *(Telusur kiri/kanan mentok)* |
| **Insert First** | $O(N)$ *(Harus geser/shift elemen)* | $O(N)$ *(Shift elemen)* | **$O(1)$** | $O(N)$ *(Cari posisi urut)* | **$O(1)$** | — |
| **Insert Last** | **$O(1)$** | $O(N)$ | $O(N)$ *(Tanpa pointer `last`)* | $O(N)$ | **$O(1)$** *(Karena ada pointer `last`)* | — |
| **Insert After (Pointer `Prec` diketahui)** | $O(N)$ | $O(N)$ | **$O(1)$** | — | **$O(1)$** | — |
| **Delete First** | $O(N)$ *(Shift elemen)* | $O(N)$ | **$O(1)$** | **$O(1)$** | **$O(1)$** | — |
| **Delete Last** | **$O(1)$** | **$O(1)$** | $O(N)$ *(Harus cari elemen sebelum terakhir)* | $O(N)$ | **$O(1)$** *(Langsung lewat `last->prev`)* | — |
| **Delete After (Pointer `Prec` diketahui)** | $O(N)$ | $O(N)$ | **$O(1)$** | **$O(1)$** | **$O(1)$** | — |
| **Insert / Delete jika HANYA nilai (`value`) yang diketahui** | $O(N)$ | $O(N)$ | **$O(N)$** *(Harus `search` dulu mencari `Prec`)* | **$O(N)$** | **$O(N)$** *(Harus `search` dulu)* | Rata-rata **$O(\log N)$** |

### 4. Evaluasi Hal-Hal Mendasar yang Tidak Boleh Terlewat
Berdasarkan **Slide 01 s.d. Slide 07**, enam prinsip mendasar yang wajib dipatuhi pada kode kita adalah:
1. **Pemisahan ADT (`.h`, `.cpp`, `main.cpp`):** File header hanya berisi deklarasi tipe data (`infotype`, `address`, `elmList`, `List`) dan prototipe primitif, sedangkan cara kerja detailnya disembunyikan di `.cpp` (*Information Hiding & Reusability*, **Slide 01 hal. 23–28**).
2. **Perbedaan `Remove` (Lepas dari List) vs `Deallocate` (Hapus dari Memori):** Sesuai peringatan di **Slide 02 hal. 93**, prosedur `deleteFirst`, `deleteLast`, dan `deleteAfter` hanya memutus sambungan pointer elemen `P` dari list dan menyerahkan `P` ke pemanggil. Penghapusan memori baru dilakukan saat memanggil `dealokasi(P)` (`delete P`).
3. **Pencegahan *Lost Element / Memory Leak*:** Jangan pernah langsung mengubah `L.first = L.first->next` tanpa menyimpan alamat elemen pertama ke pointer penampung `P` terlebih dahulu (**Slide 02 hal. 67–69**).
4. **Penanganan *Special Conditions* (Kondisi Kosong & Kondisi 1 Elemen):** Pada **DLL** (**Slide 03 hal. 17–25**) dan **Queue** (**Slide 05 hal. 57–58**), menghapus elemen saat isi list tinggal **1 elemen** (`L.first == L.last`) harus ditangani dengan blok `else` khusus yang mengubah `first = NULL` dan `last = NULL` agar tidak terjadi *error* akibat mengakses `L.first->prev` saat `L.first` sudah bernilai `NULL`.
5. **Pencegahan *Underflow* dan *Overflow* pada Stack:** Sebelum melakukan `pop` atau `peek`, wajib memeriksa `isEmptyStack(S)` agar tidak terjadi *Stack Underflow* (**Slide 04 hal. 8–9**).
6. **Keamanan Penghapusan Relasi Multi-Linked List:** Saat menghapus kategori pada relasi 1-to-N, wajib menelusuri seluruh produk dan mengubah `P->nextKategori = NULL` jika produk tersebut menunjuk kategori yang akan dihapus (**Slide 06 hal. 18**). Saat menghapus produk pada relasi M-to-N, sub-list `relasiBundling` di dalamnya wajib dikosongkan (`emptyListRelasi`) terlebih dahulu (**Slide 06 hal. 27**).

---

## Bagian 2: Source Code Lengkap Progress 1 (45% Penyelesaian)

Seluruh kode di bawah ini ditulis menggunakan standar C++ perkuliahan semester 3 tanpa komentar di dalam kode dan terbagi menjadi 3 file ADT terpisah: `techstock.h`, `techstock.cpp`, dan `main.cpp`.

### 1. File Header ADT: `techstock.h`

```cpp
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

void muatDataAwal(ListKategori &LK, ListProduk &LP, BinTree &pohonID, QueuePelanggan &Q);

#endif
```

### 2. File Implementasi Primitif ADT: `techstock.cpp`

```cpp
#include "techstock.h"

void createListKategori(ListKategori &LK) {
    LK.first = NULL;
}

adrKategori alokasiKategori(string id, string nama) {
    adrKategori P = new elmKategori;
    P->info.idKategori = id;
    P->info.namaKategori = nama;
    P->next = NULL;
    return P;
}

void dealokasiKategori(adrKategori &P) {
    delete P;
    P = NULL;
}

bool isEmptyKategori(ListKategori LK) {
    return LK.first == NULL;
}

void insertFirstKategori(ListKategori &LK, adrKategori P) {
    P->next = LK.first;
    LK.first = P;
}

void insertLastKategori(ListKategori &LK, adrKategori P) {
    if (isEmptyKategori(LK)) {
        LK.first = P;
    } else {
        adrKategori Q = LK.first;
        while (Q->next != NULL) {
            Q = Q->next;
        }
        Q->next = P;
    }
}

void deleteFirstKategori(ListKategori &LK, adrKategori &P) {
    if (isEmptyKategori(LK)) {
        P = NULL;
    } else {
        P = LK.first;
        LK.first = P->next;
        P->next = NULL;
    }
}

void deleteAfterKategori(ListKategori &LK, adrKategori Prec, adrKategori &P) {
    if (Prec == NULL || Prec->next == NULL) {
        P = NULL;
    } else {
        P = Prec->next;
        Prec->next = P->next;
        P->next = NULL;
    }
}

adrKategori searchKategori(ListKategori LK, string id) {
    adrKategori P = LK.first;
    while (P != NULL && P->info.idKategori != id) {
        P = P->next;
    }
    return P;
}

void printKategori(ListKategori LK) {
    if (isEmptyKategori(LK)) {
        cout << "Daftar kategori masih kosong." << endl;
    } else {
        cout << "==========================================" << endl;
        cout << "ID KATEGORI   | NAMA KATEGORI" << endl;
        cout << "==========================================" << endl;
        adrKategori P = LK.first;
        while (P != NULL) {
            cout << P->info.idKategori << "       | " << P->info.namaKategori << endl;
            P = P->next;
        }
        cout << "==========================================" << endl;
    }
}

void createListRelasi(ListRelasi &LR) {
    LR.first = NULL;
}

adrRelasi alokasiRelasi(adrProduk target, string ket) {
    adrRelasi R = new elmRelasi;
    R->targetProduk = target;
    R->keterangan = ket;
    R->next = NULL;
    return R;
}

void dealokasiRelasi(adrRelasi &R) {
    delete R;
    R = NULL;
}

void insertLastRelasi(ListRelasi &LR, adrRelasi R) {
    if (LR.first == NULL) {
        LR.first = R;
    } else {
        adrRelasi Q = LR.first;
        while (Q->next != NULL) {
            Q = Q->next;
        }
        Q->next = R;
    }
}

void emptyListRelasi(ListRelasi &LR) {
    adrRelasi R;
    while (LR.first != NULL) {
        R = LR.first;
        LR.first = R->next;
        R->next = NULL;
        dealokasiRelasi(R);
    }
}

void createListProduk(ListProduk &LP) {
    LP.first = NULL;
    LP.last = NULL;
}

adrProduk alokasiProduk(infotypeProduk data) {
    adrProduk P = new elmProduk;
    P->info = data;
    P->next = NULL;
    P->prev = NULL;
    P->nextKategori = NULL;
    createListRelasi(P->relasiBundling);
    return P;
}

void dealokasiProduk(adrProduk &P) {
    emptyListRelasi(P->relasiBundling);
    delete P;
    P = NULL;
}

bool isEmptyProduk(ListProduk LP) {
    return LP.first == NULL && LP.last == NULL;
}

void insertFirstProduk(ListProduk &LP, adrProduk P) {
    if (!isEmptyProduk(LP)) {
        P->next = LP.first;
        LP.first->prev = P;
        LP.first = P;
    } else {
        LP.first = P;
        LP.last = P;
    }
}

void insertLastProduk(ListProduk &LP, adrProduk P) {
    if (!isEmptyProduk(LP)) {
        P->prev = LP.last;
        LP.last->next = P;
        LP.last = P;
    } else {
        LP.first = P;
        LP.last = P;
    }
}

void insertAfterProduk(ListProduk &LP, adrProduk Prec, adrProduk P) {
    if (Prec != NULL) {
        if (Prec == LP.last) {
            insertLastProduk(LP, P);
        } else {
            P->next = Prec->next;
            P->prev = Prec;
            Prec->next->prev = P;
            Prec->next = P;
        }
    }
}

void deleteFirstProduk(ListProduk &LP, adrProduk &P) {
    if (isEmptyProduk(LP)) {
        P = NULL;
    } else if (LP.first != LP.last) {
        P = LP.first;
        LP.first = P->next;
        P->next = NULL;
        LP.first->prev = NULL;
    } else {
        P = LP.first;
        LP.first = NULL;
        LP.last = NULL;
    }
}

void deleteLastProduk(ListProduk &LP, adrProduk &P) {
    if (isEmptyProduk(LP)) {
        P = NULL;
    } else if (LP.first != LP.last) {
        P = LP.last;
        LP.last = LP.last->prev;
        P->prev = NULL;
        LP.last->next = NULL;
    } else {
        P = LP.last;
        LP.first = NULL;
        LP.last = NULL;
    }
}

void deleteAfterProduk(ListProduk &LP, adrProduk Prec, adrProduk &P) {
    if (Prec == NULL || Prec->next == NULL) {
        P = NULL;
    } else if (Prec->next == LP.last) {
        deleteLastProduk(LP, P);
    } else {
        P = Prec->next;
        Prec->next = P->next;
        P->next->prev = Prec;
        P->prev = NULL;
        P->next = NULL;
    }
}

void printProdukMaju(ListProduk LP) {
    if (isEmptyProduk(LP)) {
        cout << "Katalog produk kosong." << endl;
    } else {
        cout << "=====================================================================================" << endl;
        cout << "ID       | NAMA PRODUK               | MEREK     | KATEGORI     | HARGA      | STOK" << endl;
        cout << "=====================================================================================" << endl;
        adrProduk P = LP.first;
        while (P != NULL) {
            string namaKat = "Belum Ada";
            if (P->nextKategori != NULL) {
                namaKat = P->nextKategori->info.namaKategori;
            }
            cout << P->info.idProduk << " | "
                 << P->info.namaProduk << " | "
                 << P->info.merek << " | "
                 << namaKat << " | Rp"
                 << P->info.harga << " | "
                 << P->info.stok;
            if (P->info.stok <= P->info.stokMinimum) {
                cout << " [STOK menipis!]";
            }
            cout << endl;
            P = P->next;
        }
        cout << "=====================================================================================" << endl;
    }
}

void printProdukMundur(ListProduk LP) {
    if (isEmptyProduk(LP)) {
        cout << "Katalog produk kosong." << endl;
    } else {
        cout << "=====================================================================================" << endl;
        cout << "KATALOG DARI PRODUK TERBARU (TRAVERSAL MUNDUR DARI LAST KE FIRST)" << endl;
        cout << "=====================================================================================" << endl;
        adrProduk P = LP.last;
        while (P != NULL) {
            string namaKat = "Belum Ada";
            if (P->nextKategori != NULL) {
                namaKat = P->nextKategori->info.namaKategori;
            }
            cout << P->info.idProduk << " | "
                 << P->info.namaProduk << " | "
                 << namaKat << " | Rp"
                 << P->info.harga << " | Stok: "
                 << P->info.stok << endl;
            P = P->prev;
        }
        cout << "=====================================================================================" << endl;
    }
}

void setKategoriProduk(ListProduk &LP, ListKategori LK, string idProduk, string idKategori) {
    adrProduk P = searchProdukByIdSequential(LP, idProduk);
    adrKategori Q = searchKategori(LK, idKategori);
    if (P != NULL && Q != NULL) {
        P->nextKategori = Q;
    }
}

void printProdukPerKategori(ListProduk LP, ListKategori LK, string idKategori) {
    adrKategori K = searchKategori(LK, idKategori);
    if (K == NULL) {
        cout << "Kategori dengan ID " << idKategori << " tidak ditemukan." << endl;
        return;
    }
    cout << "Daftar Produk pada Kategori: " << K->info.namaKategori << " (" << K->info.idKategori << ")" << endl;
    cout << "----------------------------------------------------------------------" << endl;
    adrProduk P = LP.first;
    int hitung = 0;
    while (P != NULL) {
        if (P->nextKategori == K) {
            cout << "- [" << P->info.idProduk << "] " << P->info.namaProduk
                 << " | Rp" << P->info.harga << " | Stok: " << P->info.stok << endl;
            hitung = hitung + 1;
        }
        P = P->next;
    }
    if (hitung == 0) {
        cout << "Belum ada produk yang terhubung ke kategori ini." << endl;
    }
    cout << "----------------------------------------------------------------------" << endl;
}

void hapusKategoriBesertaRelasi(ListProduk &LP, ListKategori &LK, string idKategori) {
    adrKategori Q = searchKategori(LK, idKategori);
    if (Q != NULL) {
        adrProduk P = LP.first;
        while (P != NULL) {
            if (P->nextKategori == Q) {
                P->nextKategori = NULL;
            }
            P = P->next;
        }
        adrKategori hapus = NULL;
        if (LK.first == Q) {
            deleteFirstKategori(LK, hapus);
        } else {
            adrKategori Prec = LK.first;
            while (Prec != NULL && Prec->next != Q) {
                Prec = Prec->next;
            }
            if (Prec != NULL) {
                deleteAfterKategori(LK, Prec, hapus);
            }
        }
        if (hapus != NULL) {
            dealokasiKategori(hapus);
            cout << "Kategori " << idKategori << " berhasil dihapus dan relasi produk telah di-reset." << endl;
        }
    } else {
        cout << "Kategori tidak ditemukan." << endl;
    }
}

void tambahRelasiBundling(ListProduk &LP, string idUtama, string idPasangan, string ket) {
    adrProduk P = searchProdukByIdSequential(LP, idUtama);
    adrProduk Q = searchProdukByIdSequential(LP, idPasangan);
    if (P != NULL && Q != NULL && P != Q) {
        adrRelasi R = alokasiRelasi(Q, ket);
        insertLastRelasi(P->relasiBundling, R);
    }
}

void printRekomendasiBundling(ListProduk LP, string idProduk) {
    adrProduk P = searchProdukByIdSequential(LP, idProduk);
    if (P == NULL) {
        cout << "Produk tidak ditemukan." << endl;
        return;
    }
    cout << "Rekomendasi Pasangan / Bundling untuk " << P->info.namaProduk << ":" << endl;
    adrRelasi R = P->relasiBundling.first;
    if (R == NULL) {
        cout << "  (Belum ada rekomendasi bundling untuk produk ini)" << endl;
    } else {
        while (R != NULL) {
            if (R->targetProduk != NULL) {
                cout << "  -> [" << R->keterangan << "] "
                     << R->targetProduk->info.idProduk << " - "
                     << R->targetProduk->info.namaProduk
                     << " (Rp" << R->targetProduk->info.harga << ", Stok: "
                     << R->targetProduk->info.stok << ")" << endl;
            }
            R = R->next;
        }
    }
}

void createBST(BinTree &root) {
    root = NULL;
}

adrBST createNodeBST(string id, adrProduk ref) {
    adrBST N = new nodeBST;
    N->keyId = id;
    N->refProduk = ref;
    N->left = NULL;
    N->right = NULL;
    return N;
}

void insertBST(BinTree &root, string id, adrProduk ref) {
    if (root == NULL) {
        root = createNodeBST(id, ref);
    } else {
        if (root->keyId > id) {
            insertBST(root->left, id, ref);
        } else if (root->keyId < id) {
            insertBST(root->right, id, ref);
        } else {
            cout << "ID produk duplikat pada BST." << endl;
        }
    }
}

adrBST findNodeBST(BinTree root, string id) {
    if (root == NULL || root->keyId == id) {
        return root;
    } else {
        if (root->keyId > id) {
            return findNodeBST(root->left, id);
        } else {
            return findNodeBST(root->right, id);
        }
    }
}

adrBST findMinBST(BinTree root) {
    adrBST minNode = root;
    if (minNode != NULL) {
        while (minNode->left != NULL) {
            minNode = minNode->left;
        }
    }
    return minNode;
}

void inOrderBST(BinTree root) {
    if (root != NULL) {
        inOrderBST(root->left);
        if (root->refProduk != NULL) {
            cout << root->keyId << " -> "
                 << root->refProduk->info.namaProduk
                 << " (Rp" << root->refProduk->info.harga
                 << ", Stok: " << root->refProduk->info.stok << ")" << endl;
        }
        inOrderBST(root->right);
    }
}

adrProduk searchProdukByIdSequential(ListProduk LP, string id) {
    adrProduk P = LP.first;
    while (P != NULL && P->info.idProduk != id) {
        P = P->next;
    }
    return P;
}

string ubahKeHurufKecil(string teks) {
    string hasil = teks;
    for (int i = 0; i < (int)hasil.length(); i++) {
        if (hasil[i] >= 'A' && hasil[i] <= 'Z') {
            hasil[i] = hasil[i] + ('a' - 'A');
        }
    }
    return hasil;
}

void searchProdukByNamaSequential(ListProduk LP, string kataKunci) {
    string cari = ubahKeHurufKecil(kataKunci);
    adrProduk P = LP.first;
    int ditemukan = 0;
    cout << "Hasil Sequential Search untuk kata kunci '" << kataKunci << "':" << endl;
    while (P != NULL) {
        string namaLower = ubahKeHurufKecil(P->info.namaProduk);
        if (namaLower.find(cari) != string::npos) {
            cout << "- [" << P->info.idProduk << "] " << P->info.namaProduk
                 << " | Merek: " << P->info.merek
                 << " | Rp" << P->info.harga
                 << " | Stok: " << P->info.stok << endl;
            ditemukan = ditemukan + 1;
        }
        P = P->next;
    }
    if (ditemukan == 0) {
        cout << "Tidak ada produk yang cocok dengan kata kunci tersebut." << endl;
    }
}

adrProduk findMaxHargaProduk(ListProduk LP) {
    if (isEmptyProduk(LP)) {
        return NULL;
    }
    adrProduk P = LP.first;
    adrProduk maxNode = LP.first;
    while (P != NULL) {
        if (P->info.harga > maxNode->info.harga) {
            maxNode = P;
        }
        P = P->next;
    }
    return maxNode;
}

adrProduk findMinStokProduk(ListProduk LP) {
    if (isEmptyProduk(LP)) {
        return NULL;
    }
    adrProduk P = LP.first;
    adrProduk minNode = LP.first;
    while (P != NULL) {
        if (P->info.stok < minNode->info.stok) {
            minNode = P;
        }
        P = P->next;
    }
    return minNode;
}

void createArrayTerurut(ArrayTerurutProduk &A) {
    A.n = 0;
}

void insertSortedArray(ArrayTerurutProduk &A, adrProduk P) {
    if (A.n >= MAX_ARRAY || P == NULL) {
        return;
    }
    int i = 0;
    while (i < A.n && A.tab[i]->info.idProduk < P->info.idProduk) {
        i = i + 1;
    }
    adrProduk temp1 = A.tab[i];
    A.tab[i] = P;
    for (int j = i + 1; j <= A.n; j++) {
        adrProduk temp2 = A.tab[j];
        A.tab[j] = temp1;
        temp1 = temp2;
    }
    A.n = A.n + 1;
}

int binarySearchArray(ArrayTerurutProduk A, string targetId) {
    int kiri = 0;
    int kanan = A.n - 1;
    while (kiri <= kanan) {
        int tengah = (kiri + kanan) / 2;
        if (A.tab[tengah]->info.idProduk == targetId) {
            return tengah;
        } else if (A.tab[tengah]->info.idProduk < targetId) {
            kiri = tengah + 1;
        } else {
            kanan = tengah - 1;
        }
    }
    return -1;
}

void bangunArrayTerurutDariList(ListProduk LP, ArrayTerurutProduk &A) {
    createArrayTerurut(A);
    adrProduk P = LP.first;
    while (P != NULL) {
        insertSortedArray(A, P);
        P = P->next;
    }
}

void createQueue(QueuePelanggan &Q) {
    Q.head = NULL;
    Q.tail = NULL;
}

adrQueue alokasiQueue(string nomor, string nama, string keperluan) {
    adrQueue P = new elmQueue;
    P->info.nomorAntrean = nomor;
    P->info.namaPelanggan = nama;
    P->info.keperluan = keperluan;
    P->next = NULL;
    P->prev = NULL;
    return P;
}

void dealokasiQueue(adrQueue &P) {
    delete P;
    P = NULL;
}

bool isEmptyQueue(QueuePelanggan Q) {
    return Q.head == NULL;
}

void enqueue(QueuePelanggan &Q, adrQueue P) {
    if (isEmptyQueue(Q)) {
        Q.head = P;
        Q.tail = P;
    } else {
        P->prev = Q.tail;
        Q.tail->next = P;
        Q.tail = P;
    }
}

void dequeue(QueuePelanggan &Q, adrQueue &P) {
    P = Q.head;
    if (!isEmptyQueue(Q)) {
        if (Q.head != Q.tail) {
            Q.head = P->next;
            P->next = NULL;
            Q.head->prev = NULL;
        } else {
            Q.head = NULL;
            Q.tail = NULL;
        }
    }
}

adrQueue frontQueue(QueuePelanggan Q) {
    return Q.head;
}

int sizeQueue(QueuePelanggan Q) {
    int result = 0;
    adrQueue P = Q.head;
    while (P != NULL) {
        result = result + 1;
        P = P->next;
    }
    return result;
}

void printQueue(QueuePelanggan Q) {
    if (isEmptyQueue(Q)) {
        cout << "Antrean pelanggan saat ini kosong." << endl;
    } else {
        cout << "==========================================================" << endl;
        cout << "NO ANTREAN | NAMA PELANGGAN      | KEPERLUAN" << endl;
        cout << "==========================================================" << endl;
        adrQueue P = Q.head;
        while (P != NULL) {
            cout << P->info.nomorAntrean << "      | "
                 << P->info.namaPelanggan << " | "
                 << P->info.keperluan;
            if (P == Q.head) {
                cout << " <-- [TERDEPAN / FRONT]";
            }
            if (P == Q.tail) {
                cout << " <-- [TERAKHIR / REAR]";
            }
            cout << endl;
            P = P->next;
        }
        cout << "Total antrean menunggu: " << sizeQueue(Q) << " pelanggan." << endl;
        cout << "==========================================================" << endl;
    }
}

void createStack(StackAksi &S) {
    S.top = NULL;
}

adrStack alokasiStack(infotypeAksi data) {
    adrStack P = new elmStack;
    P->info = data;
    P->next = NULL;
    return P;
}

void dealokasiStack(adrStack &P) {
    delete P;
    P = NULL;
}

bool isEmptyStack(StackAksi S) {
    return S.top == NULL;
}

void push(StackAksi &S, adrStack P) {
    if (isEmptyStack(S)) {
        S.top = P;
    } else {
        P->next = S.top;
        S.top = P;
    }
}

void pop(StackAksi &S, adrStack &P) {
    if (isEmptyStack(S)) {
        P = NULL;
    } else if (S.top->next == NULL) {
        P = S.top;
        S.top = NULL;
    } else {
        P = S.top;
        S.top = S.top->next;
        P->next = NULL;
    }
}

infotypeAksi peek(StackAksi S) {
    return S.top->info;
}

void printStackKeranjang(StackAksi S) {
    if (isEmptyStack(S)) {
        cout << "Keranjang / Riwayat Aksi masih kosong." << endl;
    } else {
        cout << "==================================================================" << endl;
        cout << "ISI KERANJANG & RIWAYAT AKSI KASIR (DARI TOP KE BOTTOM - LIFO)" << endl;
        cout << "==================================================================" << endl;
        adrStack P = S.top;
        long totalSementara = 0;
        while (P != NULL) {
            long sub = P->info.hargaSatuan * P->info.jumlah;
            totalSementara = totalSementara + sub;
            cout << "[" << P->info.jenisAksi << "] "
                 << P->info.idProduk << " - " << P->info.namaProduk
                 << " x" << P->info.jumlah
                 << " (@Rp" << P->info.hargaSatuan << ") = Rp" << sub;
            if (P == S.top) {
                cout << " <-- [TOP]";
            }
            cout << endl;
            P = P->next;
        }
        cout << "------------------------------------------------------------------" << endl;
        cout << "Estimasi Subtotal Keranjang: Rp" << totalSementara << endl;
        cout << "==================================================================" << endl;
    }
}

void tambahProdukLengkap(ListProduk &LP, ListKategori LK, BinTree &pohonID,
                         string id, string nama, string merek, string idKat,
                         long harga, int stok, int minStok) {
    infotypeProduk d;
    d.idProduk = id;
    d.namaProduk = nama;
    d.merek = merek;
    d.harga = harga;
    d.stok = stok;
    d.stokMinimum = minStok;

    adrProduk P = alokasiProduk(d);
    insertLastProduk(LP, P);
    setKategoriProduk(LP, LK, id, idKat);
    insertBST(pohonID, id, P);
}

void muatDataAwal(ListKategori &LK, ListProduk &LP, BinTree &pohonID, QueuePelanggan &Q) {
    insertLastKategori(LK, alokasiKategori("KAT-01", "Processor"));
    insertLastKategori(LK, alokasiKategori("KAT-02", "Motherboard"));
    insertLastKategori(LK, alokasiKategori("KAT-03", "Memory RAM"));
    insertLastKategori(LK, alokasiKategori("KAT-04", "Storage SSD/HDD"));
    insertLastKategori(LK, alokasiKategori("KAT-05", "Kartu Grafis VGA"));
    insertLastKategori(LK, alokasiKategori("KAT-06", "Aksesoris & Cooler"));

    tambahProdukLengkap(LP, LK, pohonID, "PRD-0100", "Intel Core i5-13400F", "Intel", "KAT-01", 3250000, 10, 4);
    tambahProdukLengkap(LP, LK, pohonID, "PRD-0042", "SSD NVMe Samsung 1TB", "Samsung", "KAT-04", 1450000, 3, 5);
    tambahProdukLengkap(LP, LK, pohonID, "PRD-0200", "Motherboard ASUS B760M", "ASUS", "KAT-02", 2450000, 6, 3);
    tambahProdukLengkap(LP, LK, pohonID, "PRD-0010", "RAM DDR5 Kingston 16GB", "Kingston", "KAT-03", 950000, 20, 6);
    tambahProdukLengkap(LP, LK, pohonID, "PRD-0043", "HDD Seagate Barracuda 2TB", "Seagate", "KAT-04", 1050000, 2, 5);
    tambahProdukLengkap(LP, LK, pohonID, "PRD-0300", "CPU Cooler DeepCool AK400", "DeepCool", "KAT-06", 350000, 15, 5);
    tambahProdukLengkap(LP, LK, pohonID, "PRD-0150", "VGA NVIDIA RTX 4060 8GB", "NVIDIA", "KAT-05", 5100000, 4, 3);

    tambahRelasiBundling(LP, "PRD-0100", "PRD-0200", "COMPATIBLE LGA1700");
    tambahRelasiBundling(LP, "PRD-0100", "PRD-0010", "COMPATIBLE DDR5");
    tambahRelasiBundling(LP, "PRD-0100", "PRD-0300", "BUNDLE DISKON 5%");
    tambahRelasiBundling(LP, "PRD-0200", "PRD-0042", "COMPATIBLE M.2 NVMe");

    enqueue(Q, alokasiQueue("A-001", "Budi Santoso", "Rakit PC Gaming"));
    enqueue(Q, alokasiQueue("A-002", "Siti Aminah", "Beli SSD NVMe"));
}
```

### 3. File Program Utama CLI: `main.cpp`

```cpp
#include "techstock.h"

int main() {
    ListKategori daftarKategori;
    ListProduk katalogProduk;
    BinTree indeksBST;
    QueuePelanggan antreanKasir;
    StackAksi undoStack;
    StackAksi redoStack;
    ArrayTerurutProduk arrayUrutID;

    createListKategori(daftarKategori);
    createListProduk(katalogProduk);
    createBST(indeksBST);
    createQueue(antreanKasir);
    createStack(undoStack);
    createStack(redoStack);
    createArrayTerurut(arrayUrutID);

    muatDataAwal(daftarKategori, katalogProduk, indeksBST, antreanKasir);

    int nomorTiketOtomatis = 3;
    string pelangganAktif = "Belum Ada";
    int pilihanUtama = -1;

    while (pilihanUtama != 0) {
        cout << endl;
        cout << "==========================================================" << endl;
        cout << "     TECHSTOCK POS - SISTEM KASIR & INVENTARIS TOKO PC    " << endl;
        cout << "                  PROGRESS 1 (45% TAHAP INTI)             " << endl;
        cout << "==========================================================" << endl;
        cout << "Pelanggan Aktif di Meja Kasir : " << pelangganAktif << endl;
        cout << "Jumlah Antrean Menunggu       : " << sizeQueue(antreanKasir) << " orang" << endl;
        cout << "----------------------------------------------------------" << endl;
        cout << "1. Menu Katalog & Inventaris Produk (DLL & MLL)" << endl;
        cout << "2. Menu Pencarian & Indeks Produk (BST, Sequential, Binary)" << endl;
        cout << "3. Menu Antrean Pelanggan (Queue FIFO)" << endl;
        cout << "4. Menu Simulasi Keranjang & Undo/Redo Kasir (Stack LIFO)" << endl;
        cout << "0. Keluar Program" << endl;
        cout << "----------------------------------------------------------" << endl;
        cout << "Pilih menu (0-4): ";
        cin >> pilihanUtama;

        if (pilihanUtama == 1) {
            int subMenu1 = -1;
            while (subMenu1 != 0) {
                cout << endl;
                cout << "--- [MENU 1: KATALOG & INVENTARIS (DLL & MLL)] ---" << endl;
                cout << "1. Tampilkan Katalog Maju (First ke Last)" << endl;
                cout << "2. Tampilkan Katalog Mundur (Last ke First)" << endl;
                cout << "3. Tambah Produk Baru ke Katalog" << endl;
                cout << "4. Hapus Produk Terakhir (Delete Last + Dealokasi)" << endl;
                cout << "5. Lihat Daftar Kategori & Produk per Kategori (MLL 1-to-N)" << endl;
                cout << "6. Hapus Kategori dengan Aman (Reset Relasi 1-to-N)" << endl;
                cout << "7. Lihat Rekomendasi Bundling Produk (MLL M-to-N)" << endl;
                cout << "8. Tambah Relasi Bundling Antar Produk (MLL M-to-N)" << endl;
                cout << "9. Cek Produk Harga Tertinggi (FindMax) & Stok Terkritis (FindMin)" << endl;
                cout << "0. Kembali ke Menu Utama" << endl;
                cout << "Pilih sub-menu: ";
                cin >> subMenu1;

                if (subMenu1 == 1) {
                    printProdukMaju(katalogProduk);
                } else if (subMenu1 == 2) {
                    printProdukMundur(katalogProduk);
                } else if (subMenu1 == 3) {
                    infotypeProduk baru;
                    string idKat;
                    cout << "Masukkan ID Produk (contoh PRD-0400): ";
                    cin >> baru.idProduk;
                    if (searchProdukByIdSequential(katalogProduk, baru.idProduk) != NULL) {
                        cout << "Gagal: ID Produk sudah terdaftar di katalog!" << endl;
                    } else {
                        cin.ignore();
                        cout << "Masukkan Nama Produk: ";
                        getline(cin, baru.namaProduk);
                        cout << "Masukkan Merek: ";
                        getline(cin, baru.merek);
                        printKategori(daftarKategori);
                        cout << "Masukkan ID Kategori: ";
                        cin >> idKat;
                        cout << "Masukkan Harga Satuan (Rp): ";
                        cin >> baru.harga;
                        cout << "Masukkan Jumlah Stok: ";
                        cin >> baru.stok;
                        cout << "Masukkan Batas Stok Minimum: ";
                        cin >> baru.stokMinimum;

                        adrProduk P = alokasiProduk(baru);
                        insertLastProduk(katalogProduk, P);
                        setKategoriProduk(katalogProduk, daftarKategori, baru.idProduk, idKat);
                        insertBST(indeksBST, baru.idProduk, P);
                        cout << "Produk " << baru.namaProduk << " berhasil ditambahkan ke DLL dan BST!" << endl;
                    }
                } else if (subMenu1 == 4) {
                    adrProduk P = NULL;
                    deleteLastProduk(katalogProduk, P);
                    if (P != NULL) {
                        cout << "Produk terakhir [" << P->info.idProduk << " - "
                             << P->info.namaProduk << "] dilepas dari list dan didealokasi." << endl;
                        dealokasiProduk(P);
                    } else {
                        cout << "Katalog sudah kosong." << endl;
                    }
                } else if (subMenu1 == 5) {
                    printKategori(daftarKategori);
                    string pilihKat;
                    cout << "Masukkan ID Kategori untuk melihat daftar produknya: ";
                    cin >> pilihKat;
                    printProdukPerKategori(katalogProduk, daftarKategori, pilihKat);
                } else if (subMenu1 == 6) {
                    printKategori(daftarKategori);
                    string idHapus;
                    cout << "Masukkan ID Kategori yang ingin dihapus: ";
                    cin >> idHapus;
                    hapusKategoriBesertaRelasi(katalogProduk, daftarKategori, idHapus);
                } else if (subMenu1 == 7) {
                    string idCek;
                    cout << "Masukkan ID Produk (contoh PRD-0100): ";
                    cin >> idCek;
                    printRekomendasiBundling(katalogProduk, idCek);
                } else if (subMenu1 == 8) {
                    string id1, id2, ket;
                    cout << "Masukkan ID Produk Utama: ";
                    cin >> id1;
                    cout << "Masukkan ID Produk Pasangan Bundling: ";
                    cin >> id2;
                    cin.ignore();
                    cout << "Masukkan Keterangan Relasi (contoh COMPATIBLE / BUNDLE): ";
                    getline(cin, ket);
                    tambahRelasiBundling(katalogProduk, id1, id2, ket);
                    cout << "Relasi bundling berhasil ditambahkan!" << endl;
                } else if (subMenu1 == 9) {
                    adrProduk pMax = findMaxHargaProduk(katalogProduk);
                    adrProduk pMin = findMinStokProduk(katalogProduk);
                    if (pMax != NULL) {
                        cout << "Produk Harga Tertinggi (FindMax) : " << pMax->info.namaProduk
                             << " (Rp" << pMax->info.harga << ")" << endl;
                    }
                    if (pMin != NULL) {
                        cout << "Produk Stok Paling Sedikit (FindMin): " << pMin->info.namaProduk
                             << " (Sisa Stok: " << pMin->info.stok
                             << ", Batas Min: " << pMin->info.stokMinimum << ")" << endl;
                    }
                }
            }
        } else if (pilihanUtama == 2) {
            int subMenu2 = -1;
            while (subMenu2 != 0) {
                cout << endl;
                cout << "--- [MENU 2: PENCARIAN & INDEKS PRODUK] ---" << endl;
                cout << "1. Cari ID Produk via Binary Search Tree (BST Search - O(log N))" << endl;
                cout << "2. Cari Nama Produk via Sequential Search pada Linked List (O(N))" << endl;
                cout << "3. Cari ID Produk via Binary Search pada Ordered Array (O(log N))" << endl;
                cout << "4. Tampilkan Semua Produk Terurut ID (Inorder Traversal BST)" << endl;
                cout << "5. Cari Produk ID Terkecil pada BST (FindMin BST)" << endl;
                cout << "0. Kembali ke Menu Utama" << endl;
                cout << "Pilih sub-menu: ";
                cin >> subMenu2;

                if (subMenu2 == 1) {
                    string cariId;
                    cout << "Masukkan ID Produk yang dicari di BST (contoh PRD-0042): ";
                    cin >> cariId;
                    adrBST hasil = findNodeBST(indeksBST, cariId);
                    if (hasil != NULL && hasil->refProduk != NULL) {
                        cout << "[DITEMUKAN DI BST]" << endl;
                        cout << "ID Produk   : " << hasil->refProduk->info.idProduk << endl;
                        cout << "Nama Produk : " << hasil->refProduk->info.namaProduk << endl;
                        cout << "Merek       : " << hasil->refProduk->info.merek << endl;
                        cout << "Harga       : Rp" << hasil->refProduk->info.harga << endl;
                        cout << "Stok        : " << hasil->refProduk->info.stok << endl;
                    } else {
                        cout << "Produk dengan ID " << cariId << " tidak ditemukan di BST." << endl;
                    }
                } else if (subMenu2 == 2) {
                    string kata;
                    cin.ignore();
                    cout << "Masukkan potongan nama produk (contoh SSD / Intel / DDR5): ";
                    getline(cin, kata);
                    searchProdukByNamaSequential(katalogProduk, kata);
                } else if (subMenu2 == 3) {
                    bangunArrayTerurutDariList(katalogProduk, arrayUrutID);
                    cout << "Ordered Array berhasil disusun (" << arrayUrutID.n << " elemen terurut ID)." << endl;
                    string target;
                    cout << "Masukkan ID Produk untuk Binary Search pada Ordered Array: ";
                    cin >> target;
                    int idx = binarySearchArray(arrayUrutID, target);
                    if (idx != -1) {
                        adrProduk P = arrayUrutID.tab[idx];
                        cout << "[DITEMUKAN PADA ORDERED ARRAY INDEKS KE-" << idx << "]" << endl;
                        cout << "Nama Produk : " << P->info.namaProduk << " | Harga: Rp" << P->info.harga << endl;
                    } else {
                        cout << "ID Produk tidak ditemukan pada Ordered Array." << endl;
                    }
                } else if (subMenu2 == 4) {
                    cout << "=== DAFTAR PRODUK TERURUT BERDASARKAN ID (INORDER BST) ===" << endl;
                    inOrderBST(indeksBST);
                } else if (subMenu2 == 5) {
                    adrBST minBst = findMinBST(indeksBST);
                    if (minBst != NULL && minBst->refProduk != NULL) {
                        cout << "Node dengan ID Terkecil di BST: " << minBst->keyId
                             << " (" << minBst->refProduk->info.namaProduk << ")" << endl;
                    }
                }
            }
        } else if (pilihanUtama == 3) {
            int subMenu3 = -1;
            while (subMenu3 != 0) {
                cout << endl;
                cout << "--- [MENU 3: ANTREAN PELANGGAN (QUEUE FIFO)] ---" << endl;
                cout << "1. Lihat Daftar Antrean Saat Ini" << endl;
                cout << "2. Tambah Pelanggan Baru ke Antrean (Enqueue)" << endl;
                cout << "3. Panggil Pelanggan Terdepan ke Meja Kasir (Dequeue)" << endl;
                cout << "4. Lihat Pelanggan Terdepan Tanpa Memanggil (Front)" << endl;
                cout << "0. Kembali ke Menu Utama" << endl;
                cout << "Pilih sub-menu: ";
                cin >> subMenu3;

                if (subMenu3 == 1) {
                    printQueue(antreanKasir);
                } else if (subMenu3 == 2) {
                    string nama, keperluan;
                    cin.ignore();
                    cout << "Masukkan Nama Pelanggan: ";
                    getline(cin, nama);
                    cout << "Masukkan Keperluan Belanja: ";
                    getline(cin, keperluan);
                    string noTiket = "A-00" + to_string(nomorTiketOtomatis);
                    nomorTiketOtomatis = nomorTiketOtomatis + 1;
                    adrQueue P = alokasiQueue(noTiket, nama, keperluan);
                    enqueue(antreanKasir, P);
                    cout << "Pelanggan " << nama << " masuk antrean dengan nomor " << noTiket << "." << endl;
                } else if (subMenu3 == 3) {
                    adrQueue P = NULL;
                    dequeue(antreanKasir, P);
                    if (P != NULL) {
                        pelangganAktif = P->info.nomorAntrean + " - " + P->info.namaPelanggan;
                        cout << "Memanggil pelanggan: " << pelangganAktif
                             << " (" << P->info.keperluan << ") ke meja kasir!" << endl;
                        dealokasiQueue(P);
                    } else {
                        cout << "Antrean kosong, tidak ada pelanggan yang bisa dipanggil." << endl;
                    }
                } else if (subMenu3 == 4) {
                    adrQueue depan = frontQueue(antreanKasir);
                    if (depan != NULL) {
                        cout << "Pelanggan terdepan: " << depan->info.nomorAntrean
                             << " - " << depan->info.namaPelanggan << endl;
                    } else {
                        cout << "Antrean kosong." << endl;
                    }
                }
            }
        } else if (pilihanUtama == 4) {
            int subMenu4 = -1;
            while (subMenu4 != 0) {
                cout << endl;
                cout << "--- [MENU 4: SIMULASI KERANJANG & UNDO/REDO (STACK LIFO)] ---" << endl;
                cout << "Pelanggan Dilayani: " << pelangganAktif << endl;
                cout << "1. Tambah Barang ke Keranjang (Push ke UndoStack)" << endl;
                cout << "2. Batalkan Aksi Terakhir / UNDO (Pop UndoStack -> Push RedoStack)" << endl;
                cout << "3. Ulangi Aksi Batal / REDO (Pop RedoStack -> Push UndoStack)" << endl;
                cout << "4. Lihat Isi Keranjang & Top Stack Saat Ini" << endl;
                cout << "0. Kembali ke Menu Utama" << endl;
                cout << "Pilih sub-menu: ";
                cin >> subMenu4;

                if (subMenu4 == 1) {
                    string idBeli;
                    int qtyBeli;
                    cout << "Masukkan ID Produk yang dibeli (contoh PRD-0100): ";
                    cin >> idBeli;
                    adrBST nodeProduk = findNodeBST(indeksBST, idBeli);
                    if (nodeProduk == NULL || nodeProduk->refProduk == NULL) {
                        cout << "Produk tidak ditemukan!" << endl;
                    } else {
                        adrProduk prod = nodeProduk->refProduk;
                        cout << "Produk ditemukan: " << prod->info.namaProduk
                             << " (Harga: Rp" << prod->info.harga
                             << ", Stok tersedia: " << prod->info.stok << ")" << endl;
                        cout << "Masukkan jumlah beli: ";
                        cin >> qtyBeli;
                        if (qtyBeli <= 0 || qtyBeli > prod->info.stok) {
                            cout << "Jumlah beli tidak valid atau melebihi stok!" << endl;
                        } else {
                            infotypeAksi aksi;
                            aksi.jenisAksi = "TAMBAH";
                            aksi.idProduk = prod->info.idProduk;
                            aksi.namaProduk = prod->info.namaProduk;
                            aksi.jumlah = qtyBeli;
                            aksi.hargaSatuan = prod->info.harga;

                            push(undoStack, alokasiStack(aksi));

                            adrStack hapusRedo = NULL;
                            while (!isEmptyStack(redoStack)) {
                                pop(redoStack, hapusRedo);
                                dealokasiStack(hapusRedo);
                            }

                            cout << "Berhasil menambahkan " << prod->info.namaProduk << " ke keranjang!" << endl;
                            printRekomendasiBundling(katalogProduk, prod->info.idProduk);
                        }
                    }
                } else if (subMenu4 == 2) {
                    if (isEmptyStack(undoStack)) {
                        cout << "Underflow Cegah: Tidak ada aksi yang bisa di-Undo!" << endl;
                    } else {
                        adrStack P = NULL;
                        pop(undoStack, P);
                        if (P != NULL) {
                            cout << "[UNDO BERHASIL] Membatalkan penambahan: "
                                 << P->info.namaProduk << " (x" << P->info.jumlah << ")" << endl;
                            push(redoStack, P);
                        }
                    }
                } else if (subMenu4 == 3) {
                    if (isEmptyStack(redoStack)) {
                        cout << "Underflow Cegah: Tidak ada aksi yang bisa di-Redo!" << endl;
                    } else {
                        adrStack P = NULL;
                        pop(redoStack, P);
                        if (P != NULL) {
                            cout << "[REDO BERHASIL] Mengembalikan ke keranjang: "
                                 << P->info.namaProduk << " (x" << P->info.jumlah << ")" << endl;
                            push(undoStack, P);
                        }
                    }
                } else if (subMenu4 == 4) {
                    printStackKeranjang(undoStack);
                }
            }
        }
    }

    cout << "Terima kasih telah menggunakan TechStock POS (Progress 1 - 45%)." << endl;
    return 0;
}
```

---

## Bagian 3: Bedah Detail Per Bagian Kode, Konsep Teknis Materi, dan Analogi Awam

Agar seluruh anggota kelompok dapat menjelaskan setiap baris kode dengan lancar saat asistensi atau presentasi di depan dosen, berikut adalah penjelasan rinci per blok kode:

### Pecahan 1: Deklarasi Pointer (`Address`) dan Struktur Elemen di `techstock.h`

```cpp
typedef struct elmKategori *adrKategori;
typedef struct elmProduk *adrProduk;
typedef struct elmRelasi *adrRelasi;
typedef struct elmQueue *adrQueue;
typedef struct elmStack *adrStack;
typedef struct nodeBST *adrBST;
```

- **Kode Ini Untuk Apa?**
  Mendefinisikan tipe data *pointer* (`Address`) yang menunjuk ke alamat memori dari masing-masing *node* atau elemen struktur data.
- **Bagaimana Cara Kerjanya & Konsep Teknis Materi (Slide 01 & Slide 02 hal. 30–34):**
  Dalam pseudocode perkuliahan Struktur Data, tertulis `type Address : pointer to ElmList`. Di C++, tanda bintang (`*`) berarti variabel tersebut tidak menyimpan data barang secara langsung, melainkan menyimpan **alamat memori heksadesimal** (seperti `0x37` atau `0x2024` pada Slide 01 hal. 3 & Slide 02 hal. 44) tempat elemen tersebut berada di RAM.
- **Analogi Awam:**
  Bayangkan sebuah gudang toko komputer yang sangat luas. Daripada kita mengangkat-angkat kardus PC yang berat ke meja kasir setiap kali ingin mengecek barang, kita cukup memegang **selembar kertas kecil berisi nomor rak gudang** (misalnya *"Rak B-12"*). Kertas kecil berisi nomor lokasi itulah yang disebut **Pointer (`Address`)**, sedangkan kardus PC di dalam rak adalah **Elemen (`elmProduk`)**-nya.

---

### Pecahan 2: Doubly Linked List (DLL) Katalog Produk & Penanganan Kondisi Khusus (`Special Conditions`)

```cpp
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
```

```cpp
void insertLastProduk(ListProduk &LP, adrProduk P) {
    if (!isEmptyProduk(LP)) {
        P->prev = LP.last;
        LP.last->next = P;
        LP.last = P;
    } else {
        LP.first = P;
        LP.last = P;
    }
}

void deleteLastProduk(ListProduk &LP, adrProduk &P) {
    if (isEmptyProduk(LP)) {
        P = NULL;
    } else if (LP.first != LP.last) {
        P = LP.last;
        LP.last = LP.last->prev;
        P->prev = NULL;
        LP.last->next = NULL;
    } else {
        P = LP.last;
        LP.first = NULL;
        LP.last = NULL;
    }
}
```

- **Kode Ini Untuk Apa?**
  Mengelola katalog utama produk toko menggunakan struktur **Doubly Linked List (DLL)** agar produk bisa ditambah dari belakang (`insertLastProduk`), dihapus dari belakang (`deleteLastProduk`) dalam waktu konstan $O(1)$, dan ditelusuri maju (`printProdukMaju`) maupun mundur (`printProdukMundur`).
- **Bagaimana Cara Kerjanya & Konsep Teknis Materi (Slide 03 hal. 3–26):**
  1. Setiap node `elmProduk` memiliki dua tangan penunjuk arah: `next` (menunjuk elemen sesudahnya) dan `prev` (menunjuk elemen sebelumnya), sedangkan `ListProduk` memegang dua penanda ujung: `first` dan `last`.
  2. Saat `insertLastProduk`: jika list tidak kosong, tangan kiri node baru (`P->prev`) memegang elemen terakhir lama (`LP.last`), tangan kanan elemen terakhir lama (`LP.last->next`) memegang `P`, lalu gelar elemen terakhir (`LP.last`) dipindahkan ke `P`.
  3. **Poin Penting Evaluasi Dosen (*Hal Mendasar Jangan Terlewat*):** Perhatikan percabangan `else if (LP.first != LP.last)` dan `else` pada `deleteLastProduk`! Sesuai **Slide 03 hal. 24–26**, jika elemen di dalam list **hanya tersisa 1 buah** (`LP.first == LP.last`), kita tidak boleh menjalankan `LP.last->next = NULL` setelah `LP.last` mundur ke `NULL` karena akan menyebabkan program *crash* (*Null Pointer Dereference*). Selain itu, `deleteLastProduk` hanya melepas elemen `P` dari rangkaian list; penghapusan memori baru dilakukan saat memanggil `dealokasiProduk(P)`.
- **Analogi Awam:**
  Bayangkan barisan gerbong kereta api yang punya pengait di depan (`prev`) dan di belakang (`next`), serta kepala stasiun yang mencatat gerbong paling depan (`first`) dan gerbong paling buntut (`last`). Kalau kita mau melepas gerbong paling buntut (`deleteLast`), kita tidak perlu berjalan kaki dari lokomotif depan sampai ke belakang; kita cukup langsung ke gerbong `last`, melihat gerbong di depannya lewat pengait `prev`, lalu melepas sambungannya dalam sekejap!

---

### Pecahan 3: Multi-Linked List (MLL) Relasi 1-to-N (Kategori) dan M-to-N (Bundling)

```cpp
void setKategoriProduk(ListProduk &LP, ListKategori LK, string idProduk, string idKategori) {
    adrProduk P = searchProdukByIdSequential(LP, idProduk);
    adrKategori Q = searchKategori(LK, idKategori);
    if (P != NULL && Q != NULL) {
        P->nextKategori = Q;
    }
}

void hapusKategoriBesertaRelasi(ListProduk &LP, ListKategori &LK, string idKategori) {
    adrKategori Q = searchKategori(LK, idKategori);
    if (Q != NULL) {
        adrProduk P = LP.first;
        while (P != NULL) {
            if (P->nextKategori == Q) {
                P->nextKategori = NULL;
            }
            P = P->next;
        }
        ...
```

```cpp
void tambahRelasiBundling(ListProduk &LP, string idUtama, string idPasangan, string ket) {
    adrProduk P = searchProdukByIdSequential(LP, idUtama);
    adrProduk Q = searchProdukByIdSequential(LP, idPasangan);
    if (P != NULL && Q != NULL && P != Q) {
        adrRelasi R = alokasiRelasi(Q, ket);
        insertLastRelasi(P->relasiBundling, R);
    }
}
```

- **Kode Ini Untuk Apa?**
  Memodelkan keterkaitan antar data di toko komputer menggunakan dua model **Multi-Linked List (MLL)** sesuai **Slide 06**:
  1. **Relasi 1-to-N (`setKategoriProduk` & `hapusKategoriBesertaRelasi`):** Menghubungkan banyak produk ke satu kategori induk.
  2. **Relasi M-to-N (`tambahRelasiBundling` & `emptyListRelasi`):** Menghubungkan satu produk dengan banyak produk pasangan yang kompatibel atau diskon bundling.
- **Bagaimana Cara Kerjanya & Konsep Teknis Materi (Slide 06 hal. 10–31):**
  1. Pada **Relasi 1-to-N** (identik dengan *Example 4: Student – Class* di **Slide 06 hal. 14–18**), setiap elemen produk `P` memiliki pointer `nextKategori` yang langsung menunjuk ke alamat elemen kategori `Q` di `ListKategori`. Ketika admin menghapus sebuah kategori (`hapusKategoriBesertaRelasi`), program wajib melakukan *looping* ke seluruh `ListProduk` terlebih dahulu: setiap produk yang `P->nextKategori == Q` harus diubah menjadi `NULL` sebelum node `Q` dihapus dari memori. Ini mencegah *dangling pointer* (pointer menunjuk alamat memori yang sudah dihancurkan).
  2. Pada **Relasi M-to-N** (identik dengan *Example 5: Student – Course* di **Slide 06 hal. 22–29**), setiap elemen produk memiliki sub-list kecil (`ListRelasi relasiBundling`) di dalamnya. Setiap elemen `elmRelasi` menyimpan pointer `targetProduk` yang menunjuk ke produk pasangan di katalog. Saat suatu produk akan didealokasi (`dealokasiProduk`), prosedur `emptyListRelasi` wajib dipanggil dulu agar sub-list relasinya tidak tertinggal menjadi sampah memori (*memory leak*).
- **Analogi Awam:**
  - **1-to-N (Kategori):** Seperti siswa dan wali kelas. Banyak siswa bisa menunjuk ke 1 wali kelas yang sama. Kalau wali kelas tersebut pindah sekolah (dihapus), data wali kelas di kartu tiap siswa harus dikosongkan dulu supaya siswa tidak menunjuk ruangan kosong.
  - **M-to-N (Bundling):** Seperti daftar "Teman Dekat" di kontak HP. Di dalam kartu produk *CPU Intel i5*, ada daftar catatan kecil berisi kontak *Motherboard B760M*, *RAM DDR5*, dan *CPU Cooler* yang cocok dipasang bersamanya.

---

### Pecahan 4: Binary Search Tree (BST) untuk Indeks ID Produk (`insertBST`, `findNodeBST`, `inOrderBST`)

```cpp
void insertBST(BinTree &root, string id, adrProduk ref) {
    if (root == NULL) {
        root = createNodeBST(id, ref);
    } else {
        if (root->keyId > id) {
            insertBST(root->left, id, ref);
        } else if (root->keyId < id) {
            insertBST(root->right, id, ref);
        } else {
            cout << "ID produk duplikat pada BST." << endl;
        }
    }
}

adrBST findNodeBST(BinTree root, string id) {
    if (root == NULL || root->keyId == id) {
        return root;
    } else {
        if (root->keyId > id) {
            return findNodeBST(root->left, id);
        } else {
            return findNodeBST(root->right, id);
        }
    }
}
```

- **Kode Ini Untuk Apa?**
  Menyediakan indeks pencarian kilat berdasarkan ID Produk (`PRD-xxxx`) dan menampilkan produk secara terurut otomatis menggunakan struktur pohon biner **Binary Search Tree (BST)**.
- **Bagaimana Cara Kerjanya & Konsep Teknis Materi (Slide 07 hal. 45–47 & 115–116):**
  1. Mengikuti aturan **BST Invariant** (**Slide 07 hal. 45**): semua node di sub-pohon kiri (`left`) pasti memiliki `keyId` lebih kecil dari induknya, dan semua node di sub-pohon kanan (`right`) memiliki `keyId` lebih besar dari induknya.
  2. Node BST tidak menduplikasi seluruh data barang, melainkan hanya menyimpan `keyId` dan sebuah pointer `refProduk` yang menunjuk langsung ke node barang asli di `ListProduk` (DLL).
  3. Saat mencari ID (`findNodeBST`), setiap langkah perbandingan langsung membuang separuh cabang pohon yang tidak mungkin, menghasilkan kompleksitas waktu rata-rata **$O(\log N)$**.
  4. Saat memanggil `inOrderBST` (kiri $\rightarrow$ induk $\rightarrow$ kanan, **Slide 07 hal. 115–116**), seluruh produk otomatis tercetak berurutan dari ID terkecil (`PRD-0010`) hingga terbesar (`PRD-0300`) tanpa perlu algoritma *sorting* tambahan!
- **Analogi Awam:**
  Bayangkan papan penunjuk jalan bercabang di persimpangan. Kalau kamu mencari kamar nomor `0042` dan saat ini berdiri di depan papan nomor `0100`, papan itu langsung menyuruhmu belok ke **Kiri** (karena `0042` lebih kecil dari `0100`). Kamu tidak perlu mengetuk pintu kamar nomor `0150`, `0200`, atau `0300` yang ada di sebelah kanan.

---

### Pecahan 5: Perbandingan Sequential Search (Linked List) vs Binary Search (Ordered Array)

```cpp
void insertSortedArray(ArrayTerurutProduk &A, adrProduk P) {
    if (A.n >= MAX_ARRAY || P == NULL) {
        return;
    }
    int i = 0;
    while (i < A.n && A.tab[i]->info.idProduk < P->info.idProduk) {
        i = i + 1;
    }
    adrProduk temp1 = A.tab[i];
    A.tab[i] = P;
    for (int j = i + 1; j <= A.n; j++) {
        adrProduk temp2 = A.tab[j];
        A.tab[j] = temp1;
        temp1 = temp2;
    }
    A.n = A.n + 1;
}

int binarySearchArray(ArrayTerurutProduk A, string targetId) {
    int kiri = 0;
    int kanan = A.n - 1;
    while (kiri <= kanan) {
        int tengah = (kiri + kanan) / 2;
        if (A.tab[tengah]->info.idProduk == targetId) {
            return tengah;
        } else if (A.tab[tengah]->info.idProduk < targetId) {
            kiri = tengah + 1;
        } else {
            kanan = tengah - 1;
        }
    }
    return -1;
}
```

- **Kode Ini Untuk Apa?**
  Menjawab langsung evaluasi dosen mengenai **riset metode pencarian Binary Search vs Sequential Search**.
- **Bagaimana Cara Kerjanya & Konsep Teknis Materi (Slide 02 hal. 2–5 & hal. 96–108):**
  1. Prosedur `insertSortedArray` mengimplementasikan algoritma **Insert into a Sorted Array** persis seperti pada **Slide 02 hal. 3–5** (menggunakan variabel `temp1` dan `temp2` untuk menggeser elemen array agar array selalu terjaga urutannya setiap kali elemen dimasukkan, lalu meng-update ukuran `A.n = A.n + 1`).
  2. Fungsi `binarySearchArray` kemudian melakukan pencarian dengan membelah indeks array `tengah = (kiri + kanan) / 2`. Karena disimpan di dalam **Ordered Array (`O-Array`)**, pengaksesan `A.tab[tengah]` membutuhkan waktu $O(1)$, sehingga keseluruhan *Binary Search* benar-benar berjalan dalam waktu **$O(\log N)$**.
  3. Sebaliknya, untuk pencarian nama produk di dalam Linked List (`searchProdukByNamaSequential`), kita menggunakan **Sequential Search** ($O(N)$) karena Linked List tidak memiliki indeks array dan pencarian nama bersifat cocok-sebagian (*substring*).
- **Analogi Awam:**
  - **Sequential Search di Linked List:** Seperti mencari orang di gerbong kereta api yang tidak bernomor kursi; kita harus masuk dari gerbong pertama lalu berjalan melewati sambungan gerbong satu per satu sampai ketemu.
  - **Binary Search di Ordered Array:** Seperti membuka kamus bahasa Inggris yang halamannya bernomor urut. Kita langsung buka halaman tengahnya; kalau kata yang dicari berawalan huruf 'S' sedangkan halaman tengah baru huruf 'M', kita langsung buang separuh bagian depan kamus dan fokus ke separuh bagian belakang.

---

### Pecahan 6: Queue (Doubly Linked Queue) untuk Antrean Pelanggan FIFO

```cpp
void enqueue(QueuePelanggan &Q, adrQueue P) {
    if (isEmptyQueue(Q)) {
        Q.head = P;
        Q.tail = P;
    } else {
        P->prev = Q.tail;
        Q.tail->next = P;
        Q.tail = P;
    }
}

void dequeue(QueuePelanggan &Q, adrQueue &P) {
    P = Q.head;
    if (!isEmptyQueue(Q)) {
        if (Q.head != Q.tail) {
            Q.head = P->next;
            P->next = NULL;
            Q.head->prev = NULL;
        } else {
            Q.head = NULL;
            Q.tail = NULL;
        }
    }
}
```

- **Kode Ini Untuk Apa?**
  Mengatur antrean pelanggan di meja kasir dengan prinsip **FIFO (*First-In First-Out*)** menggunakan representasi Linked List sesuai **Slide 05 hal. 52–60**.
- **Bagaimana Cara Kerjanya & Konsep Teknis Materi (Slide 05 hal. 52–58):**
  1. Sesuai **Slide 05 hal. 52**, Queue berbasis Linked List di mata kuliah Struktur Data kita adalah **Doubly Linked List yang dibatasi operasinya**: penambahan (`enqueue`) hanya boleh dilakukan di ujung belakang (`Q.tail` / *Insert Last*) dan penghapusan (`dequeue`) hanya boleh dilakukan di ujung depan (`Q.head` / *Delete First*).
  2. Ketika antrean hanya menyisakan 1 pelanggan (`Q.head == Q.tail`) dan dipanggil (`dequeue`), baik `Q.head` maupun `Q.tail` wajib di-reset menjadi `NULL` agar tidak menyisakan *dangling pointer* di `tail`.
- **Analogi Awam:**
  Persis seperti antrean loket tiket bioskop: orang yang baru datang wajib baris di paling belakang (`tail` / `enqueue`), sedangkan kasir selalu memanggil orang yang berdiri paling depan (`head` / `dequeue`).

---

### Pecahan 7: Stack (Linked List Stack) untuk Simulasi Keranjang & Undo/Redo Kasir

```cpp
void push(StackAksi &S, adrStack P) {
    if (isEmptyStack(S)) {
        S.top = P;
    } else {
        P->next = S.top;
        S.top = P;
    }
}

void pop(StackAksi &S, adrStack &P) {
    if (isEmptyStack(S)) {
        P = NULL;
    } else if (S.top->next == NULL) {
        P = S.top;
        S.top = NULL;
    } else {
        P = S.top;
        S.top = S.top->next;
        P->next = NULL;
    }
}
```

- **Kode Ini Untuk Apa?**
  Mencatat riwayat aksi penambahan item di meja kasir serta menangani fitur **Undo** (batalkan aksi terakhir) dan **Redo** (kembalikan aksi yang baru dibatalkan) menggunakan dua buah **Stack** (`undoStack` dan `redoStack`) berprinsip **LIFO (*Last-In First-Out*)**.
- **Bagaimana Cara Kerjanya & Konsep Teknis Materi (Slide 04 hal. 64–71):**
  1. Menggunakan **Linked List Representation of Stack** (**Slide 04 hal. 65**), di mana `S.top` menunjuk elemen paling atas tumpukan.
  2. Operasi `push` sama dengan `insertFirst` di ujung `S.top` ($O(1)$), sedangkan operasi `pop` sama dengan `deleteFirst` dari ujung `S.top` ($O(1)$) dengan penanganan kondisi 1 elemen (`S.top->next == NULL`, **Slide 04 hal. 70**).
  3. Saat kasir menambah barang baru ke keranjang, aksi di-`push` ke `undoStack` dan seluruh isi `redoStack` dikosongkan. Saat kasir menekan **Undo**, elemen teratas di-`pop` dari `undoStack` lalu langsung di-`push` ke `redoStack` (tanpa perlu alokasi memori baru!). Sebaliknya saat menekan **Redo**, elemen di-`pop` dari `redoStack` dan di-`push` kembali ke `undoStack`.
- **Analogi Awam:**
  Bayangkan dua tumpukan piring di meja kasir: Tumpukan Kiri (`undoStack`) dan Tumpukan Kanan (`redoStack`). Setiap kali kasir menaruh barang, piring catatan ditaruh di paling atas Tumpukan Kiri. Kalau kasir salah input dan menekan *Undo*, kasir tinggal mengangkat piring paling atas dari Tumpukan Kiri lalu menaruhnya di atas Tumpukan Kanan. Kalau ternyata tidak jadi batal (*Redo*), piring paling atas di Tumpukan Kanan tinggal diangkat balik ke Tumpukan Kiri.
