#pragma once

#include "cinder/gl/gl.h"

using glm::vec2;
using cinder::Rectf;
using ci::Color;
using std::string;

namespace breakout {

/**
 * A class to represent a ball in the Breakout game
 */
class Ball {
 private:
  float radius_;
  Color color_;
  vec2 position_;
  vec2 velocity_;
  static constexpr float ball_speed_influence = 0.75f;

 public:
  /**
   * default constructor for ball
   */
  Ball();

  /**
   * constructs a ball, given a radius, color, position, and velocity
   * @param radius of ball
   * @param color of ball
   * @param position of ball
   * @param velocity of ball
   */
  Ball(const float radius, const Color& color, const vec2& position,
       const vec2& velocity);

  /**
   * getter for the radius of the ball
   * @return radius
   */
  const float GetRadius() const;

  /**
   * getter for position of ball
   * @return position of ball
   */
  const vec2& GetPosition() const;

  /**
   * setter for position
   * @param position to set
   */
  void SetPosition(const vec2& position);

  /**
   * getter for velocity of ball
   * @return velocity of ball
   */
  const vec2& GetVelocity() const;

  /**
   * setter for velocity of ball
   * @param velocity
   */
  void SetVelocity(const vec2& velocity);

  /**
   * method to draw ball
   */
  void Draw() const;

  /**
   * updates the position of the ball for next frame
   */
  void UpdatePosition();

  /**
   * checks if the ball is going to collide with a platform, and updates velocity
   * @param platform_location
   */
  void UpdateVelocityOnPlatformCollision(const Rectf& platform_location);

  /**
   * returns true and updates velocity on collision with brick
   * @param brick_location
   * @return true on collision, false otherwise
   */
  bool CollideWithBrick(const Rectf& brick_location);

  /**
   * checks for collision with walls, and updates velocity accordingly
   * @param top wall of game
   * @param bottom wall of game
   * @param left wall of game
   * @param right wall of game
   */
  void UpdateVelocityOnWallCollisions(const float top, const float bottom, const float left, const float right);

  /**
   * method that checks if ball has reached the bottom of game
   * @param bottom of game
   * @return true if reached bottom
   */
  bool ReachedBottom(const float bottom) const;
};


}  // namespace breakout