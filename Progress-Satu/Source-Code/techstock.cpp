#include "techstock.h"

void createListAkun(ListAkun &LA) {
    LA.first = NULL;
}

adrAkun alokasiAkun(string user, string pass, string role, string nama) {
    adrAkun P = new elmAkun;
    P->info.username = user;
    P->info.password = pass;
    P->info.role = role;
    P->info.nama = nama;
    P->next = NULL;
    return P;
}

void insertLastAkun(ListAkun &LA, adrAkun P) {
    if (LA.first == NULL) {
        LA.first = P;
    } else {
        adrAkun Q = LA.first;
        while (Q->next != NULL) {
            Q = Q->next;
        }
        Q->next = P;
    }
}

adrAkun cariAkun(ListAkun LA, string user, string pass) {
    adrAkun P = LA.first;
    while (P != NULL) {
        if (P->info.username == user && P->info.password == pass) {
            return P;
        }
        P = P->next;
    }
    return NULL;
}

adrAkun cariUsername(ListAkun LA, string user) {
    adrAkun P = LA.first;
    while (P != NULL && P->info.username != user) {
        P = P->next;
    }
    return P;
}

void printAkun(ListAkun LA) {
    int wUser = 8;  // Panjang header "USERNAME"
    int wRole = 4;  // Panjang header "ROLE"
    int wNama = 13; // Panjang header "NAMA PENGGUNA"

    adrAkun P = LA.first;
    while (P != NULL) {
        if ((int)P->info.username.length() > wUser) wUser = P->info.username.length();
        if ((int)P->info.role.length() > wRole) wRole = P->info.role.length();
        if ((int)P->info.nama.length() > wNama) wNama = P->info.nama.length();
        P = P->next;
    }

    int totalLebar = wUser + wRole + wNama + 6;
    string garis(totalLebar, '=');

    cout << garis << endl;
    cout << left << setw(wUser) << "USERNAME" << " | "
         << left << setw(wRole) << "ROLE" << " | "
         << left << setw(wNama) << "NAMA PENGGUNA" << endl;
    cout << garis << endl;

    P = LA.first;
    while (P != NULL) {
        cout << left << setw(wUser) << P->info.username << " | "
             << left << setw(wRole) << P->info.role << " | "
             << left << setw(wNama) << P->info.nama << endl;
        P = P->next;
    }
    cout << garis << endl;
}

void simpanAkun(ListAkun LA, string namaFile) {
    ofstream fileOut(namaFile.c_str());
    if (fileOut.is_open()) {
        adrAkun P = LA.first;
        while (P != NULL) {
            fileOut << P->info.username << " "
                    << P->info.password << " "
                    << P->info.role << " "
                    << P->info.nama << endl;
            P = P->next;
        }
        fileOut.close();
    }
}

void muatAkun(ListAkun &LA, string namaFile) {
    ifstream fileIn(namaFile.c_str());
    if (!fileIn.is_open()) {
        insertLastAkun(LA, alokasiAkun("admin", "admin123", "ADMIN", "Ahlan_Admin"));
        insertLastAkun(LA, alokasiAkun("kasir1", "kasir123", "KASIR", "Sofwan_Kasir"));
        simpanAkun(LA, namaFile);
        return;
    }

    string user, pass, role, nama;
    while (fileIn >> user >> pass >> role >> nama) {
        insertLastAkun(LA, alokasiAkun(user, pass, role, nama));
    }
    fileIn.close();
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
    return P;
}

void dealokasiProduk(adrProduk &P) {
    delete P;
    P = NULL;
}

bool isEmptyProduk(ListProduk LP) {
    return LP.first == NULL && LP.last == NULL;
}

void insertLastProduk(ListProduk &LP, adrProduk P) {
    if (isEmptyProduk(LP)) {
        LP.first = P;
        LP.last = P;
    } else {
        P->prev = LP.last;
        LP.last->next = P;
        LP.last = P;
    }
}

void deleteLastProduk(ListProduk &LP, adrProduk &P) {
    if (isEmptyProduk(LP)) {
        P = NULL;
    } else if (LP.first == LP.last) {
        P = LP.last;
        LP.first = NULL;
        LP.last = NULL;
    } else {
        P = LP.last;
        LP.last = LP.last->prev;
        P->prev = NULL;
        LP.last->next = NULL;
    }
}

adrProduk cariProduk(ListProduk LP, string id) {
    adrProduk P = LP.first;
    while (P != NULL && P->info.idProduk != id) {
        P = P->next;
    }
    return P;
}

