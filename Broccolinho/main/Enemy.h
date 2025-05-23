//
// Created by kassi on 5/16/2025.
//
#ifndef ENEMY_H
#define ENEMY_H

#include <Gamebuino-Meta.h>
class Player;

class Enemy {
public: 
  int x, y, w, h;
  bool alive;

  Enemy();
  void draw() const;
  void move(const Player& player);
  void spawn(const Player& player, int minDistance);

private:
  int moveCooldown;           
  int moveDelay = 3;    
};

#endif 
