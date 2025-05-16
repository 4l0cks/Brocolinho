#include <Gamebuino-Meta.h>
#include "Player.h"
#include "Enemy.h"

Player::Player() {
  w = h = 3;
  x = (gb.display.width() - w) / 2;
  y = (gb.display.height() - h) / 2;
  hp = 5;

  lastAttackTime = 0;
  attackCooldown = 500;
  lastDamageTime = 0;
  damageCooldown = 500;
}

void Player::draw() const {
  gb.display.setColor(RED);
  gb.display.fillRect(x, y, w, h);
}

void Player::move() {
  if (gb.buttons.repeat(BUTTON_LEFT, 1))  { x--; }
  if (gb.buttons.repeat(BUTTON_RIGHT, 1)) { x++; }
  if (gb.buttons.repeat(BUTTON_UP, 1))    { y--; }
  if (gb.buttons.repeat(BUTTON_DOWN, 1))  { y++; }

  
  if (x < 0) x = 0;
  if (y < 0) y = 0;
  if (x + w > gb.display.width())  x = gb.display.width() - w;
  if (y + h > gb.display.height()) y = gb.display.height() - h;
}

bool Player::collidesWith(const Enemy& enemy) const {
  if (!enemy.alive) return false; 
  return !(x + w < enemy.x || x > enemy.x + enemy.w || y + h < enemy.y || y > enemy.y + enemy.h);
}

bool Player::isAlive() const {
  return hp > 0;
}

void Player::attackZone(Enemy enemies[], int enemyCount) {
  unsigned long currentTime = millis();

  int attackX = x - 6;
  int attackY = y - 6;
  int attackW = w + 12;
  int attackH = h + 12;

  if (currentTime - lastAttackTime >= attackCooldown) {
    gb.display.setColor(RED);
    gb.display.drawRect(attackX, attackY, attackW, attackH);

    for (int i = 0; i < enemyCount; i++) {
      if (enemies[i].alive) {
        if (attackX < enemies[i].x + enemies[i].w &&
            attackX + attackW > enemies[i].x &&
            attackY < enemies[i].y + enemies[i].h &&
            attackY + attackH > enemies[i].y) {
          enemies[i].alive = false;
          enemies[i].w = 0;
        }
      }
    }

    lastAttackTime = currentTime;
  }
}



void Player::takeDamage(int amount) {
  unsigned long currentTime = millis();
  if (currentTime - lastDamageTime >= damageCooldown) {
    hp -= amount;
    if(hp < 0) hp = 0;
    lastDamageTime = currentTime;
  }
}