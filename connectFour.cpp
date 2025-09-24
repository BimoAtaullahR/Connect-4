#include <iostream>
#include <utility>
#include <string>
#include <algorithm>
#include <limits>

#define fi first
#define se second
using namespace std;

char kotak[10][10];
string arahConnectFour;
int kolom;
int bawahKolom[10];
string bgColor = "\033[0m", fontColor = "\033[0m", RESET = "\033[0m";
string warna;
pair<string,string> warnaPemain1, warnaPemain2;

pair<string,string> merah = {"\033[41m", "\033[37m"};
pair<string,string> hijau = {"\033[42m", "\033[93m"};
pair<string,string> biru = {"\033[44m", "\033[1m"};
pair<string,string> cyan = {"\033[46m", "\033[1m"};

void inputWarna(){
    //PEMAIN 1
    bool lanjut = true;
    cout << "(Pemain 1) Pilih warna favoritmu (merah/hijau/biru/cyan): ";
    while(lanjut){
        cin >> warna;
        lanjut = false;
        transform(warna.begin(), warna.end(), warna.begin(), [](unsigned char c){return tolower(c);});
        if(warna=="merah"){
            warnaPemain1.fi = merah.fi;
            warnaPemain1.se = merah.se;
        }
        else if(warna=="hijau"){
            warnaPemain1.fi = hijau.fi;
            warnaPemain1.se = hijau.se;
        }
        else if(warna=="biru"){
            warnaPemain1.fi = biru.fi;
            warnaPemain1.se = biru.se;
        }
        else if(warna=="cyan"){
            warnaPemain1.fi = cyan.fi;
            warnaPemain1.se = cyan.se;
        }
        
        else{
          lanjut = true;
          cout << "Input tidak valid, silakan pilih warna yang sesuai (merah/hijau/biru/cyan): ";  
        } 
    }

    //PEMAIN 2
    lanjut = true;
    cout << "(Pemain 2) Pilih warna favoritmu (merah/hijau/biru/cyan): ";
    while(lanjut){
        cin >> warna;
        lanjut = false;
        transform(warna.begin(), warna.end(), warna.begin(), [](unsigned char c){return tolower(c);});
        if(warna=="merah"){
            warnaPemain2.fi = merah.fi;
            warnaPemain2.se = merah.se;
        }
        else if(warna=="hijau"){
            warnaPemain2.fi = hijau.fi;
            warnaPemain2.se = hijau.se;
        }
        else if(warna=="biru"){
            warnaPemain2.fi = biru.fi;
            warnaPemain2.se = biru.se;
        }
        else if(warna=="cyan"){
            warnaPemain2.fi = cyan.fi;
            warnaPemain2.se = cyan.se;
        }
        else{
          lanjut = true;
          cout << "Input tidak valid, silakan pilih warna yang sesuai (merah/hijau/biru/cyan): ";  
        } 
    }
}

void cekInput(){
    while(!(cin>>kolom) || kolom < 1 || kolom > 7 || bawahKolom[kolom+1] > 6){
        if(bawahKolom[kolom+1] > 6) cout <<  "Kolom " << kolom << " sudah penuh, silakan pilih kolom lainnya: ";
        else{
            cout << "Input tidak valid, silakan input sebuah angka (1-7): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

}

bool connect4(int x, int y, char token){
    //CEK HORIZONTAL
    int horizontal = 0;
    for(int i = y; i < 9; i++){
        if(kotak[x][i] != token) break;
        else horizontal++;
    }
    for(int i = y-1; i > 1; i--){
        if(kotak[x][i] != token) break;
        else horizontal++;
    }
    if(horizontal==4){
        arahConnectFour = "Horizontal";
        return true;
    }

    //CEK VERTIKAL
    int vertikal = 0;
    for(int i = x; i < 7; i++){
        if(kotak[i][y] != token) break;
        else vertikal++;
    }
    for(int i = x-1; i > 0; i--){
        if(kotak[i][y] != token) break;
        else vertikal++;
    }
    if(vertikal == 4){
        arahConnectFour = "Vertikal";
        return true;
    }

    int tempX = x, tempY = y;
    //CEK DIAGONAL KIRI ATAS KE KANAN BAWAH
    int diagonal1 = 0;
    while(tempX < 7 && tempY < 9){
        if(kotak[tempX][tempY] != token) break;
        diagonal1++;
        tempX++; tempY++;
    }

    tempX = x-1, tempY = y-1;
    while(tempX > 0 && tempY > 1){
        if(kotak[tempX][tempY] != token) break;
        diagonal1++;
        tempX--; tempY--;
    }
    if(diagonal1 == 4){
        arahConnectFour = "Diagonal dari Kiri Atas ke Kanan Bawah";
        return true;
    }

    //CEK DIAGONAL KIRI BAWAH KE KANAN ATAS
    tempX = x, tempY = y;
    int diagonal2 = 0;
    while(tempX > 0 && tempY < 9){
        if(kotak[tempX][tempY] != token) break;
        diagonal2++;
        tempX--; tempY++;
    }
    tempX = x+1, tempY = y-1;
    while(tempX < 7 && tempY > 1){
        if(kotak[tempX][tempY] != token) break;
        diagonal2++;
        tempX++; tempY--;
    }
    if(diagonal2 == 4){
        arahConnectFour = "Diagonal dari Kiri Bawah ke Kanan Atas";
        return true;
    }

    // cout << horizontal << " " << vertikal << " " << diagonal1 << " " << diagonal2 << endl;
    //sampai sini jika tidak ada connect four
    return false;
}

void cetakKotak(){
    for(int i = 1; i <= 7; i++){
        for(int j = 1; j <= 9; j++){
                cout <<  kotak[i][j] << " ";
            }
        cout << endl;
    }
}

int main(){
    inputWarna();
    bgColor = warnaPemain1.fi; fontColor = warnaPemain1.se;
    cout << bgColor << fontColor;
    system("cls");
    for(int i = 1; i <= 7; i++){
        for(int j = 1; j <= 9; j++){
            if(j == 1 || j == 9){
                kotak[i][j] = '|';
            }
            else if(i==7){
                kotak[i][j] = '-';
            }
            else kotak[i][j] = ' ';
            cout << kotak[i][j] << " ";
        }
        cout << endl;
    }

    int round = 1;
    fill(begin(bawahKolom), end(bawahKolom), 1);

    while(round <= 42){
        char token;
        if(round%2){
            token = 'X';
            bgColor = warnaPemain2.fi;
            fontColor = warnaPemain2.se;
        } 
        else{
            token = 'O';
            bgColor = warnaPemain1.fi;
            fontColor = warnaPemain1.se;
        }
        
        cout <<"(Pemain " << ((round%2) ? '1' : '2') << ") Pilih Kolom 1-7: ";
        cekInput();
        system("cls");
        kotak[6-bawahKolom[kolom+1]+1][kolom+1] = token;
        
        //mengecek vertikal, horizontal, dan 2 diagonalnya:
        if(connect4(6-bawahKolom[kolom+1]+1, kolom+1, token)){
            cetakKotak();
            cout << "Selamat Pemain " << ((round%2) ? 1 : 2)
            << " Memenangkan Permainan dengan Connect Four " << 
            arahConnectFour << endl;
            
            system("pause");
            return 0;
        }
        
        cout << bgColor << fontColor;
        system("cls"); // membersihkan output kotak dan tulisan-tulisan sebelumnya
        cetakKotak();
        
        
        bawahKolom[kolom+1]++;
        round++;

    }

    cout << "Permainan Imbang, Silakan Coba Ulang Lagi Permainannya!";
    system("pause");
    return 0;
}