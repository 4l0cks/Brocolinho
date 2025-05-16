//
// Created by kassi on 5/16/2025.
//
#include "Enemy.h"
#include "Player.h"

Enemy::Enemy() {
  w = h = 3;
  x = 10; 
  y = 10;
  moveCooldown = 0;
}

void Enemy::draw() const {
  gb.display.setColor(GREEN);
  gb.display.fillRect(x, y, w, h);
}

void Enemy::moveTowards(const Player& player) {
  if (moveCooldown > 0) {
    moveCooldown--;
    return;  
  }

  moveCooldown = moveDelay;
   if (x < player.x) x++;
  else if (x > player.x) x--;

  if (y < player.y) y++;
  else if (y > player.y) y--;
}

void Enemy::spawnAwayFromPlayer(const Player& player, int minDistance) {
  int attempts = 0;
  const int maxAttempts = 50;

  do {
    x = random(0, gb.display.width() - w);
    y = random(0, gb.display.height() - h);

    int dx = x - player.x;
    int dy = y - player.y;
    float dist = sqrt(dx * dx + dy * dy);

    if (dist >= minDistance) break;
    attempts++;
  } while (attempts < maxAttempts);
}