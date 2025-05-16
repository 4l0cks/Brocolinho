#include <Gamebuino-Meta.h>
#include "Player.h"
#include "Enemy.h"

Player player;
const int NUM_ENEMIES = 5;
Enemy enemies[NUM_ENEMIES];
int wave = 1;

enum GameState { MENU, PLAYING, GAME_OVER };
GameState gameState = MENU;

void spawnWave() {
  for (int i = 0; i < NUM_ENEMIES; i++) {
    enemies[i] = Enemy(); 
    enemies[i].spawn(player, 20);
  }
}

bool isWaveOver() {
  for (int i = 0; i < NUM_ENEMIES; i++) {
    if (enemies[i].alive) return false;
  }
  return true;
}

void resetGame() {
  player = Player();       
  for (int i = 0; i < NUM_ENEMIES; i++) {
    enemies[i] = Enemy();    
  }
  wave = 1;
  spawnWave();               
  gameState = PLAYING;
}

void setup() {
  gb.begin();
  randomSeed(analogRead(0));
}

void loop() {
  while (!gb.update());
  gb.display.clear();

  if (gameState == MENU) {
    gb.display.setCursor(10, 20);
    gb.display.print("Welcome to");
    gb.display.setCursor(10, 30);
    gb.display.print("Broccolinho!");

    gb.display.setCursor(10, 50);
    gb.display.print("Press A to start");

    if (gb.buttons.pressed(BUTTON_A)) {
      player = Player(); // Reset player
      spawnWave();
      gameState = PLAYING;
    }

    return; 
  }if (gameState == PLAYING) {
    player.move();
    player.draw();

    for (int i = 0; i < NUM_ENEMIES; i++) {
      enemies[i].move(player);
      enemies[i].draw();

      if (enemies[i].alive && player.collidesWith(enemies[i])) {
        player.takeDamage(1);
      }
    }

    player.attackZone(enemies, NUM_ENEMIES);

  
    gb.display.setCursor(0, 0);
    gb.display.print("HP: ");
    gb.display.print(player.hp);

    gb.display.setCursor(60, 0);
    gb.display.print("Wave: ");
    gb.display.print(wave);

   
    if (!player.isAlive()) {
      gameState = GAME_OVER;
    }

   
    if (isWaveOver()) {
      wave++;
      spawnWave();
    }

    if (gb.buttons.pressed(BUTTON_A)) {
      resetGame();
    }    

  } else if (gameState == GAME_OVER) {
    gb.display.setColor(RED);
    gb.display.setCursor(20, 20);
    gb.display.print("GAME OVER");

    gb.display.setCursor(10, 40);
    gb.display.print("Press A to Restart");

    if (gb.buttons.pressed(BUTTON_A)) {
      resetGame();
    }
  }
}
