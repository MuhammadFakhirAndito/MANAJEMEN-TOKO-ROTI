#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

struct roti {
    char nama[20];
    int id, stok;
    float harga;
};
	
roti dataroti[100];
int r = 0;
char nama_invoice[20];
float harga_invoice;
int jumlah_invoice;
float total_invoice;

// Fungsi helper untuk membandingkan string nama secara manual menggunakan pointer
int bandingkanNama(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

// Fungsi helper untuk mengurutkan nama secara Ascending dengan pointer (untuk keperluan Binary Search)
void sortNamaASC(roti* arr, int n) {
    for (roti* i = arr; i < arr + n - 1; i++) {
        for (roti* j = arr; j < arr + n - 1 - (i - arr); j++) {
            if (bandingkanNama(j->nama, (j + 1)->nama) > 0) {
                roti temp = *j;
                *j = *(j + 1);
                *(j + 1) = temp;
            }
        }
    }
}

void inputroti() {
    FILE *fp;
    fp = fopen("roti.txt", "a");
    if (fp == NULL) {
        cout << "\n[Eror] Gagal membuka file." << endl;
        return;
    }
	
    cout << "Masukkan jumlah data roti : "; cin >> r;
	
    roti* p = dataroti; // Menggunakan akses pointer ke struct
    for (int i = 0; i < r ; i++, p++) {
        cout << "\nID roti : "; cin >> p->id;
        cout << "Nama Roti : "; cin >> p->nama;
        cout << "Harga Roti : "; cin >> p->harga;
        cout << "Stok Roti : "; cin >> p->stok;
			
        fprintf(fp, "%d %s %.2f %d\n", p->id, p->nama, p->harga, p->stok);
    }
    fclose(fp);
    cout << "\nData berhasil disimpan ke file." << endl;
}
	
void sortingBubleASC() {
    FILE *fp;
    fp = fopen("roti.txt", "r");
	
    if (fp == NULL) {
        cout << "\n[Eror] file roti.txt tidak ditemukan." << endl;
        return;
    }
    r = 0;
    roti* p = dataroti;
	
    while (fscanf(fp, "%d %s %f %d\n", &p->id, p->nama, &p->harga, &p->stok) != EOF) {
        r++;
        p++;
    }
    fclose(fp);
    
    // Bubble Sort berdasarkan Harga Terendah menggunakan pointer
    for (roti* i = dataroti; i < dataroti + r - 1; i++) {
        for (roti* j = dataroti; j < dataroti + r - 1 - (i - dataroti); j++) {
            if (j->harga > (j + 1)->harga) {
                roti temp = *j;
                *j = *(j + 1);
                *(j + 1) = temp;
            }
        }
    }
    
    cout << "\n=====================================================\n";
    cout << "   ID\t\tNAMA\t\tHARGA\t\tSTOK\n";
    cout << "=====================================================\n";

    for (roti* i = dataroti; i < dataroti + r; i++) {
        cout << "   " << i->id << "\t\t" << i->nama << "\t" << i->harga << "\t\t" << i->stok << endl;
    }
}

void quickDESC(int awal, int akhir) {
    int i = awal;
    int j = akhir;
    float pivot = (dataroti + (awal + akhir) / 2)->harga; // Akses basis alamat pointer
    roti temp;

    while (i <= j) {
        while ((dataroti + i)->harga > pivot) {
            i++;
        }
        while ((dataroti + j)->harga < pivot) {
            j--;
        }
        if (i <= j) {
            roti* pi = dataroti + i;
            roti* pj = dataroti + j;
            temp = *pi;
            *pi = *pj;
            *pj = temp;
            i++;
            j--;
        }
    }

    if (awal < j) quickDESC(awal, j);
    if (i < akhir) quickDESC(i, akhir);
}

void sortingQuickDESC() {
    FILE *fp;
    fp = fopen("roti.txt", "r");
	
    if (fp == NULL) {
        cout << "\n[Eror] file roti.txt tidak ditemukan." << endl;
        return;
    }
    r = 0;
    roti* p = dataroti;
	
    while (fscanf(fp, "%d %s %f %d", &p->id, p->nama, &p->harga, &p->stok) != EOF) {
        r++;
        p++;
    }
    fclose(fp);    
    quickDESC(0, r - 1);
    
    cout << "\n=====================================================\n";
    cout << "   ID\t\tNAMA\t\tHARGA\t\tSTOK\n";
    cout << "=====================================================\n";

    for (roti* i = dataroti; i < dataroti + r; i++) {
        cout << "   " << i->id << "\t\t" << i->nama << "\t" << i->harga << "\t\t" << i->stok << endl;
    }
}

int hitungData() {
    FILE *fp;
    fp = fopen("roti.txt", "r");

    if (fp == NULL) {
        return 0;
    }

    int jumlah = 0;
    roti* p = dataroti;

    while (fscanf(fp, "%d %s %f %d\n", &p->id, p->nama, &p->harga, &p->stok) != EOF) {
        jumlah++;
        p++;
    }

    fclose(fp);
    return jumlah;
}

void editmenu() {
    FILE *fp;
    fp = fopen("roti.txt", "r");
	
    if (fp == NULL) {
        cout << "\n[Eror] file roti.txt tidak ditemukan." << endl;
        return;
    }
    r = 0;
    roti* p = dataroti;
    
    while (fscanf(fp, "%d %s %f %d", &p->id, p->nama, &p->harga, &p->stok) != EOF) {
        r++;
        p++;
    }
    fclose(fp);
    
    int edit;
    cout << "\nMasukkan ID roti yang mau di edit : "; cin >> edit;
    
    bool ketemu = false;
    
    for (roti* i = dataroti; i < dataroti + r; i++) {
        if (i->id == edit) {
            ketemu = true;
            cout << "Data ditemukan" << endl;
            cout << "=========================" << endl;
            cout << "        Data Lama        " << endl;
            cout << "=========================" << endl;
            cout << "Nama Roti  : " << i->nama << endl;
            cout << "Harga Roti : " << i->harga << endl;
            cout << "Stok Roti  : " << i->stok << endl;
			
            cout << "=========================" << endl;
            cout << "        Data Baru        " << endl;
            cout << "=========================" << endl;
            cout << "Nama Roti  : "; cin >> i->nama;
            cout << "Harga Roti : "; cin >> i->harga;
            cout << "Stok Roti  : "; cin >> i->stok;
            break;
        }
    }
    if (!ketemu) {
        cout << "\nID roti tidak ditemukan!\n";
        return;
    }
    
    fp = fopen("roti.txt", "w");
    for (roti* i = dataroti; i < dataroti + r; i++) {
        fprintf(fp, "%d %s %.2f %d\n", i->id, i->nama, i->harga, i->stok);
    }
    fclose(fp);
    cout << "Data roti berhasil diperbarui." << endl;
}

void sequential() {
    FILE *fp;
    bool found = false;
    int jumlahdata = hitungData();
    char cariroti[20];
	
    cout << "Masukkan nama roti yang dicari : "; cin >> cariroti;
	
    fp = fopen("roti.txt", "r");
	
    if (fp == NULL) {
        cout << "\n[Eror] file roti.txt tidak ditemukan." << endl;
        return;
    }
    
    r = 0;
    roti* p = dataroti;
    while (fscanf(fp, "%d %s %f %d", &p->id, p->nama, &p->harga, &p->stok) != EOF) {
		
        int idx = 0;
        bool sama = true;
		
        while (p->nama[idx] != '\0' || cariroti[idx] != '\0') {
            if (p->nama[idx] != cariroti[idx]) {
                sama = false;
                break;
            }
            idx++;
        }

        if (sama) {
            cout << "\nJumlah data roti : " << jumlahdata;
            cout << "\nRoti ditemukan\n";
            cout << "Nama   : " << p->nama << endl;
            cout << "Harga  : " << p->harga << endl;
            cout << "Stok   : " << p->stok << endl;

            found = true;
            break;
        }
        r++;
        p++;
    }
		
    if (!found) cout << "Data tidak ditemukan\n";
    fclose(fp);
}
	
void binary() {
    FILE *fp;
    bool found = false;
    int jumlahdata = hitungData();
    char cariroti[20];

    cout << "Masukkan nama roti yang dicari : "; cin >> cariroti;

    fp = fopen("roti.txt", "r");
    if (fp == NULL) {
        cout << "\nError: file roti.txt tidak ditemukan\n";
        return;
    }

    r = 0;
    roti* p = dataroti;
    while (fscanf(fp, "%d %s %f %d", &p->id, p->nama, &p->harga, &p->stok) != EOF) {
        r++;
        p++;
    }
    fclose(fp);

    sortNamaASC(dataroti, r);

    int kiri = 0;
    int kanan = r - 1;

    while (kiri <= kanan) {
        int tengah = (kiri + kanan) / 2;
        roti* ptengah = dataroti + tengah;

        int hasilBanding = bandingkanNama(cariroti, ptengah->nama);

        if (hasilBanding == 0) {
            found = true;
            cout << "\nJumlah data roti : " << jumlahdata << endl;
            cout << "Roti ditemukan (Hasil Terurut Binary)\n";
            cout << "Nama   : " << ptengah->nama << endl;
            cout << "Harga  : " << ptengah->harga << endl;
            cout << "Stok   : " << ptengah->stok << endl;
            break;
        }
        else if (hasilBanding > 0) {
            kiri = tengah + 1;
        }
        else {
            kanan = tengah - 1;
        }
    }

    if (!found) {
        cout << "Data tidak ditemukan\n";
    }
}

void beliroti() {
    FILE *fp;
    fp = fopen("roti.txt", "r");

    if (fp == NULL) {
        cout << "File tidak ditemukan\n";
        return;
    }

    r = 0;
    roti* p = dataroti;
    while (fscanf(fp, "%d %s %f %d", &p->id, p->nama, &p->harga, &p->stok) != EOF) {
        r++;
        p++;
    }
    fclose(fp);

    int idcari;
    int jumlah_beli;
    bool found = false;

    cout << "Masukkan ID roti yang ingin dibeli : "; cin >> idcari;

    for (roti* i = dataroti; i < dataroti + r; i++) {
        if (i->id == idcari) {
            cout << "Masukkan jumlah beli : "; cin >> jumlah_beli;

            if (jumlah_beli <= i->stok) {
                i->stok -= jumlah_beli;

                int k = 0;
                while (i->nama[k] != '\0') {
                    nama_invoice[k] = i->nama[k];
                    k++;
                }
                nama_invoice[k] = '\0';

                harga_invoice = i->harga;
                jumlah_invoice = jumlah_beli;
                total_invoice = harga_invoice * jumlah_invoice;

                cout << "\nPembelian berhasil! Silakan pilih menu Invoice untuk mencetak struk\n";
                found = true;
                break;
            }
            else {
                cout << "Stok tidak cukup\n";
                return;
            }
        }
    }

    if (!found) {
        cout << "ID roti tidak ditemukan\n";
        return;
    }

    fp = fopen("roti.txt", "w");
    for (roti* i = dataroti; i < dataroti + r; i++) {
        fprintf(fp, "%d %s %.2f %d\n", i->id, i->nama, i->harga, i->stok);
    }
    fclose(fp);
}

void invoice() {
    if (jumlah_invoice == 0) {
        cout << "Belum ada transaksi pembelian\n";
        return;
    }
	
    cout << "\n====== STRUK PEMBELIAN ======\n";
    cout << "Nama Roti : " << nama_invoice << endl;
    cout << "Harga     : " << harga_invoice << endl;
    cout << "Jumlah    : " << jumlah_invoice << endl;
    cout << "Total     : " << total_invoice << endl;
    cout << "=============================\n";
}

int main() {
    int pilihan;
	
    do {
        cout << "=======================================" << endl;
        cout << "||     WELCOME TO WARM LOAF BAKERY    ||" << endl;
        cout << "=======================================" << endl;
        cout << "||" << "1. Masuk sebagai karyawan" << endl;
        cout << "||" << "2. Masuk sebagai pembeli" << endl;
        cout << "||" << "3. Keluar Aplikasi" << endl; // Ditambahkan opsi keluar agar loop do-while aman
        cout << "=======================================" << endl;
        cout << "||" << "Pilihan  : "; cin >> pilihan; 
	
        if (pilihan == 1) {
            string Usn;
            int Pass;
            string UsnBenar = "dito";
            int PassBenar = 123;
		
            cout << "\n=======================================" << endl;
            cout << "||           Halo Karyawan!          ||" << endl;
            cout << "||  Silahkan login untuk melanjutkan ||" << endl;
            cout << "=======================================" << endl;
		
            cout << "Masukkan Username : "; cin >> Usn;
            cout << "Masukkan Password : "; cin >> Pass;
		
            bool LoginBerhasil = (Usn == UsnBenar && Pass == PassBenar);
		
            if (LoginBerhasil) {
                int pilihKaryawan;
                do {
                    cout << "\n=======================================" << endl;
                    cout << "||             WELCOME BAKER!        ||" << endl;
                    cout << "=======================================" << endl;
                    cout << "||" << "1. Tambah menu roti" << endl;
                    cout << "||" << "2. Lihat menu roti" << endl;
                    cout << "||" << "3. Edit menu  roti" << endl;
                    cout << "||" << "4. Logout" << endl;
                    cout << "=======================================" << endl;
                    cout << "||" << "Pilihan  : "; cin >> pilihKaryawan; 
		
                    if (pilihKaryawan == 1) {
                        inputroti();	
                        char ngga;
                        cout << "Apakah anda ingin melanjutkan program? (y/n) : "; cin >> ngga;
	
                        if (ngga == 'n' || ngga == 'N') {
                            pilihKaryawan = 4;
                        }
                    } else if (pilihKaryawan == 2) {
                        int asc;
                        int jumlah = hitungData();
                        cout << "\nJumlah data roti: " << jumlah << endl;
                        cout << "Pilih Metode Lihat:" << endl;
                        cout << "1. Ascending" << endl;
                        cout << "2. Descending" << endl;
                        cout << "Masukkan metode : "; cin >> asc;
                        if (asc == 1) {
                            sortingBubleASC();
                        } else if (asc == 2) {
                            sortingQuickDESC();	
                        }
                        system("pause");
                    } else if (pilihKaryawan == 3) {
                        editmenu();
                        system("pause");	
                    } else if (pilihKaryawan == 4) {
                        cout << "Terimakasih Baker, Selamat Beristirahat!" << endl;
                        system("pause");
                    }
                } while (pilihKaryawan != 4);
            } else {
                cout << "\nusername dan password salah!\n";
            }
        } else if (pilihan == 2) {
            int pilihPelanggan;
            do {
                cout << "\n=======================================" << endl;
                cout << "||           MENU PELANGGAN          ||" << endl;
                cout << "=======================================" << endl;
                cout << "||" << "1. Cari roti" << endl;
                cout << "||" << "2. Beli roti" << endl;
                cout << "||" << "3. Invoice  roti" << endl;
                cout << "||" << "4. Logout" << endl;
                cout << "=======================================" << endl;
                cout << "||" << "Pilihan  : "; cin >> pilihPelanggan;
			
                if (pilihPelanggan == 1) {
                    int sequ;
                    cout << "Pilih Metode Cari:" << endl;
                    cout << "1. Sequential" << endl;
                    cout << "2. Binary" << endl;
                    cout << "Masukkan metode : "; cin >> sequ;
				
                    if (sequ == 1) {
                        sequential();
                    } else if (sequ == 2) {
                        binary();
                    }
                    char ngga;
                    cout << "Kembali ke menu? (y/n) : "; cin >> ngga;
	
                    if (ngga == 'n' || ngga == 'N') {
                        pilihPelanggan = 4;
                    }
                } else if (pilihPelanggan == 2) {
                    int asc;
                    int jumlah = hitungData();
                    cout << "\nJumlah data roti: " << jumlah << endl;
                    cout << "Pilih Metode Lihat Terlebih Dahulu:" << endl;
                    cout << "1. Ascending" << endl;
                    cout << "2. Descending" << endl;
                    cout << "Masukkan metode : "; cin >> asc;
                    if (asc == 1) {
                        sortingBubleASC();
                    } else if (asc == 2) {
                        sortingQuickDESC();	
                    }
                    system("pause");
                    beliroti();
                    char ngga;
                    cout << "Kembali ke menu? (y/n) : "; cin >> ngga;
	
                    if (ngga == 'n' || ngga == 'N') {
                        pilihPelanggan = 4;
                    }
                } else if (pilihPelanggan == 3) {
                    invoice();
                    char ngga;
                    cout << "Kembali ke menu? (y/n) : "; cin >> ngga;
	
                    if (ngga == 'n' || ngga == 'N') {
                        pilihPelanggan = 4;
                    }
                } else if (pilihPelanggan == 4) {
                    cout << "\nTerimakasih telah berbelanja disini! Semoga harimu menyenangkan!" << endl;
                    system("pause");
                }
            } while (pilihPelanggan != 4);
        } else if (pilihan == 3) {
            cout << "Keluar dari program Warm Loaf Bakery." << endl;
        } else {
            system("cls");
        }
    } while (pilihan != 3);
    return 0;
}