void printProdukMaju(ListProduk LP) {
    if (isEmptyProduk(LP)) {
        cout << "Katalog produk masih kosong." << endl;
    } else {
        int wId = 2;     // Panjang header "ID"
        int wNama = 11;  // Panjang header "NAMA PRODUK"
        int wKat = 8;    // Panjang header "KATEGORI"
        int wHarga = 5;  // Panjang header "HARGA"
        int wStok = 4;   // Panjang header "STOK"

        adrProduk P = LP.first;
        while (P != NULL) {
            string teksHarga = "Rp" + to_string(P->info.harga);
            string teksStok = to_string(P->info.stok);

            if ((int)P->info.idProduk.length() > wId) wId = P->info.idProduk.length();
            if ((int)P->info.namaProduk.length() > wNama) wNama = P->info.namaProduk.length();
            if ((int)P->info.kategori.length() > wKat) wKat = P->info.kategori.length();
            if ((int)teksHarga.length() > wHarga) wHarga = teksHarga.length();
            if ((int)teksStok.length() > wStok) wStok = teksStok.length();
            P = P->next;
        }

        int totalLebar = wId + wNama + wKat + wHarga + wStok + 12;
        string garis(totalLebar, '=');

        cout << garis << endl;
        cout << left << setw(wId) << "ID" << " | "
             << left << setw(wNama) << "NAMA PRODUK" << " | "
             << left << setw(wKat) << "KATEGORI" << " | "
             << left << setw(wHarga) << "HARGA" << " | "
             << left << setw(wStok) << "STOK" << endl;
        cout << garis << endl;

        P = LP.first;
        while (P != NULL) {
            string teksHarga = "Rp" + to_string(P->info.harga);
            cout << left << setw(wId) << P->info.idProduk << " | "
                 << left << setw(wNama) << P->info.namaProduk << " | "
                 << left << setw(wKat) << P->info.kategori << " | "
                 << left << setw(wHarga) << teksHarga << " | "
                 << left << setw(wStok) << P->info.stok << endl;
            P = P->next;
        }
        cout << garis << endl;
    }
}

void printProdukMundur(ListProduk LP) {
    if (isEmptyProduk(LP)) {
        cout << "Katalog produk masih kosong." << endl;
    } else {
        int wId = 2;     // Panjang header "ID"
        int wNama = 11;  // Panjang header "NAMA PRODUK"
        int wKat = 8;    // Panjang header "KATEGORI"
        int wHarga = 5;  // Panjang header "HARGA"
        int wStok = 4;   // Panjang header "STOK"

        adrProduk P = LP.last;
        while (P != NULL) {
            string teksHarga = "Rp" + to_string(P->info.harga);
            string teksStok = to_string(P->info.stok);

            if ((int)P->info.idProduk.length() > wId) wId = P->info.idProduk.length();
            if ((int)P->info.namaProduk.length() > wNama) wNama = P->info.namaProduk.length();
            if ((int)P->info.kategori.length() > wKat) wKat = P->info.kategori.length();
            if ((int)teksHarga.length() > wHarga) wHarga = teksHarga.length();
            if ((int)teksStok.length() > wStok) wStok = teksStok.length();
            P = P->prev;
        }

        int totalLebar = wId + wNama + wKat + wHarga + wStok + 12;
        string judul = "KATALOG PRODUK DARI INPUT TERBARU (MUNDUR: LAST KE FIRST)";
        if ((int)judul.length() > totalLebar) totalLebar = judul.length();
        string garis(totalLebar, '=');

        cout << garis << endl;
        cout << judul << endl;
        cout << garis << endl;
        cout << left << setw(wId) << "ID" << " | "
             << left << setw(wNama) << "NAMA PRODUK" << " | "
             << left << setw(wKat) << "KATEGORI" << " | "
             << left << setw(wHarga) << "HARGA" << " | "
             << left << setw(wStok) << "STOK" << endl;
        cout << garis << endl;

        P = LP.last;
        while (P != NULL) {
            string teksHarga = "Rp" + to_string(P->info.harga);
            cout << left << setw(wId) << P->info.idProduk << " | "
                 << left << setw(wNama) << P->info.namaProduk << " | "
                 << left << setw(wKat) << P->info.kategori << " | "
                 << left << setw(wHarga) << teksHarga << " | "
                 << left << setw(wStok) << P->info.stok << endl;
            P = P->prev;
        }
        cout << garis << endl;
    }
}

void simpanProduk(ListProduk LP, string namaFile) {
    ofstream fileOut(namaFile.c_str());
    if (fileOut.is_open()) {
        adrProduk P = LP.first;
        while (P != NULL) {
            fileOut << P->info.idProduk << " "
                    << P->info.namaProduk << " "
                    << P->info.kategori << " "
                    << P->info.harga << " "
                    << P->info.stok << endl;
            P = P->next;
        }
        fileOut.close();
    }
}

void muatProduk(ListProduk &LP, string namaFile) {
    ifstream fileIn(namaFile.c_str());
    if (!fileIn.is_open()) {
        infotypeProduk p1 = {"PRD-001", "Intel_Core_i5", "Processor", 3250000, 10};
        infotypeProduk p2 = {"PRD-002", "ASUS_B760M", "Motherboard", 2450000, 6};
        infotypeProduk p3 = {"PRD-003", "RAM_Kingston_16GB", "Memory", 950000, 20};
        infotypeProduk p4 = {"PRD-004", "SSD_Samsung_1TB", "Storage", 1450000, 5};

        insertLastProduk(LP, alokasiProduk(p1));
        insertLastProduk(LP, alokasiProduk(p2));
        insertLastProduk(LP, alokasiProduk(p3));
        insertLastProduk(LP, alokasiProduk(p4));
        simpanProduk(LP, namaFile);
        return;
    }

    infotypeProduk d;
    while (fileIn >> d.idProduk >> d.namaProduk >> d.kategori >> d.harga >> d.stok) {
        insertLastProduk(LP, alokasiProduk(d));
    }
    fileIn.close();
}