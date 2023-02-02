#include <catch2/catch.hpp>
#include "ball.h"

using namespace breakout;

TEST_CASE("Testing wall collisions") {
  Ball ball = Ball(1, "green", vec2(), vec2());
  const float kTopWall = 0;
  const float kRightWall = 20;
  const float kBottomWall = 20;
  const float kLeftWall = 0;
  SECTION("No wall collisions") {
    ball.SetPosition(vec2(5, 5));
    vec2 ball_velocity = vec2(1, 1);
    ball.SetVelocity(ball_velocity);
    ball.UpdateVelocityOnWallCollisions(kTopWall, kBottomWall, kLeftWall, kRightWall);
    REQUIRE(ball.GetVelocity() == ball_velocity);
  }

  SECTION("Top wall collision") {
    ball.SetPosition(vec2(5, 2));
    ball.SetVelocity(vec2(0, -1));
    ball.UpdatePosition();
    ball.UpdateVelocityOnWallCollisions(kTopWall, kBottomWall, kLeftWall, kRightWall);
    REQUIRE(ball.GetVelocity() == vec2(0, 1));
  }

  SECTION("Bottom wall collision") {
    ball.SetPosition(vec2(5, 18));
    ball.SetVelocity(vec2(0, 1));
    ball.UpdatePosition();
    ball.UpdateVelocityOnWallCollisions(kTopWall, kBottomWall, kLeftWall, kRightWall);

    // ball is supoosed to stop moving when hits ground
    REQUIRE(ball.GetVelocity() == vec2());
  }

  SECTION("Left wall collision") {
    ball.SetPosition(vec2(2, 2));
    ball.SetVelocity(vec2(-1, 0));
    ball.UpdatePosition();
    ball.UpdateVelocityOnWallCollisions(kTopWall, kBottomWall, kLeftWall, kRightWall);
    REQUIRE(ball.GetVelocity() == vec2(1, 0));
  }

  SECTION("Right wall collision") {
    ball.SetPosition(vec2(18, 2));
    ball.SetVelocity(vec2(1, 0));
    ball.UpdatePosition();
    ball.UpdateVelocityOnWallCollisions(kTopWall, kBottomWall, kLeftWall, kRightWall);
    REQUIRE(ball.GetVelocity() == vec2(-1, 0));
  }
}

TEST_CASE("Testing platform collisions") {
  const Rectf platform_location = Rectf(vec2(4, 6), vec2(8, 8));
  Ball ball = Ball(1, "green", vec2(), vec2());
  SECTION("Ball not colliding with platform") {
    vec2 ball_velocity = vec2(1, 1);
    ball.SetVelocity(ball_velocity);
    ball.UpdateVelocityOnPlatformCollision(platform_location);
    REQUIRE(ball.GetVelocity() == ball_velocity);
  }

  SECTION("Testing center of platform collision") {
    ball.SetPosition(vec2(9, 2));
    vec2 ball_velocity = vec2(-3, 4);
    ball.SetVelocity(ball_velocity);
    ball.UpdatePosition();
    ball.UpdateVelocityOnPlatformCollision(platform_location);
    REQUIRE(ball.GetVelocity() == vec2(0, -5));
    REQUIRE(length(ball.GetVelocity()) == length(ball_velocity));
  }

  SECTION("Testing left side") {
    ball.SetPosition(vec2(5, 8));
    vec2 ball_velocity = vec2(0, -1);
    ball.SetVelocity(ball_velocity);
    ball.UpdatePosition();
    ball.UpdateVelocityOnPlatformCollision(platform_location);
    REQUIRE(ball.GetVelocity().x == Approx(-0.375));
    REQUIRE(ball.GetVelocity().y == Approx(0.92702));
    REQUIRE(length(ball.GetVelocity()) == Approx(length(ball_velocity)));
  }

  SECTION("Testing right side") {
    ball.SetPosition(vec2(7, 8));
    vec2 ball_velocity = vec2(0, -1);
    ball.SetVelocity(ball_velocity);
    ball.UpdatePosition();
    ball.UpdateVelocityOnPlatformCollision(platform_location);
    REQUIRE(ball.GetVelocity().x == Approx(0.375));
    REQUIRE(ball.GetVelocity().y == Approx(0.92702));
    REQUIRE(length(ball.GetVelocity()) == Approx(length(ball_velocity)));
  }
}

TEST_CASE("Testing brick collisions") {
  const Rectf brick_location = Rectf(vec2(4, 6), vec2(8, 8));
  Ball ball = Ball(1, "green", vec2(), vec2());
  SECTION("No brick collisions") {
    vec2 ball_velocity = vec2(1, 1);
    ball.SetVelocity(ball_velocity);
    REQUIRE(ball.CollideWithBrick(brick_location) == false);
    REQUIRE(ball.GetVelocity() == ball_velocity);
  }

  SECTION("Top side of brick collision") {
    ball.SetPosition(vec2(5, 4));
    vec2 ball_velocity = vec2(0, 1);
    ball.SetVelocity(ball_velocity);
    ball.UpdatePosition();
    REQUIRE(ball.CollideWithBrick(brick_location));
    REQUIRE(ball.GetVelocity() == vec2(ball_velocity.x, -ball_velocity.y));
  }

  SECTION("Bottom side of brick collision") {
    ball.SetPosition(vec2(5, 10));
    vec2 ball_velocity = vec2(0, -1);
    ball.SetVelocity(ball_velocity);
    ball.UpdatePosition();
    REQUIRE(ball.CollideWithBrick(brick_location));
    REQUIRE(ball.GetVelocity() == vec2(ball_velocity.x, -ball_velocity.y));
  }

  SECTION("Left side of brick collision") {
    ball.SetPosition(vec2(2, 7));
    vec2 ball_velocity = vec2(1, 0);
    ball.SetVelocity(ball_velocity);
    ball.UpdatePosition();
    REQUIRE(ball.CollideWithBrick(brick_location));
    REQUIRE(ball.GetVelocity() == vec2(-ball_velocity.x, ball_velocity.y));
  }

  SECTION("Right side of brick collision") {
    ball.SetPosition(vec2(10, 7));
    vec2 ball_velocity = vec2(-1, 0);
    ball.SetVelocity(ball_velocity);
    ball.UpdatePosition();
    REQUIRE(ball.CollideWithBrick(brick_location));
    REQUIRE(ball.GetVelocity() == vec2(-ball_velocity.x, ball_velocity.y));
  }
}