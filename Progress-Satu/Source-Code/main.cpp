#include "techstock.h"

int main() {
    ListAkun daftarAkun;
    ListProduk katalogProduk;

    createListAkun(daftarAkun);
    createListProduk(katalogProduk);

    muatAkun(daftarAkun, "Akun/akun.txt");
    muatProduk(katalogProduk, "Produk/produk.txt");

    int pilihAwal = -1;
    while (pilihAwal != 0) {
        cout << endl;
        cout << "==========================================" << endl;
        cout << "          APLIKASI TECHSTOCK POS          " << endl;
        cout << "==========================================" << endl;
        cout << "1. Login Pengguna" << endl;
        // cout << "2. Registrasi User Baru" << endl;
        cout << "0. Keluar Aplikasi" << endl;
        cout << "------------------------------------------" << endl;
        cout << "Pilih menu: ";
        cin >> pilihAwal;

        if (pilihAwal == 1) {
            string user, pass;
            cout << "Username : ";
            cin >> user;
            cout << "Password : ";
            cin >> pass;

            adrAkun akunAktif = cariAkun(daftarAkun, user, pass);
            if (akunAktif == NULL) {
                cout << "Login gagal! Username atau password salah." << endl;
            } else {
                cout << "Login berhasil! Selamat datang, " << akunAktif->info.nama
                     << " (" << akunAktif->info.role << ")" << endl;

                int pilihMenu = -1;
                while (pilihMenu != 0) {
                    cout << endl;
                    cout << "==========================================" << endl;
                    cout << "         MENU UTAMA TECHSTOCK POS         " << endl;
                    cout << "==========================================" << endl;
                    cout << "User Aktif : " << akunAktif->info.nama
                         << " [" << akunAktif->info.role << "]" << endl;
                    cout << "------------------------------------------" << endl;
                    cout << "1. Lihat Katalog Produk (Maju)" << endl;
                    cout << "2. Lihat Katalog Produk (Mundur)" << endl;
                    cout << "3. Cari Produk Berdasarkan ID" << endl;

                    if (akunAktif->info.role == "ADMIN") {
                        cout << "4. [Admin] Tambah Produk Baru" << endl;
                        cout << "5. [Admin] Hapus Produk Terakhir" << endl;
                        cout << "6. [Admin] Lihat Daftar User" << endl;
                        cout << "7. [Admin] Tambah User Baru" << endl;
                    }

                    cout << "0. Logout" << endl;
                    cout << "------------------------------------------" << endl;
                    cout << "Pilih menu: ";
                    cin >> pilihMenu;

                    if (pilihMenu == 1) {
                        printProdukMaju(katalogProduk);
                    } else if (pilihMenu == 2) {
                        printProdukMundur(katalogProduk);
                    } else if (pilihMenu == 3) {
                        string idCari;
                        cout << "Masukkan ID Produk (contoh PRD-001): ";
                        cin >> idCari;
                        adrProduk P = cariProduk(katalogProduk, idCari);
                        if (P != NULL) {
                            cout << "Ditemukan: " << P->info.idProduk << " | "
                                 << P->info.namaProduk << " | "
                                 << P->info.kategori << " | Rp"
                                 << P->info.harga << " | Stok: "
                                 << P->info.stok << endl;
                        } else {
                            cout << "Produk tidak ditemukan." << endl;
                        }
                    } else if (pilihMenu == 4 && akunAktif->info.role == "ADMIN") {
                        infotypeProduk dataBaru;
                        cout << "ID Produk (contoh PRD-005)       : ";
                        cin >> dataBaru.idProduk;
                        cout << "Nama Produk (tanpa spasi/pakai _): ";
                        cin >> dataBaru.namaProduk;
                        cout << "Kategori                         : ";
                        cin >> dataBaru.kategori;
                        cout << "Harga                            : ";
                        cin >> dataBaru.harga;
                        cout << "Stok                             : ";
                        cin >> dataBaru.stok;

                        if (cariProduk(katalogProduk, dataBaru.idProduk) != NULL) {
                            cout << "ID produk sudah ada. Tidak boleh duplikat." << endl;
                        } else {
                            insertLastProduk(katalogProduk, alokasiProduk(dataBaru));
                            simpanProduk(katalogProduk, "Produk/produk.txt");
                            cout << "Produk berhasil ditambahkan!" << endl;
                        }
                        // insertLastProduk(katalogProduk, alokasiProduk(dataBaru));
                        // simpanProduk(katalogProduk, "Produk/produk.txt");
                        // cout << "Produk berhasil ditambahkan ke Produk/produk.txt!" << endl;
                    } else if (pilihMenu == 5 && akunAktif->info.role == "ADMIN") {
                        adrProduk P = NULL;
                        deleteLastProduk(katalogProduk, P);
                        if (P != NULL) {
                            cout << "Produk " << P->info.namaProduk << " berhasil dihapus." << endl;
                            dealokasiProduk(P);
                            simpanProduk(katalogProduk, "Produk/produk.txt");
                        } else {
                            cout << "Katalog produk sudah kosong." << endl;
                        }
                    } else if (pilihMenu == 6 && akunAktif->info.role == "ADMIN") {
                        printAkun(daftarAkun);
                    } else if (pilihMenu == 7 && akunAktif->info.role == "ADMIN") {
                        string user, pass, role, nama;
                        cout << "Username Baru                    : ";
                        cin >> user;
                        cout << "Password                         : ";
                        cin >> pass;
                        cout << "Role (ADMIN/KASIR)               : ";
                        cin >> role;
                        cout << "Nama Pengguna (pakai _ jika >1)  : ";
                        cin >> nama;

                        if (cariUsername(daftarAkun, user) != NULL) {
                            cout << "Username sudah ada. Tidak boleh duplikat" << endl;
                        } else if (role != "ADMIN" && role != "KASIR") {
                            cout << "Role ditolak! Penulisan role harus ADMIN atau KASIR (huruf kapital)." << endl;
                        } else {
                            insertLastAkun(daftarAkun, alokasiAkun(user, pass, role, nama));
                            simpanAkun(daftarAkun, "Akun/akun.txt");
                            cout << "User baru berhasil disimpan ke Akun/akun.txt!" << endl;
                        }
                    } else if (pilihMenu == 0) {
                        cout << "Logout berhasil." << endl;
                    } else {
                        cout << "Menu tidak tersedia." << endl;
                    }
                }
            }
        // } else if (pilihAwal == 2) {
        //     string user, pass, role, nama;
        //     cout << "Username Baru                    : ";
        //     cin >> user;
        //     cout << "Password                         : ";
        //     cin >> pass;
        //     cout << "Role (ADMIN/KASIR)               : ";
        //     cin >> role;
        //     cout << "Nama Pengguna (pakai _ jika >1)  : ";
        //     cin >> nama;

        //     if (cariUsername(daftarAkun, user) != NULL) {
        //         cout << "Username sudah ada. Tidak boleh duplikat" << endl;
        //     } else {
        //         insertLastAkun(daftarAkun, alokasiAkun(user, pass, role, nama));
        //         simpanAkun(daftarAkun, "Akun/akun.txt");
        //         cout << "User baru berhasil disimpan ke Akun/akun.txt!" << endl;
        //     }
        } else if (pilihAwal != 0) {
            cout << "Pilihan tidak valid." << endl;
        }
    }

    cout << "Terima kasih telah menggunakan TechStock POS." << endl;
    return 0;
}