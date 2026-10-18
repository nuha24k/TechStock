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