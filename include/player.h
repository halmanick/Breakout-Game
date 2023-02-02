#pragma once

#include <string>

using std::string;

namespace breakout {

/**
 * class that holds player info
 */
class Player {
 private:
  int lives_;
  int score_;

 public:
  /**
   * default construcotr
   */
  Player();

  /**
   * constructs a player given number of lives
   * @param name of player
   * @param lives player starts with
   */
  Player(const int lives);

  /**
   * getter for number of lives player has left
   * @return number of lives player has left
   */
  const int GetLives() const;

  /**
   * setter for lives of player used for testing
   * @param lives to set
   */
  void SetLives(const int& lives);

  /**
   * getter for score player has
   * @return score of player
   */
  const int GetScore() const;

  /**
   * method to decrement number of lives of player
   */
  void DecreaseLives();

  /**
   * returns whether player is alive or not, if lives are greater than or equal
   * to zero
   * @return true if player is alive
   */
  bool PlayerDead() const;

  /**
   * increases the player score by a given score to add
   * @param score to add to player's score
   */
  void IncreaseScore(const int score);
};

}  //  namespace breakout