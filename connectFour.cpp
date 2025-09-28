#include <iostream>
#include <utility>
#include <string>
#include <algorithm>
#include <limits>
#include <chrono>
#include <thread>
#include <vector>

#define fi first
#define se second
#define pb push_back
using namespace std;

string pemain1, pemain2;
char kotak[10][10];
string arahConnectFour;
int kolom, ronde, temp, giliran, giliranTemp, skorPemain1, skorPemain2;
char token;
int bawahKolom[10];
vector<pair<int,int>> tokenKemenangan;

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
    cout << "(" << pemain1 << ") Pilih warna favoritmu (merah/hijau/biru/cyan): ";
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
    cout << "(" << pemain2 <<") Pilih warna favoritmu (merah/hijau/biru/cyan): ";
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
    tokenKemenangan = {};
    int horizontal = 0;
    for(int i = y; i < 9; i++){
        if(kotak[x][i] != token) break;
        else{
            horizontal++;
            tokenKemenangan.pb({x, i});
        } 
    }
    for(int i = y-1; i > 1; i--){
        if(kotak[x][i] != token) break;
        else{
            horizontal++;
            tokenKemenangan.pb({x,i});
        } 
    }
    if(horizontal==4){
        arahConnectFour = "Horizontal";
        return true;
    }

    //CEK VERTIKAL
    int vertikal = 0; tokenKemenangan = {};
    for(int i = x; i < 7; i++){
        if(kotak[i][y] != token) break;
        else{
            vertikal++;
            tokenKemenangan.pb({i, y});  
        } 
    }
    for(int i = x-1; i > 0; i--){
        if(kotak[i][y] != token) break;
        else{
            vertikal++;
            tokenKemenangan.pb({i, y});  
        } 
    }
    if(vertikal == 4){
        arahConnectFour = "Vertikal";
        return true;
    }

    int tempX = x, tempY = y;
    //CEK DIAGONAL KIRI ATAS KE KANAN BAWAH
    int diagonal1 = 0; tokenKemenangan = {};
    while(tempX < 7 && tempY < 9){
        if(kotak[tempX][tempY] != token) break;
        diagonal1++;
        tokenKemenangan.pb({tempX, tempY});  
        tempX++; tempY++;
    }

    tempX = x-1, tempY = y-1;
    while(tempX > 0 && tempY > 1){
        if(kotak[tempX][tempY] != token) break;
        diagonal1++;
        tokenKemenangan.pb({tempX, tempY});  
        tempX--; tempY--;

    }
    if(diagonal1 == 4){
        arahConnectFour = "Diagonal dari Kiri Atas ke Kanan Bawah";
        return true;
    }

    //CEK DIAGONAL KIRI BAWAH KE KANAN ATAS
    tempX = x, tempY = y;
    int diagonal2 = 0; tokenKemenangan = {};
    while(tempX > 0 && tempY < 9){
        if(kotak[tempX][tempY] != token) break;
        diagonal2++;
        tokenKemenangan.pb({tempX, tempY});  
        tempX--; tempY++;
    }
    tempX = x+1, tempY = y-1;
    while(tempX < 7 && tempY > 1){
        if(kotak[tempX][tempY] != token) break;
        diagonal2++;
        tokenKemenangan.pb({tempX, tempY});  
        tempX++; tempY--;
    }
    if(diagonal2 == 4){
        arahConnectFour = "Diagonal dari Kiri Bawah ke Kanan Atas";
        return true;
    }

    //sampai sini jika tidak ada connect four
    return false;
}

void cetakAnimasiKotak(){
    int row = 1;
    while(row <= 6-bawahKolom[kolom+1]+1){
        system("cls");
        for(int i = 1; i <= 7; i++){
            for(int j = 1; j <= 9; j++){
                    if(i==row && kolom+1==j){
                        cout << token << " ";
                    }
                    else cout <<  kotak[i][j] << " ";
                }
            cout << endl;
        }
        row++;
        this_thread::sleep_for(chrono::milliseconds(250));
    }
    kotak[6-bawahKolom[kolom+1]+1][kolom+1] = token;
}

void cetakKotakBiasaDanSkor(){
    cout << "Ronde "<< ronde - temp + 1 << " (dari " << ronde << ")" << endl;
    cout << "Skor " << pemain1 << ": " << skorPemain1 << endl;
    cout << "Skor " << pemain2 << ": " << skorPemain2 << endl;
    cout << endl;
    for(int i = 1; i <= 7; i++){
        for(int j = 1; j <= 9; j++){
                cout <<  kotak[i][j] << " ";
            }
        cout << endl;
    }
    cout << endl;
}

