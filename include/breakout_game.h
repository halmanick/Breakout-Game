#pragma once

#include "ball.h"
#include "cinder/gl/gl.h"
#include "platform.h"
#include "brick.h"
#include "player.h"
#include <vector>

using std::vector;
using std::string;

namespace breakout {

/**
 * A class that holds all of the gameplay and objects for Breakout game
 */
class BreakoutGame {
 private:

  /**
   * sets up bricks in a new game given a bool to add textures
   * @param add_textures if true add textures
   */
  void SetupBricks(const bool add_textures);

  /**
   * sets up the game with default values and starting locations of objects given
   * a bool to add textures
   * @param add_textures add_textures if true add textures
   */
  void SetupNextLevel(const bool add_textures);

  /**
   * continues on current level
   */
  void ContinueOnCurrentLevel();

  /**
   * sets velocity of ball once platform makes the first move
   */
  void StartMovingBallOncePlatformMoves();

  /**
   * resets location of ball
   */
  void ResetBallLocation();

  /**
   * handles case when ball reaches bottom of game
   */
  void HandleBallReachingBottom();
  Platform platform_;
  Ball ball_;
  vector<Brick> bricks_;
  int level_ = 0;
  Player player_;
  bool game_running_ = false;
  int game_mode_;
  vec2 ball_starting_velocity_;
  const vec2 kBallSpeedIncrement = vec2(0, -0.5);
  vec2 platform_start_location_;
  const int kPlayerLives = 3;
  vector<int> high_scores_;

  // ball starting speeds and platform width, ranking from easy to hard difficulty
  const vector<vec2> kBallSpeeds{ vec2(0, -6), vec2(0, -7.5), vec2(0, -9.5) };
  const vector<float> kPlatformWidths{ 200, 150, 100 };

  // border locations
  const float kTopBorder;
  const float kBottomBorder;
  const float kLeftBorder;
  const float kRightBorder;

  // default values of objects
  const Color kPlatformColor = "red";
  const float kPlatformHeight = 10;
  const Color kBallColor = "blue";
  const float kBallRadius = 8;
  const float kBrickWidth = 120.0f;
  const float kBrickHeight = 40.0f;
  const vector<Color> brick_order_{ "purple", "magenta", "blue", "red", "orange", "green", "yellow" };
  const vector<int> brick_scores_{ 9, 8, 7, 5, 4, 3, 1 };
  const string kBrickTexturePath = "include\\bricktexture.jpeg";
  const string kPlatformTexturePath = "include\\platformtexture.jpg";

 public:

  /**
   * constructor for breakoutgame, given game width and height
   * @param game_width
   * @param game_height
   */
  BreakoutGame(const float game_width, const float game_height);

  /**
   * getter for platform in game used for testing
   * @return Platform
   */
  const Platform& GetPlatform() const;

  /**
   * setter for platform location used for testing
   * @param location to set platform at
   */
  void SetPlatformLocation(const Rectf& location);

  /**
   * getter for bricks in game used for testing
   * @return vector of Bricks
   */
  const vector<Brick>& GetBricks() const;

  /**
   * removes the bricks in game to simulate completing level for testing
   */
  void RemoveBricks();

  /**
   * getter for player in game used for testing
   * @return Player
   */
  const Player& GetPlayer() const;


  /**
   * setter for setting player's lives for testing
   * @param lives to set for player
   */
  void SetPlayerLives(const int& lives);

  /**
   * Getter for ball in game used for testing
   * @return Ball
   */
  const Ball& GetBall() const;

  /**
   * getter for current level in game used for testing
   * @return Level
   */
  const int& GetLevel() const;

  /**
   * Starts a new game given a bool to add textures
   * @param add_textures if true add textures
   */
  void StartNewGame(const bool add_textures, const int& difficulty);

  /**
   * method to update game information each frame given a bool to add textures
   * @param add_textures if true add textures
   */
  void UpdateFrame(const bool add_textures);

  /**
   * displays the current objects in game each frame
   */
  void Display() const;

  /**
   * method to display high scores in the game
   */
  void DisplayHighScores() const;

  /**
   * handles right key press
   */
  void HandleRightKey();

  /**
   * handles left key press
   */
  void HandleLeftKey();

  /**
   * handles mouse drag
   * @param mouse_position location of mouse
   */
  void HandleMouseDrag(vec2 mouse_position);

  /**
   * Checks if game is over
   * @return true if game is over
   */
  bool GameOver();

  /**
   * method to add players score to leaderboard
   */
  void AddToLeaderboard();

  /**
   * clears the bricks in game and sets game_running to false
   */
  void ClearGame();
};


}  //  namespace breakout