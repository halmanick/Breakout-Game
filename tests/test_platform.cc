#include <catch2/catch.hpp>
#include "platform.h"

using namespace breakout;

TEST_CASE("Testing platform constructor") {
  const float width = 4;
  const float height = 1;
  Platform platform = Platform(vec2(10, 1), width, height, "green");
  SECTION("Testing width") {
    REQUIRE(platform.GetLocation().getWidth() == width);
  }

  SECTION("Testing height") {
    REQUIRE(platform.GetLocation().getHeight() == height);
  }

  SECTION("Testing proper location") {
    REQUIRE(platform.GetLocation().getCenter() == vec2(10, height / 2));
  }
}

TEST_CASE("Testing platform key movement") {
  const float width = 4;
  const float height = 1;
  Platform platform = Platform(vec2(50, 1), width, height, "green");
  const float right_wall = 100;
  const float left_wall = 0;
  const float kKeyMovement = 40;
  vec2 previous_center = platform.GetLocation().getCenter();
  SECTION("Testing Right Key Movement") {
    platform.MoveRightKey(right_wall);
    REQUIRE(platform.GetLocation().getCenter() == previous_center + vec2(kKeyMovement, 0));
    REQUIRE(platform.GetLocation().getWidth() == width);
    REQUIRE(platform.GetLocation().getHeight() == height);
  }

  SECTION("Testing platform not going past right wall") {
    platform.MoveRightKey(right_wall);
    platform.MoveRightKey(right_wall);
    REQUIRE(platform.GetLocation().getCenter() == vec2(right_wall - (width / 2), height / 2));
    REQUIRE(platform.GetLocation().getWidth() == width);
    REQUIRE(platform.GetLocation().getHeight() == height);
  }

  SECTION("Testing Left Key Movement") {
    previous_center = platform.GetLocation().getCenter();
    platform.MoveLeftKey(left_wall);
    REQUIRE(platform.GetLocation().getCenter() == previous_center + vec2(-kKeyMovement, 0));
    REQUIRE(platform.GetLocation().getWidth() == width);
    REQUIRE(platform.GetLocation().getHeight() == height);
  }

  SECTION("Testing platform not going past left wall") {
    platform.MoveLeftKey(left_wall);
    platform.MoveLeftKey(left_wall);
    REQUIRE(platform.GetLocation().getCenter() == vec2(left_wall + (width / 2), height / 2));
    REQUIRE(platform.GetLocation().getWidth() == width);
    REQUIRE(platform.GetLocation().getHeight() == height);
  }
}

TEST_CASE("Testing platform moving with mouse") {
  const float width = 4;
  const float height = 1;
  Platform platform = Platform(vec2(50, 1), width, height, "green");
  const float right_wall = 100;
  const float left_wall = 0;
  const float kKeyMovement = 40;
  vec2 previous_center = platform.GetLocation().getCenter();
  SECTION("Test that center of platform follows location of mouse x coordinate") {
    platform.MoveWithMouse(vec2(80, 50), left_wall, right_wall);
    REQUIRE(platform.GetLocation().getCenter() == vec2(80, height / 2));
    REQUIRE(platform.GetLocation().getWidth() == width);
    REQUIRE(platform.GetLocation().getHeight() == height);
  }

  SECTION("Test that platform doesn't go past left wall") {
    platform.MoveWithMouse(vec2(-10, 40), left_wall, right_wall);
    REQUIRE(platform.GetLocation().getCenter() == vec2(left_wall + width / 2, height / 2));
    REQUIRE(platform.GetLocation().getWidth() == width);
    REQUIRE(platform.GetLocation().getHeight() == height);
  }

  SECTION("Test that platform doesn't go past right wall") {
    platform.MoveWithMouse(vec2(150, 40), left_wall, right_wall);
    REQUIRE(platform.GetLocation().getCenter() == vec2(right_wall - width / 2, height / 2));
    REQUIRE(platform.GetLocation().getWidth() == width);
    REQUIRE(platform.GetLocation().getHeight() == height);
  }
}