void cetakKotakKemenangan(){
    string fontMenang = "\033[1m", bgMenang = "\033[43m";
    for(int i = 1; i <= 7; i++){
            for(int j = 1; j <= 9; j++){
                bool cek = false;
                    for(pair<int,int> k : tokenKemenangan){
                        if(k.fi==i && k.se==j){
                            cek = true;
                            cout << RESET << bgMenang << fontMenang << kotak[i][j];
                            // cout << i << " " << j;
                            cout << RESET << bgColor << fontColor << " ";
                            break;
                        }
                    }
                    if(!cek) cout <<  kotak[i][j] << " ";
                }
            cout << endl;
        }
}

void pergantianGiliran(){
    if(giliranTemp==2){
        token = 'X';
        bgColor = warnaPemain2.fi;
        fontColor = warnaPemain2.se;
    } 
    else{
        token = 'O';
        bgColor = warnaPemain1.fi;
        fontColor = warnaPemain1.se;
    }
}

int main(){
    cout << "Nama Pemain 1: "; cin >> pemain1;
    cout << "Nama Pemain 2: "; cin >> pemain2;
    cout << "Berapa banyak ronde permainan yang mau dimainkan? (bilangan ganjil): ";
    while(!(cin >> ronde) || ronde%2==0){
        cout << "Input tidak valid, silakan input kembali (integer/bilangan ganjil): ";
    }

    inputWarna();
    temp = ronde;
    giliran = 2;

    //MULAI RONDE PERMAINAN 
    while(temp && skorPemain1 < ronde/2+1 && skorPemain2 < ronde/2+1){
        bool imbang = true;
        giliran = ((giliran==1) ? 2 : 1);
        giliranTemp = giliran;
        pergantianGiliran();
       
        cout << bgColor << fontColor;
        system("cls");

        //set kotak kosong
        for(int i = 1; i <= 7; i++){
            for(int j = 1; j <= 9; j++){
                if(j == 1 || j == 9){
                    kotak[i][j] = '|';
                }
                else if(i==7){
                    kotak[i][j] = '-';
                }
                else kotak[i][j] = ' ';
                // cout << kotak[i][j] << " ";
            }
            // cout << endl;
        }
    
        int round = 1;
        fill(begin(bawahKolom), end(bawahKolom), 1);
        cetakKotakBiasaDanSkor();
        
        while(round <= 42){
            
            cout <<"(" << ((giliranTemp==1) ? pemain1 : pemain2) << ", " << token << ") Pilih Kolom 1-7: ";
            cekInput();
            
            cetakAnimasiKotak();

            //mengecek vertikal, horizontal, dan 2 diagonalnya:
            if(connect4(6-bawahKolom[kolom+1]+1, kolom+1, token)){
                system("cls");
                if(giliranTemp==1) skorPemain1++;
                else skorPemain2++;
                cout << "Ronde "<< ronde - temp + 1 << " (dari " << ronde << ")" << endl;
                cout << "Skor " << pemain1 << ": " << skorPemain1 << endl;
                cout << "Skor " << pemain2 << ": " << skorPemain2 << endl;
                cout << endl;
                cetakKotakKemenangan();
                cout << endl;
                cout << "Selamat " << ((giliranTemp==1) ? pemain1 : pemain2)
                << " Memenangkan Permainan dengan Connect Four " << 
                arahConnectFour << endl;

                imbang = false;
                break;
            }
            
            giliranTemp = ((giliranTemp==1) ? 2 : 1);
            pergantianGiliran(); // mengganti warna terminal dan token sesuai giliran pemain yang berganti
            cout << bgColor << fontColor;
            system("cls"); // membersihkan output kotak dan tulisan-tulisan sebelumnya
            cetakKotakBiasaDanSkor();
            
            bawahKolom[kolom+1]++;
            round++;
        }
    
        if(imbang) cout << "Permainan Imbang, Silakan Coba Ulang Lagi Permainannya!" << endl;
        else temp--;
        if(temp){
            cout << "Lanjutkan permainan? (y/n)";
            string input;
            while((cin >> input) && input != "y" && input != "n"){
                cout << "Input tidak valid, silakan input kembali (y/n): ";
            }
            if(input == "n") break;
        }
        
    }

    cout << endl;
    if(skorPemain1 != skorPemain2) cout << "Selamat, " << ((skorPemain1 > skorPemain2) ? pemain1 : pemain2)
    << " memenangkan permainan Connect Four ini dengan skor " << max(skorPemain1, skorPemain2) << " kemenangan dari" << ronde-temp << " ronde permainan" << endl;
    else{
        cout << "Permainan Connect Four ini berakhir imbang dengan skor masing-masing pemain: " << endl;
        cout << pemain1 << ": " << skorPemain1 << endl;
        cout << pemain2 << ": " << skorPemain2 << endl;
    } 
    
    cout << endl;
    cout << "Tutup terminal (y/n): ";
    string terminal;
    while((cin >> terminal) && terminal != "y"){
        cout << "Tutup terminal (y/n): ";
    }
    return 0;
}