#include <bits/stdc++.h>
using namespace std;

char kotak[10][10];
string arahConnectFour;

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

    cout << horizontal << " " << vertikal << " " << diagonal1 << " " << diagonal2 << endl;
    //sampai sini jika tidak ada connect four
    return false;

}

int main(){
    for(int i = 1; i <= 7; i++){
        for(int j = 1; j <= 9; j++){
            if(j == 1 || j == 9){
                kotak[i][j] = '|';
            }
            else if(i==7){
                kotak[i][j] = '_';
            }
            else kotak[i][j] = ' ';
            cout << kotak[i][j];
        }
        cout << endl;
    }

    int round = 1;
    int bawahKolom[10];
    fill(begin(bawahKolom), end(bawahKolom), 1);

    while(round <= 42){
        cout << "Pilih Kolom 1-7: ";
        int kolom; cin >> kolom;
        while(kolom < 1 || kolom > 7){
            cout << "Input tidak valid, silakan pilih kolom yang sesuai (1-7): ";
            cin >> kolom;
        }
        while(bawahKolom[kolom+1] > 6){
            cout << "Kolom " << kolom << " sudah penuh, silakan pilih kolom lainnya: ";
            cin >> kolom;
        }
        char token;
        if(round%2) token = 'X';
        else token = 'O';
        kotak[6-bawahKolom[kolom+1]+1][kolom+1] = token;
        
        for(int i = 1; i <= 7; i++){
            for(int j = 1; j <= 9; j++){
                cout << kotak[i][j];
            }
            cout << endl;
        }
        
        //mengecek vertikal, horizontal, dan 2 diagonalnya:
        if(connect4(6-bawahKolom[kolom+1]+1, kolom+1, token)){
            cout << "Selamat Pemain " << ((round%2) ? 1 : 2) << " Memenangkan Permainan dengan Connect Four " << arahConnectFour << endl;
            return 0;
        }
        
        bawahKolom[kolom+1]++;
        round++;
    }

    cout << "Permainan Imbang, Silakan Coba Ulang Lagi Permainannya!";
    return 0;
}