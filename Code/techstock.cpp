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
    if (isEmptyKategori(LK) || Prec == NULL || Prec->next == NULL) {
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
    if (!isEmptyProduk(LP) && Prec != NULL) {
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
    if (isEmptyProduk(LP) || Prec == NULL || Prec->next == NULL) {
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