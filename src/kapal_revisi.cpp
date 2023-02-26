#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <windows.h>

#include "ship.hpp"
#include "enemyShip.hpp"

using namespace std;

// Deklarasi class ship untuk kapal
class ship;
// Konstruktor class ship
ship::ship(){
    x = 0; // atribut awal kapal
    y = 0;
    health = 100;
}

// Fungsi untuk menghitung jarak 2 kapal
int ship::calculateDistance(enemyShip& enemy){
    int dx = abs(x - enemy.x);
    int dy = abs(y - enemy.y);
    return sqrt(dx * dx + dy * dy);
}

// Prosedur untuk menampilkan posisi kapal
void ship::showPosition(enemyShip& enemy){
    cout << "Kapal saat ini berada pada koordinat (" << x << ", " << y << ")" << endl;
    cout << "Kapal musuh berada di koordinat (" << enemy.x << ", " << enemy.y << ")" << endl;
}

// Fungsi untuk mengecek kondisi kapal
bool ship::isAlive(){
    return health > 0;
}

// Prosedur menyerang lawan
void ship::attack(enemyShip& enemy){
    int distance = calculateDistance(enemy);
    if (distance <= maxRange) {
        cout << "Kapal menembakkan meriamnya dan mengenai kapal musuh!" << endl;
        enemy.health -= damage;
        if (enemy.health <= 0) {
            cout << "Kapal musuh tenggelam!" << endl;
        } else {
            cout << "Kapal musuh memiliki kesehatan " << enemy.health << endl;
        }
    } else {
        cout << "Kapal musuh terlalu jauh, tidak dapat ditembak!" << endl;
    }
}

// Prosedur untuk bergerak
void ship::move(int n, int index){
    if (index == 0){
        y += n;
    } else {
        x += n;
    }
}

// Fungsi untuk mengecek kapal keluar peta atau tidak
bool ship::isOut(){
    return x > 10 || y > 10 || x < -10 || y < - 10;
}

// Prosedur jika kapal keluar peta maka dia tenggelam
void ship::dead(){
    health = 0;
}

// Deklarasi class enemyShip untuk kapal lawan
class enemyShip;
// Konstruktor class enemyShip
enemyShip::enemyShip(){
    srand(time(0));
    int num1, num2;
    do {
        num1 = rand() % 2;
        num2 = rand() % 2;
        x = num1 * (rand() % 10 + 1);
        y = num2 * (rand() % 10 + 1);
    } while (x == 0 && y == 0);
    health = 50;
}

// Fungsi untuk mengecek keadaan kapal lawan
bool enemyShip::isAlive(){
    return health > 0;
}

// Prosedur menyerang dari kapal lawan
void enemyShip::attack(ship& ship){
    int distance = ship.calculateDistance(*this);
    if (distance <= maxRange) {
        cout << "Kapal musuh menembakkan meriamnya dan mengenai kapal!" << endl;
        ship.health -= damage;
        if (ship.health <= 0) {
            cout << "Kapal tenggelam!" << endl;
        } else {
            cout << "Kapal memiliki kesehatan " << ship.health << endl;
        }
    } else {
        cout << "Kapal terlalu jauh, musuh tidak dapat menembak!" << endl;
    }
}

int main(int argc, char const *argv[])
{
    ship ally; // deklarasi objek kapal dengan nama ally
    enemyShip enemy; // deklarasi objek kapal lawan dengan nama enemy

    while (ally.isAlive())
    {
        ally.showPosition(enemy); // menampilkan koordinat kapal
        Sleep(1000);

        int choice;
        cout << "Apa yang ingin dilakukan kapal?" << endl;
        cout << "1. Bergerak" << endl;
        cout << "2. Menembak" << endl;
        cout << "3. Diam di tempat" << endl;
        cin >> choice;
        Sleep(1000);

        switch (choice) {
            case 1: {
                // Meminta input arah gerak
                int direction;
                cout << "Pilih arah gerak:" << endl;
                cout << "1. Ke atas" << endl;
                cout << "2. Ke bawah" << endl;
                cout << "3. Ke kanan" << endl;
                cout << "4. Ke kiri" << endl;
                cin >> direction;
                
                // Menggerakkan kapal
                int n = pow(-1, ((direction + 1) % 2));
                int index = floor((direction + 1) / 4);
                
                ally.move(n, index);

                // Cek apakah kapal keluar dari peta
                if (ally.isOut()) {
                    cout << "Kapal keluar dari peta!" << endl;
                    ally.dead();
                    break;
                }
                break;
            }
            case 2: {
                // Menyerang kapal musuh
                ally.attack(enemy);
                
                // Cek apakah kapal musuh masih hidup
                if (!enemy.isAlive()) {
                    cout << "Kapal musuh berhasil dikalahkan!" << endl;
                    break;
                }
                
                // Serangan balik dari kapal musuh
                Sleep(1000);
                enemy.attack(ally);
                break;
            }
            case 3: {
                // Diam di tempat
                cout << "Kapal diam di tempat." << endl;
                
                // Serangan dari kapal musuh
                Sleep(1000);
                enemy.attack(ally);
                break;
            }
            default:
                cout << "Perintah tidak valid!" << endl;
                break;
        }
    }

    // Game over
    Sleep(1000);
    cout << "Kapal tenggelam! Jumlah kapal musuh yang berhasil dikalahkan: 1" << endl;
    return 0;
}
