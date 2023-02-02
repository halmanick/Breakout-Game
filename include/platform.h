#pragma once

#include "cinder/gl/gl.h"

using glm::vec2;
using ci::Color;
using cinder::Rectf;
using std::string;

namespace breakout {

/**
 * A class to represent a platform in the Breakout game
 */
class Platform {
 private:

  // stores the entire location of platform as a Rectf object
  Rectf entire_location_;
  Color color_;
  float width_;
  float height_;
  ci::gl::Texture2dRef texture_;
  static constexpr float kKeyMovement = 40;

 public:
  /**
   * default constructor
   */
  Platform();

  /**
   * constructs a platform given a starting location of the center of the base
   * of the platform, with a given width, height, and color
   * @param starting_location_ of the center point of the base
   * @param width of platform
   * @param height of platform
   * @param color of platform
   */
  Platform(const vec2& starting_location_, const float width,
           const float height, const Color& color);

  /**
   * constructs a platform given a starting location of the center of the base
   * of the platform, with a given width, height, color, and path for texture
   * @param starting_location_ of the center point of the base
   * @param width of platform
   * @param height of platform
   * @param color of platform
   * @param texture_path for platform
   */
  Platform(const vec2& starting_location_, const float width,
           const float height, const Color& color, const string& texture_path);

  /**
   * getter for location of platform
   * @return location of platform
   */
  const Rectf& GetLocation() const;

  /**
   * setter for platform location used for testing
   * @param location to set platform at
   */
  void SetLocation(const Rectf& location);

  /**
   * method to draw platform
   */
  void Draw() const;

  /**
   * method that moves platform when right key is pressed
   * @param right_edge of the game
   */
  void MoveRightKey(const float right_edge);

  /**
   * method that moves platform when left key is pressed
   * @param left_edge of game
   */
  void MoveLeftKey(const float left_edge);

  /**
   * method that moves the platform to follow mouse location
   * @param mouse_location
   * @param left_edge of game
   * @param right_edge of game
   */
  void MoveWithMouse(const vec2& mouse_location, const float left_edge, const float right_edge);
};
}  // namespace breakout