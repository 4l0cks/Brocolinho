#include <Gamebuino-Meta.h>
#include "Player.h"
#include "Enemy.h"

Player player;
const int NUM_ENEMIES = 5;
Enemy enemies[NUM_ENEMIES];

void setup() {
  gb.begin();
  randomSeed(analogRead(0));

  for (int i = 0; i < NUM_ENEMIES; i++) {
    enemies[i] = Enemy();
    enemies[i].spawnAwayFromPlayer(player, 20); // Keep at least 20 pixels away
  }
}

void loop() {
  while (!gb.update());
  gb.display.clear();

  player.move();
  player.draw();

  for (int i = 0; i < NUM_ENEMIES; i++) {
    enemies[i].moveTowards(player);
    enemies[i].draw();

    if (player.collidesWith(enemies[i])) {
      gb.display.setCursor(0, i * 10);
      gb.display.print("Hit by enemy ");
      gb.display.print(i);
    }
  }
}

