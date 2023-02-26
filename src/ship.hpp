#ifndef SHIP_HPP_
#define SHIP_HPP_

class enemyShip;
#include "enemyShip.hpp"

class ship{
private:
    int x, y;               // posisi kapal
    int health;             // kesehatan kapal
    int const damage = 10;  // besar damage
    int maxRange = 5;       // jarak tembak maksimum

public:
    ship();
    int calculateDistance(enemyShip& enemy);
    void showPosition(enemyShip& enemy);
    bool isAlive();
    void attack(enemyShip& enemy);
    void move(int n, int index);
    bool isOut();
    void dead();

friend class enemyShip;
};

#endif /*SHIP_HPP_*/