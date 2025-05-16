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

    Player(); 
    void draw() const;
    void move();
    bool collidesWith(const Enemy& enemy) const;
    bool isAlive() const;
};


#endif //PLAYER_H
