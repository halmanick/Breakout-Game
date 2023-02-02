#include "player.h"

namespace breakout {

Player::Player() {
  lives_ = 0;
  score_ = 0;
}

Player::Player(const int lives) {
  lives_ = lives;
  score_ = 0;
}

const int Player::GetLives() const {
  return lives_;
}

void Player::SetLives(const int &lives) {
  lives_ = lives;
}

const int Player::GetScore() const {
  return score_;
}

void Player::DecreaseLives() {
  lives_--;
}

bool Player::PlayerDead() const {
  return (lives_ < 0);
}

void Player::IncreaseScore(const int score) {
  score_ += score;
}

}  //  namespace breakout