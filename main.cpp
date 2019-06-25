#include <iostream>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
using namespace std;

struct dataBarang {
    string barang[100];
    string supplier[100];
    int jumlah[100];
    int harga_jual[100];
    int harga_beli[100];
    int untung[100];
    string kode[100];
}dataBarang;

struct keuntungan {
    long untung[12];
}keuntungan;

struct beli {
    string pbl[10000];
}beli;

struct pjl {
    string kode[1000];
    int banyak[1000];
}pjl;

string pembeliGlobal;

//untuk getch()
/* reads from keypress, doesn't echo */
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

/* reads from keypress, echoes */
int getche(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

//prototype fungsi
void loadData();
void welcome();
void menu();
void lihatdata();
void exit();
void tambahdata();
void baru();
void simpan();
void penjualan();
void struk(string namaBarang[100], int hargaBarang[100], int total, int banyakBarangDalamKeranjang, int bayar, int itemKeranjang);
void untung();
void sortir();
void namaBarang();
void namaPembeli();
void namaSupplier();
void tanggalTransaksi();
void caridata();
void laporan();
void lap_penjualan();
void lap_keuangan();


void lap_penjualan() {
    awal:
    system("clear");
    cout << "************************************************************" << endl;
        cout << "                    LAPORAN PENJUALAN" << endl;
        cout << endl;
        int banyakdatapenjualan;
        int i=0;

        while(pjl.kode[i] != "") {
            banyakdatapenjualan++;
            i++;
        }

        //banyak data barang
        int banyakdatabarang = 0;
        int j=0;
        while(dataBarang.barang[j] != "") {
            banyakdatabarang++;
            j++;
        }

        for(int i=0; i<banyakdatapenjualan; i++) {
            for(int j=0; j<banyakdatabarang; j++) {
                if(pjl.kode[i] == dataBarang.kode[i]) {
                    int angka = 1;
                    cout << "[" << angka << "]. "<< pjl.kode[i] << " --- " << dataBarang.barang[j] << " --- banyak : " << pjl.banyak[i] << " --- stok : " << dataBarang.jumlah[j] << endl; 
                    angka++;
                }
            }
        }
        cout << endl << endl;
        cout << "************************************************************" << endl;
        cout << "Anda Ingin Ke Menu [y/n] : ";
        char m;
        cin >> m;

        if(m == 'y') {
            system("clear");
            menu();
        } else {
            system("clear");
            exit();
        }
}

void lap_keuangan() {
    system("clear");
    string bulan[12] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November","Desember"};
        int pilih;
        cout << "Anda Ingin Melihat Laba Bulan : ";
        cin >> pilih;
        system("clear");
        cout << "************************************************************" << endl;
        cout << "                       LAPORAN KEUANGAN" << endl << endl;
        cout << "                     Bulan   : " << pilih << "(";

        for(int i=0; i<12; i++) {
            if(pilih-1 == i) {
                cout << bulan[i];
            }
        }

        cout << ")";
        cout << endl;

        cout << endl;
        cout << "                  LABA       : Rp. " << keuntungan.untung[pilih-1] << endl;
        cout << endl;
        cout << "************************************************************" << endl;
        cout << "Anda Ingin Ke Menu [y/n] : ";
        char m;
        cin >> m;

        if(m == 'y') {
            system("clear");
            menu();
        } else {
            system("clear");
            exit();
        }
}

void laporan() {
    cout << "======================== LAPORAN ===========================" << endl;
    cout << endl << endl;
    cout << "[1]. LAPORAN PENJUALAN      ||  [3]. LAPORAN STOCK BARANG" << endl;
    cout << "[2]. LAPORAN KEUANGAN       ||  [4]. RIWAYAT PEMBELI" << endl;
    cout << endl;
    int pilih;
    cout << "Pilihan  : "; cin >> pilih;

    switch(pilih) {
        case 1:
        lap_penjualan();
        break;

        case 2:
        lap_keuangan();
        break;

        case 3:
        cout << "ok1" << endl;
        lihatdata();
        break;

        case 4:
        cout << "ok2" << endl;
        namaPembeli();
        break;
    }
}

void caridata() {
	system("clear");
    cout << "============================================================" << endl;
    cout << "                        CARI DATA";
    cout << endl;
    cout << endl;

    string kode;

    cout << "Masukkan kode   : ";
    cin >> kode;

    cout << "============================================================" << endl;
    cout << endl;
    cout << endl;

    //jumlah;;
    int jumlah = 0;
    while(dataBarang.barang[jumlah] != "") {
        jumlah++;
    }

    bool temu = true;

    for(int i=0; i<jumlah; i++) {
        if(dataBarang.kode[i] == kode) {
        cout << "                     DATA DITEMUKAN";
        cout << endl;
        cout << endl;

        cout << dataBarang.kode[i] << "      " << dataBarang.barang[i] << "       " << "Rp. " << dataBarang.harga_jual[i];
        cout << endl;
        goto lanjut;
        }
        else {
        temu = false;
        }
    }

    if(temu == false) {
        cout << "                  DATA TIDAK DITEMUKAN";
        cout << endl;
    }

        lanjut:
        cout << endl;

        char a;
        cout << "Ingin kembali ke menu [y/n] : ";
        cin >> a;
        if(a == 'y' | a == 'Y') {
        menu();
        }
}

void namaPembeli() {
    awal:
    system("clear");
    cout << "===============================NAMA PEMBELI===================================" << endl;
    cout << endl;
    cout << endl;

    // banyak data
    int banyakdata = 0;
    int i = 0;
    while(beli.pbl[i] != "") {
        banyakdata++;
        i++;
    }

    string *pbl = new string[banyakdata];

    for(int i=0; i<banyakdata; i++) {
        pbl[i] = beli.pbl[i];
    }


    //bubble sort
    for(int i=0; i<banyakdata-1; i++) {
        for(int j=i+1; j<banyakdata; j++) {
            if(pbl[i] > pbl[j]) {
                string tampung;

                tampung = pbl[i];
                pbl[i] = pbl[j];
                pbl[j] = tampung;
            }
        }
    }

    for(int i=0; i<banyakdata; i++) {
        cout << "[" << i+1 << "]. " << pbl[i] << endl;
    }

    cout << endl << endl;

    cout << "Anda Ingin Ke Menu [y/n] : ";
    char m;
    cin >> m;

    if(m == 'y') {
        system("clear");
        menu();
    } else {
        system("clear");
        exit();
    }

}

void namaBarang() {
    // banyak data
    int banyakdata = 0;
    int i = 0;
    while(dataBarang.barang[i] != "") {
        banyakdata++;
        i++;
    }

    string barang[banyakdata];
    int harga[banyakdata];
    string supplier[banyakdata];

    for(int i=0; i<banyakdata; i++) {
        barang[i] = dataBarang.barang[i];
        harga[i] = dataBarang.harga_jual[i];
        supplier[i] = dataBarang.supplier[i];
    }

    //bubble

    for(int i=0; i<banyakdata - 1; i++) {
        for(int j=i+1; j<banyakdata; j++) {
            if(barang[i] > barang[j]) {
                string tampung;

                tampung = barang[i];
                barang[i] = barang[j];
                barang[j] = tampung;
            }
        }
    }

    for(int i=0; i<banyakdata; i++) {
        cout << "[" << (i+1) << "]. " << barang[i] << endl;
        cout << "    " << "Harga   : Rp. " << harga[i] << endl;
        cout << "    " << "Supplier: " << supplier[i] << endl;
    }

    cout << endl;

    cout << "Anda Ingin Ke Menu [y/n] : ";
    char m;
    cin >> m;

    if(m == 'y') {
        system("clear");
        menu();
    } else {
        system("clear");
        exit();
    }
}

void namaSupplier() {
    // banyak data
    int banyakdata = 0;
    int i = 0;
    while(dataBarang.barang[i] != "") {
        banyakdata++;
        i++;
    }

    string barang[banyakdata];
    int harga[banyakdata];
    string supplier[banyakdata];

    for(int i=0; i<banyakdata; i++) {
        barang[i] = dataBarang.barang[i];
        harga[i] = dataBarang.harga_jual[i];
        supplier[i] = dataBarang.supplier[i];
    }

    //bubble

    for(int i=0; i<banyakdata - 1; i++) {
        for(int j=i+1; j<banyakdata; j++) {
            if(supplier[i] > supplier[j]) {
                string tampung;

                tampung = supplier[i];
                supplier[i] = supplier[j];
                supplier[j] = tampung;
            }
        }
    }

    for(int i=0; i<banyakdata; i++) {
        cout << "[" << (i+1) << "]. " << barang[i] << endl;
        cout << "    " << "Harga   : Rp. " << harga[i] << endl;
        cout << "    " << "Supplier: " << supplier[i] << endl;
    }

    cout << endl;

    cout << "Anda Ingin Ke Menu [y/n] : ";
    char m;
    cin >> m;

    if(m == 'y') {
        system("clear");
        menu();
    } else {
        system("clear");
        exit();
    }
}

void sortir() {
    awal:

    system("clear");
    cout << "================================SORTIR===================================";
    cout << endl << endl << endl;

    cout << " [1]. Berdasarkan Nama Barang   ||   [3]. Berdasarkan Nama Supplier";
    cout << endl;
    cout << " [2]. Berdasarkan Nama Pembeli  ||   [4]. Berdasarkan Tanggal Transaksi";
    cout << endl;
    cout << endl;

    int pil;

    cout << "Pilih : ";
    cin >> pil;

    switch(pil) {
        case 1:
        namaBarang();
        break;

        case 2:
        namaPembeli();
        break;

        case 3:
        namaSupplier();
        break;

        case 4:
        //tanggalTransaksi();
        break;

        default:
        cout << "Salah Input !" << endl;
    }
}

void untung() {
    for(int i=0; i<12; i++) {
        cout << keuntungan.untung[i] << endl;
    }
}

// penjualan

void penjualan() {
    system("clear");
    struct keranjang {
        string namaBarang[100];
        string kode[100];
        int harga[100];
        int jumlah[100];
    }keranjang;

    cout << "========================================================";
    cout << endl;
    cout << endl;
    cout << "Nama Pembeli    : ";
    string pembeli;
    cin >> pembeli;

    int indeks = 0;
    beli:
    cout << "Kode Barang     : ";
    cin >> keranjang.kode[indeks];
    cout << "Jumlah Item     : ";
    cin >> keranjang.jumlah[indeks];
    cout << endl;
    indeks++;
    char y;
    cout << "Ulang [y/n]     : ";
    cin >> y;

    cout << endl;

    if(y == 'y') {
        goto beli;
    }

    int itemKeranjang = indeks;

    //banyak barang
    int banyakBarangDalamKeranjang = 0;

    for(int i=0; i<itemKeranjang; i++) {
        banyakBarangDalamKeranjang += keranjang.jumlah[i];
    }

    system("clear");

    cout << "========================================================" << endl << endl;


    cout << "Banyak Jenis    : " << itemKeranjang << " jenis" << endl;
    cout << "Banyak Barang   : " << banyakBarangDalamKeranjang << " buah" << endl;

    cout << "========================================================" << endl << endl;

    // banyak data
    int banyakdata = 0;
    int i = 0;
    while(dataBarang.barang[i] != "") {
        banyakdata++;
        i++;
    }

    int total = 0;

    string namaBarang[100];
    int hargaBarang[100];

    for(int i=0; i<indeks; i++) {
        for(int j=0; j<banyakdata; j++) {
            if(keranjang.kode[i] == dataBarang.kode[j]) {
                cout << dataBarang.barang[j] << "   " << " -----   Rp." << dataBarang.harga_jual[j] << " ----- " << keranjang.jumlah[i] << " pcs" << " ----- " << dataBarang.harga_jual[j] * keranjang.jumlah[i] << endl;
                total += (dataBarang.harga_jual[j] * keranjang.jumlah[i]);

                //copy array
                namaBarang[i] = dataBarang.barang[j];
                hargaBarang[i] = dataBarang.harga_beli[j];
            }
        }
    }

    cout << "========================================================" << endl;
    cout << "   " << endl;

    cout << "Total          : Rp." << total << endl;

    cout << endl;
    char proses;
    cout << "Proses   [y/n] : ";
    cin >> proses;

    if(proses == 'y') {
        system("clear");
        cout << "========================================================" << endl;
        cout << "                         KONFIRMASI";
        cout << endl;
        cout << endl;
        cout << "Nama Pembeli        : " << pembeli << endl;
        cout << "Total Pembelian     : Rp. " << total << endl;
        cout << "Bayar               : Rp. ";
        int bayar;
        cin >> bayar;
        cout << endl;
        cout << endl;
        cout << "Kembalian           : Rp. " << bayar - total;
        cout << endl;

        cout << "Lanjut Cetak Struk  : ";
        char cetak;
        cin >> cetak;

        if(cetak == 'y') {

            //banyak pembeli
            int banyakpembeli;
            int k=0;
            while(beli.pbl[k] != "") {
                k++;
                banyakpembeli++;
            }
            //update data pembeli
            beli.pbl[banyakpembeli] = pembeli;

            ofstream input7;
            input7.open("db_pembeli.txt");

            input7 << beli.pbl[0];
            for(int i=1; i<=banyakpembeli; i++) {
                input7 << endl << beli.pbl[i];
            }

            input7.close();

            //update data
            for(int i=0; i<indeks; i++) {
                for(int j=0; j<banyakdata; j++) {
                    if(keranjang.kode[i] == dataBarang.kode[j]) {
                        dataBarang.jumlah[j] -= keranjang.jumlah[i];
                    }
                }
            }

            //stok
            ofstream input5;
            input5.open("db_stok.txt");
            input5 << dataBarang.jumlah[0];
            for(int i=1; i<banyakdata; i++) {
                input5 << endl << dataBarang.jumlah[i];
            }
            input5.close();

            //keuntungan laba
            int untung;
            for(int i=0; i<indeks; i++) {
                for(int j=0; j<banyakdata; j++) {
                    if(keranjang.kode[i] == dataBarang.kode[j]) {
                        untung += (dataBarang.harga_jual[j] - dataBarang.harga_beli[j]) * keranjang.jumlah[i];
                    }
                }
            }

            time_t now = time(0);
            tm *ltm = localtime(&now);
            int bulan = ltm->tm_mon;

            keuntungan.untung[bulan] += untung;

            //tulis data keuntungan ke db_untung.txt
            ofstream write6;

            write6.open("db_untung.txt");
            write6 << keuntungan.untung[0];

            for(int i=1; i<12; i++) {
                write6 << endl << keuntungan.untung[i];
            }

            write6.close();

            int pbl = 0;
            int j = 0;
            while(dataBarang.barang[j] != "") {
                pbl++;
                j++;
            }


            loadData();

            struk(namaBarang, hargaBarang, total, banyakBarangDalamKeranjang, bayar, itemKeranjang);

        } else {
            cout << "Anda Ingin Ke Menu [y/n] : ";
            char m;
            cin >> m;

            if(m == 'y') {
                system("clear");
                menu();
            } else {
                system("clear");
                exit();
            }
        }

    } else {
        cout << "Anda Ingin Ke Menu [y/n] : ";
        char m;
        cin >> m;

        if(m == 'y') {
            system("clear");
            menu();
        } else {
            system("clear");
            exit();
        }
    }

}

void struk(string namaBarang[100], int hargaBarang[100], int total, int banyakBarangDalamKeranjang, int bayar, int itemKeranjang) {

    system("clear");
    cout << "                        RETAIL";

    cout << endl;

    cout << "                   OBLONG VAN JOGJA";

    cout << endl;

    cout << "           Jl. Malioboro No. 149 Yogyakarta";
    cout << endl;
    cout << "                  Telp. (0274)582582";
    cout << endl;
    cout << endl;

    cout << "Faktur Penjualan";
    cout << endl;
    cout << "Tanggal   : ";
    cout << endl;
    cout << "Pelanggan : " << "Umum";
    cout << endl;
    cout << "==========================================================";
    cout << endl;

    for(int i=0; i<itemKeranjang; i++) {
        cout << namaBarang[i];
        cout << endl;
        cout << "                             Rp. " << hargaBarang[i];
        cout << endl;
    }

    cout << endl;
    cout << endl;


    time_t now = time(0);
    tm *ltm = localtime(&now);

    cout << "==========================================================";
    cout << endl;
    cout << "Item : " << banyakBarangDalamKeranjang;
    cout << endl;
    cout << "                    Total     Rp. " << total;
    cout << endl;
    cout << "                    Bayar     Rp. " << bayar;
    cout << endl;
    cout << "                   Kembalian  Rp. " << (bayar-total);
    cout << endl;
    cout << "==========================================================";
    cout << endl;
    cout << "                     TERIMA KASIH";
    cout << endl;

    cin.get();

    for(int i=0; i<3; i++) {
        cout << endl;
    }

    cout << "Anda Ingin Ke Menu [y/n] : ";
    char m;
    cin >> m;

    if(m == 'y') {
        system("clear");
        menu();
    } else {
        system("clear");
        exit();
    }

}

void simpan() {

    // banyak data
    int banyakdata = 0;
    int i = 0;
    while(dataBarang.barang[i] != "") {
        banyakdata++;
        i++;
    }

                ofstream input1;
                ofstream input2;
                ofstream input3;
                ofstream input4;
                ofstream input5;

                //nama barang
                input1.open("db_barang.txt");
                input1 << dataBarang.barang[0];
                for(int i=1; i<banyakdata; i++) {
                    input1 << endl << dataBarang.barang[i];
                }
                input1.close();

                //harga
                input2.open("db_harga.txt");
                input2 << dataBarang.harga_beli[0];
                input2 << "     ";
                input2 << dataBarang.harga_jual[0];
                for(int i=1; i<banyakdata; i++) {
                    input2 << endl << dataBarang.harga_beli[i];
                    input2 << "     ";
                    input2 << dataBarang.harga_jual[i];
                }
                input2.close();

                //kode barang
                input3.open("db_kode.txt");
                input3 << dataBarang.kode[0];
                for(int i=1; i<banyakdata; i++) {
                    input3 << endl << dataBarang.kode[i];
                }
                input3.close();

                //supplier
                input4.open("db_supplier.txt");
                input4 << dataBarang.supplier[0];
                for(int i=1; i<banyakdata; i++) {
                    input4 << endl << dataBarang.supplier[i];
                }
                input4.close();

                //stok
                input5.open("db_stok.txt");
                input5 << dataBarang.jumlah[0];
                for(int i=1; i<banyakdata; i++) {
                    input5 << endl << dataBarang.jumlah[i];
                }
                input5.close();

                //keuntungan

                loadData();
}

void baru() {
    // banyak data
    int banyakdata = 0;
    int i = 0;
    while(dataBarang.barang[i] != "") {
        banyakdata++;
        i++;
    }

    cout << "========================================================";
    cout << endl;
    cout << endl;

    cout << "Silahkan Masukkan Data : ";
    cout << endl;
    cout << "No Data     : " << 0 << banyakdata+1;
    int bnyk = banyakdata + 1;
    string s_bnyk = to_string(bnyk);
    dataBarang.kode[banyakdata] = "0" + s_bnyk;
    cout << endl;
    cin.ignore();
    cout << "Nama Barang : ";
    getline(cin, dataBarang.barang[banyakdata]);
    cout << "Harga Awal  : ";
    cin >> dataBarang.harga_beli[banyakdata];
    cout << "Harga Jual  : ";
    cin >> dataBarang.harga_jual[banyakdata];
    cout << "Stok Barang : ";
    cin >> dataBarang.jumlah[banyakdata];
    cout << "Supplier    : ";
    cin.ignore();
    cin >> dataBarang.supplier[banyakdata];
    //keuntungan
    dataBarang.untung[banyakdata] = dataBarang.harga_jual[banyakdata] - dataBarang.harga_beli[banyakdata];

    // banyakdata = 0;
    // i = 0;
    // while(dataBarang.barang[i] != "") {
    //     banyakdata++;
    //     i++;
    // }

    // cout << "Banyak Data : " << banyakdata << endl;

    // for(int i=0; i<banyakdata; i++) {
    //     cout << dataBarang.kode[i] << "--" << dataBarang.barang[i] << "--";
    //     cout << "    " << dataBarang.harga_beli[i] << " --- " << dataBarang.harga_jual[i] << endl;
    //     cout << "    " << dataBarang.supplier[i] << endl;
    // }

    string y;
    cout << "Apakah Anda akan menyimpan data tersebut [y/n] : ";
    cin >> y;

    if(y == "y") {
        //lakukan write data ke db
        banyakdata++;

        // for(int i=0; i<banyakdata; i++) {
        //     cout << dataBarang.kode[i] << "--" << dataBarang.barang[i] << "--";
        //     cout << "    " << dataBarang.harga_beli[i] << " --- " << dataBarang.harga_jual[i] << endl;
        //     cout << "    " << dataBarang.supplier[i] << endl;
        // }

        cout << "Banyak Data : " << banyakdata << endl;

        ofstream input1;
        ofstream input2;
        ofstream input3;
        ofstream input4;
        ofstream input5;

        //nama barang
        input1.open("db_barang.txt", ios::app);
        input1 << endl << dataBarang.barang[banyakdata - 1];
        input1.close();

        //harga
        input2.open("db_harga.txt", ios::app);
        input2 << endl << dataBarang.harga_beli[banyakdata - 1];
        input2 << "     ";
        input2 << dataBarang.harga_jual[banyakdata - 1];
        input2.close();

        //kode barang
        input3.open("db_kode.txt", ios::app);
        input3 << endl << dataBarang.kode[banyakdata - 1];
        input3.close();

        //supplier
        input4.open("db_supplier.txt", ios::app);
        input4 << endl << dataBarang.supplier[banyakdata - 1];
        input4.close();

        //stok
        input5.open("db_stok.txt", ios::app);
        input5 << endl << dataBarang.jumlah[banyakdata - 1];
        input5.close();

        loadData();

        cout << "Data Berhasil Ditambahkan";
        cout << endl;
        cout << endl;
        cout << "Anda Ingin Ke Menu [y/n] : ";
        char m;
        cin >> m;

        if(m == 'y') {
            system("clear");
            menu();
        } else {
            system("clear");
            exit();
        }

    } else {
        loadData();
    }


}

void lama() {
    system("clear");
    cout << "========================================================" << endl;
    cout << endl;
    cout << "Masukkan Kode Barang : ";
    string kodeBarang;
    cin >> kodeBarang;

    // banyak data
    int banyakdata = 0;
    int i = 0;
    while(dataBarang.barang[i] != "") {
        banyakdata++;
        i++;
    }

    bool temu = false;
    for(int i=0; i<banyakdata; i++) {
        if(kodeBarang == dataBarang.kode[i]) {
            cout << dataBarang.kode[i] << ". " << dataBarang.barang[i] << endl;
            cout << "   " << "Rp. " << dataBarang.harga_jual[i] << endl;
            cout << "   " << "Stok : " << dataBarang.jumlah[i] << endl;
            cout << endl << endl;

            cout << "             BARANG DITEMUKAN!" << endl;
            temu = true;

            cout << endl;

            cout << "Anda Ingin Ubah Data Dari Barang Ini : ";
            char y;
            cin >> y;

            if(y == 'y') {
                cout << "Nama Barang   : ";
                cin.ignore();
                getline(cin, dataBarang.barang[i]);
                cout << "Harga Awal    : ";
                cin >> dataBarang.harga_beli[i];
                cout << "Harga Jual    : ";
                cin >> dataBarang.harga_jual[i];
                dataBarang.untung[i] = dataBarang.harga_jual[i] - dataBarang.harga_beli[i];
                cout << "Stok Barang   : ";
                cin >> dataBarang.jumlah[i];
                cout << "Supplier      : ";
                cin.ignore();
                getline(cin, dataBarang.supplier[i]);

                cout << "Data Telah Dibuah" << endl;


            }

        }
    }

    simpan();


    if(temu == false) {
        cout << "Maaf Barang Tidak Ditemukan" << endl;
        cout << endl << endl;
    }

     cout << "Anda Ingin Ke Menu [y/n] : ";
        char m;
        cin >> m;

        if(m == 'y') {
            system("clear");
            menu();
        } else {
            system("clear");
            exit();
        }


}

void tambahdata() {
    awal:
    system("clear");
    cout << "========================================================" << endl;
    cout << endl;
    cout << "[1]. Tambah Data Baru";
    cout << endl;
    cout << "[2]. Tambah Data Dari Data Yang Sudah Ada";
    cout << endl;
    cout << endl;
    int pil;
    cout << "Pilihan  : ";
    cin >> pil;

    switch(pil) {
        case 1:
        baru();
        break;

        case 2:
        lama();
        break;

        default:
        cout << "Salah Input" << endl;
        goto awal;
    }
}

void lihatdata() {
    cout << "========================================================" << endl;
    int no=1;

    // banyak data
    int banyakdata = 0;
    int i = 0;
    while(dataBarang.barang[i] != "") {
        banyakdata++;
        i++;
    }

    for(int i=0; i<banyakdata; i++, no++) {
        cout << "[" << no << "]. " << dataBarang.barang[i] << endl;
        cout << "    " << "Rp. " << dataBarang.harga_jual[i] << endl;
        cout << "    " << "Stok : " << dataBarang.jumlah[i] << endl;
    }

    cout << endl;
    cout << "========================================================" << endl;
    cout << endl;

    cout << "Kembali Ke Menu [y/n] : ";
    char kbl;
    cin >> kbl;

    if(kbl == 'y') {
        system("clear");
        menu();
    } else {
        system("clear");
        exit();
    }
}

void exit() {
	system("clear");
	cout << "=======================================================" << endl << endl << endl;
    cout << endl;
    cout << "                   ANDA TELAH LOGOUT" << endl;
    cout << endl;
    cout << endl;
}

void loadData() {
    ifstream load1;
    ifstream load2;
    ifstream load3;
    ifstream load4;
    ifstream load5;
    ifstream load6;
    ifstream load7;

    //barang
    load1.open("db_barang.txt", ios::app);
    int i=0;
    string tampungbaju;

    while(!load1.eof()) {
        getline(load1, tampungbaju);
        dataBarang.barang[i] = tampungbaju;
        i++;
    }
    load1.close();

    // banyak data
    int banyakdata = 0;
    i = 0;
    while(dataBarang.barang[i] != "") {
        banyakdata++;
        i++;
    }

    //harga
    load2.open("db_harga.txt", ios::app);
    i=0;
    int harga_awal;
    int harga_akhir;

    while(!load2.eof()) {
        load2 >> harga_awal;
        dataBarang.harga_beli[i] = harga_awal;
        load2 >> harga_akhir;
        dataBarang.harga_jual[i] = harga_akhir;
        i++;
    }
    load2.close();

    //kodebarang
    load3.open("db_kode.txt", ios::app);
    i=0;
    string tampungkode;

    while(!load3.eof()) {
        load3 >> tampungkode;
        dataBarang.kode[i] = tampungkode;
        i++;
    }
    load3.close();

    //supplier
    load4.open("db_supplier.txt", ios::app);
    i=0;
    string tampungsupplier;

    while(!load4.eof()) {
        load4 >> tampungsupplier;
        dataBarang.supplier[i] = tampungsupplier;
        i++;
    }
    load4.close();

    //untung
    for(int i=0; i<banyakdata; i++) {
        dataBarang.untung[i] = dataBarang.harga_jual[i] - dataBarang.harga_beli[i];
    }

    //banyak stok
    load5.open("db_stok.txt", ios::app);
    i=0;
    int tampungstok;

    while(!load5.eof()) {
        load5 >> tampungstok;
        dataBarang.jumlah[i] = tampungstok;
        i++;
    }
    load5.close();

    // laba keuntungan
    load6.open("db_untung.txt", ios::app);
    i=0;
    int tampunguntung;

    while(!load6.eof()) {
        load6 >> tampunguntung;
        keuntungan.untung[i] = tampunguntung;
        i++;
    }
    load6.close();

    // pembeli
    load7.open("db_pembeli.txt", ios::app);
    i=0;
    string tampung;

    while(!load7.eof()) {
        getline(load7, beli.pbl[i]);
        i++;
    }
    load7.close();
}

void welcome() {
    awal:
    string uname, password;
    cout << "=============================================" << endl;
    cout << endl;
    cout << "Username     : ";
    cin >> uname;
    cout << "Password     : ";
    cin >> password;

    if(uname == "admin" && password == "admin") {
        cout << endl;
        cout << endl;

        cout << "            LOGIN BERHASIL";
        cout << endl;
        getch();
        cout << "";
        system("clear");
        menu();

    } else {
        system("clear");
        cout << endl;
        cout << endl;
        cout << "  USERNAME ATAU PASSWORD ANDA SALAH!";
        cout << endl << endl;
        cout << "         SILAHKAN COBA LAGI!";
        cout << endl;
        getchar();
        goto awal;
    }

}

void menu() {
    awal:

    system("clear");
    cout << "=========================MENU==========================";
    cout << endl << endl << endl;

    cout << " [1]. Penjualan           ||   [5]. Lihat Data";
    cout << endl;
    cout << " [2]. Tambah Data         ||   [6]. Laporan Data";
    cout << endl;
    cout << " [3]. Cari Data           ||   [7]. Exit";
    cout << endl;
    cout << " [4]. Sortir Data         ||   " << endl;

    cout << endl << endl << endl;

    int pil;

    cout << "Pilihan : ";
    cin >> pil;

    // Pilihan

    switch(pil) {
        case 1:
        system("clear");
        penjualan();
        break;


        case 2:
        system("clear");
        tambahdata();
        break;


        case 3:
        system("clear");
        caridata();
        break;


        case 4:
        system("clear");
        sortir();
        break;


        case 5:
        system("clear");
        lihatdata();
        break;

        case 6:
        laporan();
        break;

        case 7:
        exit();
        break;

        default:
        cout << "Anda salah input!" << endl;
        cout << "Silahkan coba lagi" << endl;
        cin.get();
        goto awal;
  }
}

main() {
    loadData();
    welcome();
}