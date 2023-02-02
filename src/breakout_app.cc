#include "breakout_app.h"

namespace breakout {

BreakoutApp::BreakoutApp() {
  ci::app::setWindowPos(kWindowMarginX, kWindowMarginY);
  ci::app::setWindowSize(kWindowWidth, kWindowHeight);
  on_menu_ = true;
  on_leaderboard_ = false;
  on_game_ = false;
  menu_ = Menu("Breakout",
               vec2(kWindowWidth / 2, kWindowHeight / 8),
               menu_title_font);
  menu_.AddButton("Easy",
                  vec2(kWindowWidth / 3, kWindowHeight / 2.6),
                  vec2(kWindowWidth / 1.5, kWindowHeight / 2),
                  button_font);
  menu_.AddButton("Medium",
                  vec2(kWindowWidth / 3,kWindowHeight / 1.9),
                  vec2(kWindowWidth / 1.5,kWindowHeight /
                                               1.55), button_font);
  menu_.AddButton("Hard",
                  vec2(kWindowWidth / 3, kWindowHeight / 1.48),
                  vec2(kWindowWidth / 1.5, kWindowHeight
                                               / 1.25), button_font);
  menu_.AddButton("High Scores",
                  vec2(kWindowWidth / 3, kWindowHeight / 1.21),
                  vec2(kWindowWidth / 1.5, kWindowHeight / 1.05),
                  button_font);
}

void BreakoutApp::draw() {
  if (on_menu_) {
    ci::gl::clear();
    menu_.Draw(menu_title_font, button_font);
  }

  if (on_leaderboard_) {
    ci::gl::clear();
    breakout_game_.DisplayHighScores();
  }

  if (on_game_) {
    ci::gl::clear();
    breakout_game_.Display();
  }
}

void BreakoutApp::update() {
  if (breakout_game_.GameOver()) {
    breakout_game_.AddToLeaderboard();
    breakout_game_.ClearGame();
    on_menu_ = true;
    on_game_ = false;
  }

  if (on_game_) {
    breakout_game_.UpdateFrame(kAddTextures);
  }
}

void BreakoutApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_RIGHT:
      if (on_game_) {
        breakout_game_.HandleRightKey();
      }

      break;

    case ci::app::KeyEvent::KEY_LEFT:
      if (on_game_) {
        breakout_game_.HandleLeftKey();
      }

      break;

    case ci::app::KeyEvent::KEY_b:
      if (on_leaderboard_) {
        on_leaderboard_ = false;
        on_menu_ = true;
      }

      break;
  }
}

void BreakoutApp::mouseDown(ci::app::MouseEvent event) {
  if (on_leaderboard_ | on_game_) {
    return;
  }

  if (on_menu_) {
    if (menu_.ButtonPressed("Easy", event.getPos())) {
      on_menu_ = false;
      on_game_ = true;
      breakout_game_.ClearGame();
      breakout_game_.StartNewGame(kAddTextures, kEasyDifficulty);
    }

    if (menu_.ButtonPressed("Medium", event.getPos())) {
      on_menu_ = false;
      on_game_ = true;
      breakout_game_.ClearGame();
      breakout_game_.StartNewGame(kAddTextures, kMediumDifficulty);
    }

    if (menu_.ButtonPressed("Hard", event.getPos())) {
      on_menu_ = false;
      on_game_ = true;
      breakout_game_.ClearGame();
      breakout_game_.StartNewGame(kAddTextures, kHardDifficulty);
    }

    if (menu_.ButtonPressed("High Scores", event.getPos())) {
      on_menu_ = false;
      on_leaderboard_ = true;
    }
  }
}

void BreakoutApp::mouseDrag(ci::app::MouseEvent event) {
  if (on_game_) {
    breakout_game_.HandleMouseDrag(event.getPos());
  }
}

}  // namespace breakout
