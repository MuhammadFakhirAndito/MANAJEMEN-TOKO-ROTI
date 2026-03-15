#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

struct roti{
	char nama [20];
	int id,stok;
	float harga;
	};
	
roti dataroti[100];
int r = 0;

void  inputroti(){
	FILE *fp;
	
	fp = fopen("roti.txt","a");
	
	
	cout << "Masukkan jumlah data roti : "; cin >> r;
	
	for ( int i = 0; i < r ; i++){
		cout << "\nID roti : ";cin >> dataroti[i].id;
		cout << "Nama Roti : ";cin >> dataroti[i].nama;
		cout << "Harga Roti : ";cin >> dataroti[i].harga;
		cout << "Stok Roti : ";cin >> dataroti[i].stok;
			
		fprintf(fp,"%d %s %.2f %d\n",
		dataroti[i].id,
		dataroti[i].nama,
		dataroti[i].harga,
		dataroti[i].stok);
		}
		fclose(fp);
		
		cout << "\nData berhasil disimpan ke file." << endl;
	}
	
void sortingBubleASC(){
	FILE *fp;
	fp = fopen("roti.txt","r");
	
	if(fp == NULL){
        cout << "\n[Eror] file roti.txt tidak ditemukan." << endl;
		return;
    }
	r = 0;
	int i,j;
	
	while(fscanf(fp,"%d %s %f %d\n",
		&dataroti[r].id,
        dataroti[r].nama,
		&dataroti[r].harga,
		&dataroti[r].stok)!=EOF){
		r++;
    }
    
    fclose(fp);
    roti temp;
    
    for (i=0; i<r-1; i++){
		for (j=0; j<r-1-i; j++){
		if (dataroti[j].harga > dataroti[j+1].harga)
			{
			 temp= dataroti[j];
			 dataroti[j]= dataroti[j+1];
			 dataroti[j+1]= temp;
			}
		}
	}
    
    cout << "\n=====================================================\n";
	cout << "   ID\t\tNAMA\t\tHARGA\t\tSTOK\n";
	cout << "=====================================================\n";

	for(int i=0;i<r;i++){
	cout << "   " << dataroti[i].id << "\t\t"
		 << dataroti[i].nama << "\t"
		 << dataroti[i].harga << "\t\t"
		 << dataroti[i].stok << endl;
	}
}

void quickDESC(int awal, int akhir){

    int i = awal;
    int j = akhir;

    float pivot = dataroti[(awal + akhir) / 2].harga;

    roti temp;

    while(i <= j){
        while(dataroti[i].harga > pivot){
            i++;
        }while(dataroti[j].harga < pivot){
            j--;
        }if(i <= j){
            temp = dataroti[i];
            dataroti[i] = dataroti[j];
            dataroti[j] = temp;
            i++;
            j--;
        }
    }

    if(awal < j)
        quickDESC(awal, j);

    if(i < akhir)
        quickDESC(i, akhir);
}

void sortingQuickDESC(){
	FILE *fp;
	fp = fopen("roti.txt","r");
	
	if(fp == NULL){
        cout << "\n[Eror] file roti.txt tidak ditemukan." << endl;
        return;
    }
	r = 0;
	
	while(fscanf(fp,"%d %s %f %d",
		&dataroti[r].id,
        dataroti[r].nama,
		&dataroti[r].harga,
		&dataroti[r].stok)!=EOF){
		r++;
    }
    fclose(fp);    
    quickDESC(0,r-1);
    
    cout << "\n=====================================================\n";
	cout << "   ID\t\tNAMA\t\tHARGA\t\tSTOK\n";
	cout << "=====================================================\n";

	for(int i=0;i<r;i++){
	cout << "   " << dataroti[i].id << "\t\t"
		 << dataroti[i].nama << "\t"
		 << dataroti[i].harga << "\t\t"
		 << dataroti[i].stok << endl;
	}
}

int hitungData(){
    FILE *fp;
    fp = fopen("roti.txt","r");

    if(fp == NULL){
        cout << "\n[Eror] file roti.txt tidak ditemukan." << endl;
    }

    int jumlah = 0;

    while(fscanf(fp,"%d %s %f %d\n",
		&dataroti[jumlah].id,
        dataroti[jumlah].nama,
        &dataroti[jumlah].harga,
        &dataroti[jumlah].stok)!= EOF){
        jumlah++;
    }

    fclose(fp);
    return jumlah;
}

