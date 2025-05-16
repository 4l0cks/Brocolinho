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

  Enemy();
  void draw() const;
  void moveTowards(const Player& player);
  void spawnAwayFromPlayer(const Player& player, int minDistance);

private:
  int moveCooldown;           
  int moveDelay = 3;    
};

#endif 
