#include "breakout_game.h"

namespace breakout {

BreakoutGame::BreakoutGame(const float game_width, const float game_height)
    : kTopBorder(game_height / 8), kLeftBorder(0), kRightBorder(game_width),
      kBottomBorder(game_height) {
}

const Platform& BreakoutGame::GetPlatform() const {
  return platform_;
}

void BreakoutGame::SetPlatformLocation(const Rectf& location) {
  platform_.SetLocation(location);
}

const vector<Brick>& BreakoutGame::GetBricks() const {
  return bricks_;
}

void BreakoutGame::RemoveBricks() {
  bricks_.clear();
}

const Ball& BreakoutGame::GetBall() const {
  return ball_;
}

const Player& BreakoutGame::GetPlayer() const {
  return player_;
}

void BreakoutGame::SetPlayerLives(const int& lives) {
  player_.SetLives(lives);
}

const int& BreakoutGame::GetLevel() const {
  return level_;
}

void BreakoutGame::StartNewGame(const bool add_textures, const int& difficulty) {
  level_ = 0;
  game_mode_ = difficulty;
  ball_starting_velocity_ = kBallSpeeds[game_mode_];
  player_ = Player(kPlayerLives);
  platform_start_location_ = vec2(kRightBorder / 2, kBottomBorder);
  SetupNextLevel(add_textures);
  game_running_ = true;
}

void BreakoutGame::SetupNextLevel(const bool add_textures) {
  if (add_textures) {
    platform_ = Platform(platform_start_location_,
                         kPlatformWidths[game_mode_], kPlatformHeight,
                         kPlatformColor, kPlatformTexturePath);
  } else {
    platform_ = Platform(platform_start_location_,
                         kPlatformWidths[game_mode_], kPlatformHeight,
                         kPlatformColor);
  }

  ResetBallLocation();
  ball_starting_velocity_ += (float (level_) * kBallSpeedIncrement);
  level_++;
  SetupBricks(add_textures);
}

void BreakoutGame::ResetBallLocation() {
  vec2 ball_starting_location =
      vec2(platform_start_location_.x,
           platform_start_location_.y - 3 * kPlatformHeight);
  ball_ = Ball(kBallRadius, kBallColor, ball_starting_location,
               vec2());
}

void BreakoutGame::HandleBallReachingBottom() {
  if (ball_.ReachedBottom(kBottomBorder)) {
    player_.DecreaseLives();
    platform_start_location_ = vec2(platform_.GetLocation().getCenter().x,
                                    kBottomBorder);
    ResetBallLocation();
  }
}

void BreakoutGame::Display() const {
  ci::gl::color(Color("white"));
  ci::gl::drawLine(vec2(kLeftBorder, kTopBorder),
                   vec2(kRightBorder, kTopBorder));
  string level = "Level: " + std::to_string(level_);
  ci::gl::drawStringCentered(level,
                             vec2(kRightBorder / 8, kTopBorder / 3),
                             "white", ci::Font("calibri",
                                               40));
  string score = "Score: " + std::to_string(player_.GetScore());
  ci::gl::drawStringCentered(score,
                             vec2(kRightBorder / 1.2, kTopBorder / 3),
                             "white", ci::Font("calibri",
                                               40));
  string lives = "Lives: " + std::to_string(player_.GetLives());
  ci::gl::drawStringCentered(lives,
                             vec2(kRightBorder / 2, kTopBorder / 3),
                             "white", ci::Font("calibri",
                                               40));
  platform_.Draw();
  ball_.Draw();
  for (size_t i = 0; i < bricks_.size(); i++) {
    bricks_[i].Draw();
  }
}

void BreakoutGame::DisplayHighScores() const {
  ci::gl::color(Color("white"));
  ci::gl::drawStringCentered("High Scores",
                             vec2(kRightBorder / 2, kTopBorder / 6),
                             "white", ci::Font("calibri",
                                               60));
  for (size_t i = 0; i < high_scores_.size(); i++) {
    string score = std::to_string(high_scores_[i]);
    ci::gl::drawStringCentered(score,
                               vec2(kRightBorder / 2,
                                    (1.2 * kTopBorder) + (40 * i)),
                               "white", ci::Font("calibri",
                                                 40));
  }

  ci::gl::color(Color("white"));
  ci::gl::drawStringCentered("Press B to go back to Menu",
                             vec2(kRightBorder / 2, 0.9 *
                                                        kBottomBorder),
                             "white", ci::Font("calibri",
                                               40));
}

void BreakoutGame::UpdateFrame(const bool add_textures) {
  HandleBallReachingBottom();
  StartMovingBallOncePlatformMoves();
  if (bricks_.empty() && game_running_) {
    SetupNextLevel(add_textures);
  } else {
    ContinueOnCurrentLevel();
  }
}

void BreakoutGame::ContinueOnCurrentLevel() {
  ball_.UpdateVelocityOnWallCollisions(kTopBorder, kBottomBorder, kLeftBorder,
                                       kRightBorder);
  ball_.UpdateVelocityOnPlatformCollision(platform_.GetLocation());
  for (auto it = bricks_.begin(); it != bricks_.end(); it++) {
    if (ball_.CollideWithBrick(it->GetLocation())) {
      player_.IncreaseScore(it->GetScore());
      bricks_.erase(it);
      break;
    }
  }

  ball_.UpdatePosition();
}

void BreakoutGame::StartMovingBallOncePlatformMoves() {
  vec2 platform_starting_center =
      vec2(platform_start_location_.x,
           platform_start_location_.y - (kPlatformHeight / 2));
  if (ball_.GetVelocity() == vec2() && platform_.GetLocation().getCenter()
                                           != platform_starting_center) {
    ball_.SetVelocity(ball_starting_velocity_);

  }
}

void BreakoutGame::HandleRightKey() {
  platform_.MoveRightKey(kRightBorder);
}

void BreakoutGame::HandleLeftKey() {
  platform_.MoveLeftKey(kLeftBorder);
}

void BreakoutGame::HandleMouseDrag(vec2 mouse_position) {
  platform_.MoveWithMouse(mouse_position, kLeftBorder, kRightBorder);
}

void BreakoutGame::SetupBricks(const bool add_textures) {
  float start_location_x = kLeftBorder;
  float start_location_y = kTopBorder + (kBottomBorder / 6);
  size_t num_of_columns = size_t (kRightBorder - kLeftBorder) /
                          size_t (kBrickWidth);
  for (size_t row = 0; row < brick_order_.size(); row++) {
    for (size_t col = 0; col < num_of_columns; col++) {
      Rectf brick_location = Rectf(vec2(start_location_x, start_location_y),
                                   vec2(start_location_x + kBrickWidth,
                                        start_location_y + kBrickHeight));
      if (add_textures) {
        bricks_.push_back(Brick(brick_location, brick_order_[row],
                                kBrickTexturePath, brick_scores_[row]));
      } else {
        bricks_.push_back(Brick(brick_location, brick_order_[row],
                                brick_scores_[row]));
      }

      start_location_x += kBrickWidth;
    }

    start_location_x = kLeftBorder;
    start_location_y += kBrickHeight;
  }
}

bool BreakoutGame::GameOver() {
  return player_.PlayerDead();
}

void BreakoutGame::AddToLeaderboard() {
  if (!std::count(high_scores_.begin(), high_scores_.end(),
                  player_.GetScore())) {
    high_scores_.push_back(player_.GetScore());
  }
  std::sort(high_scores_.rbegin(), high_scores_.rend());
}

void BreakoutGame::ClearGame() {
  bricks_.clear();
  ball_.SetVelocity(vec2());
  game_running_ = false;
}

}