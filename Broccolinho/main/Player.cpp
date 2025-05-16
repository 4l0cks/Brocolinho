#include "Player.h"
#include "Enemy.h"

Player::Player() {
  w = h = 3;
  x = (gb.display.width() - w) / 2;
  y = (gb.display.height() - h) / 2;
  int hp = 5;
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
  return !(x + w < enemy.x || x > enemy.x + enemy.w || y + h < enemy.y || y > enemy.y + enemy.h);
}

bool Player::isAlive() const {
  return hp > 0;
}