void editmenu(){
	FILE *fp;
	
	fp = fopen ("roti.txt","r");
	
	if(fp == NULL){
        cout << "\n[Eror] file roti.txt tidak ditemukan." << endl;
        return;
    }
    r = 0;
    
    while(fscanf(fp,"%d %s %f %d",
		&dataroti[r].id,
        dataroti[r].nama,
		&dataroti[r].harga,
		&dataroti[r].stok)!=EOF){
		r++;
    }
    
    fclose(fp);
    
    int edit;
    cout << "\nMasukkan ID roti yang mau di edit : ";cin >> edit;
    
    bool ketemu = false;
    
    for (int i = 0; i < r; i++){
		if (dataroti[i].id == edit){
			ketemu = true;
			cout << "Data ditemukan" << endl;
			cout << "=========================" << endl;
			cout << "        Data Lama        " << endl;
			cout << "=========================" << endl;
			cout << "Nama Roti  : " << dataroti[i].nama << endl;
			cout << "Harga Roti : " << dataroti[i].harga << endl;
			cout << "Stok Roti  : " << dataroti[i].stok << endl;
			
			cout << "=========================" << endl;
			cout << "        Data Baru        " << endl;
			cout << "=========================" << endl;
			cout << "Nama Roti  : ";cin >> dataroti[i].nama;
			cout << "Harga Roti : ";cin >> dataroti[i].harga;
			cout << "Stok Roti  : ";cin >> dataroti[i].stok;
		}
	}
		if (!ketemu){
			cout << "\nID roti tidak ditemukan!\n";
			return;
		}
		fp = fopen("roti.txt","w");
		
		for(int i = 0; i < r;i++){
			fprintf(fp,"%d %s %.2f %d\n",
			dataroti[i].id,
			dataroti[i].nama,
			dataroti[i].harga,
			dataroti[i].stok);
		}
		fclose(fp);
		cout << "Data roti berhasil diperbarui." << endl;
}

int main()
{
	int pilihan;
	
	do {
		cout << "=======================================" << endl;
		cout << "||    WELCOME TO WARM LOAF BAKERY    ||" << endl;
		cout << "=======================================" << endl;
		cout << "||" << "1. Masuk sebagai karyawan" << endl;
		cout << "||" << "2. Masuk sebagai pembeli" << endl;
		cout << "=======================================" << endl;
		cout << "||" << "Pilihan  : "; cin >> pilihan; 
	
	
	if(pilihan == 1){
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
		
		if (LoginBerhasil){
		int pilihKaryawan;
			do{
			cout << "\n=======================================" << endl;
			cout << "||           WELCOME BAKER!          ||" << endl;
			cout << "=======================================" << endl;
			cout << "||" << "1. Tambah menu roti" << endl;
			cout << "||" << "2. Lihat menu roti" << endl;
			cout << "||" << "3. Edit menu  roti" << endl;
			cout << "||" << "4. Logout" << endl;
			cout << "=======================================" << endl;
			cout << "||" << "Pilihan  : "; cin >> pilihKaryawan; 
		
			if (pilihKaryawan == 1){
				inputroti();	
				char ngga;
				cout << "Apakah anda ingin melanjutkan program? (y/n) : ";
				cin >> ngga;
	
				if (ngga == 'n' || ngga == 'N'){
				pilihKaryawan = 4;
				}
			}else if (pilihKaryawan == 2){
				int asc;
				
				int jumlah = hitungData();
				cout << "\nJumlah data roti: " << jumlah << endl;
				cout << "Pilih Metode Lihat:" << endl;
				cout << "1. Ascending" << endl;
				cout << "2. Descending" << endl;
				cout << "Masukkan metode : "; cin >> asc;
				if(asc == 1){
				sortingBubleASC();
				}else if (asc == 2){
				sortingQuickDESC();	
				}
				system("pause");
			}else if (pilihKaryawan == 3){
				editmenu();
				system("pause");	
			}else if (pilihKaryawan == 4){
				cout << "Terimakasih Baker, Selamat Beristirahat!" << endl;
				system("pause");
			}
			}while(pilihKaryawan != 4);
		}else{
			cout << "\nusername dan password salah!\n";
		}
	}else if (pilihan ==2){
		
	}else{
		system("cls");
	}
}while (pilihan != 3);
	return 0;
}

