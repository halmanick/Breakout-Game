#include <catch2/catch.hpp>
#include "breakout_game.h"

using namespace breakout;

const float kGameWidth = 1200;
const float kGameHeight = 800;
const bool kAddTextures = false;
const int kGameDifficulty = 0;
const float kPlatformHeight = 10;

TEST_CASE("Testing new game") {
  BreakoutGame game = BreakoutGame(kGameWidth, kGameHeight);
  SECTION("Checking level is set up") {
    game.StartNewGame(kAddTextures, kGameDifficulty);
    REQUIRE(game.GetLevel() == 1);
  }

  SECTION("Checking platform location") {
    game.StartNewGame(kAddTextures, kGameDifficulty);
    REQUIRE(game.GetPlatform().GetLocation().getCenter() == vec2(kGameWidth / 2, kGameHeight - (kPlatformHeight / 2)));
  }

  SECTION("Checking ball location") {
    game.StartNewGame(kAddTextures, kGameDifficulty);
    vec2 platform_start_location_ = vec2(kGameWidth / 2, kGameHeight);
    vec2 ball_starting_location =
        vec2(platform_start_location_.x, platform_start_location_.y - 3 * kPlatformHeight);
    REQUIRE(game.GetBall().GetPosition() == ball_starting_location);
  }

  SECTION("Checking correct amount of bricks") {
    game.StartNewGame(kAddTextures, kGameDifficulty);
    REQUIRE(game.GetBricks().size() == 70);
  }
}

TEST_CASE("Testing Update Frame") {
  const vec2 kBallStartingSpeed = vec2(0, -6);
  BreakoutGame game = BreakoutGame(kGameWidth, kGameHeight);
  SECTION("Test that ball doesn't move when until platform moves") {
    game.StartNewGame(kAddTextures, kGameDifficulty);
    game.UpdateFrame(kAddTextures);
    REQUIRE(game.GetBall().GetVelocity() == vec2());
  }

  SECTION("Test that ball moves when platform location changes") {
    // imitate moving platform with mouse to the right
    Rectf platform_location = Rectf(vec2(510, 790), vec2(710, 790));
    game.StartNewGame(kAddTextures, kGameDifficulty);
    game.SetPlatformLocation(platform_location);
    game.UpdateFrame(kAddTextures);
    REQUIRE(game.GetBall().GetVelocity() == kBallStartingSpeed);
  }

  SECTION("Test that brick gets removed once ball hits it") {
    Rectf platform_location = Rectf(vec2(510, 790), vec2(710, 790));
    game.StartNewGame(kAddTextures, kGameDifficulty);
    game.SetPlatformLocation(platform_location);
    while (game.GetBricks().size() == 70) {
      game.UpdateFrame(kAddTextures);
    }

    REQUIRE(game.GetBricks().size() == 69);
  }

  SECTION("Testing for end of level") {
    Rectf platform_location = Rectf(vec2(510, 790), vec2(710, 790));
    game.StartNewGame(kAddTextures, kGameDifficulty);
    game.SetPlatformLocation(platform_location);
    game.RemoveBricks();
    game.UpdateFrame(kAddTextures);

    //  check that level increases
    REQUIRE(game.GetLevel() == 2);

    //  make sure bricks get reset
    REQUIRE(game.GetBricks().size() == 70);

    //  make sure ball speed increases when platform moves again
    platform_location = Rectf(vec2(520, 790), vec2(720, 790));
    game.SetPlatformLocation(platform_location);
    game.UpdateFrame(kAddTextures);
    REQUIRE(length(game.GetBall().GetVelocity()) > length(kBallStartingSpeed));
  }

  SECTION("Testing game over") {
    game.StartNewGame(kAddTextures, kGameDifficulty);
    game.SetPlayerLives(-1);
    REQUIRE(game.GameOver());
  }
}