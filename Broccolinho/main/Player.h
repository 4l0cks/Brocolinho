//
// Created by kassi on 5/16/2025.
//
#ifndef PLAYER_H
#define PLAYER_H

#include <Gamebuino-Meta.h>

class Enemy;

class Player {
public:
    int x, y, w, h;
    int hp;
    int speed;

    Player(); 
    void draw() const;
    void move();
    bool collidesWith(const Enemy& enemy) const;
    void attackZone(Enemy enemies[], int enemyCount);
    bool isAlive() const;
    void takeDamage(int amount);


private:
    unsigned long lastAttackTime;
    unsigned long attackCooldown;

    unsigned long lastDamageTime;
    unsigned long damageCooldown;
};


#endif //PLAYER_H
