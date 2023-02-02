#pragma once
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "breakout_game.h"
#include "menu.h"


namespace breakout {

/**
 * An app to play the game Breakout
 */
class BreakoutApp : public ci::app::App{

 private:
  const int kWindowWidth = 1200;
  const int kWindowHeight = 800;
  const int kWindowMarginX = 360;
  const int kWindowMarginY = 140;
  const int kEasyDifficulty = 0;
  const int kMediumDifficulty = 1;
  const int kHardDifficulty = 2;
  BreakoutGame breakout_game_ = BreakoutGame(float (kWindowWidth), float (kWindowHeight));
  Menu menu_;
  const cinder::Font menu_title_font = cinder::Font("calibri", 48);
  const cinder::Font button_font = cinder::Font("calibri", 36);
  const bool kAddTextures = true;
  bool on_menu_;
  bool on_leaderboard_;
  bool on_game_;


 public:
  BreakoutApp();
  void draw() override;
  void update() override;
  void mouseDown(ci::app::MouseEvent event) override;
  void mouseDrag(ci::app::MouseEvent event) override;
  void keyDown(ci::app::KeyEvent event) override;
};


} // namespace breakout