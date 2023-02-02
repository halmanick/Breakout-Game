#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using glm::vec2;
using ci::Color;
using cinder::Rectf;
using std::string;

namespace breakout {

/**
 * A class to represent a brick in the Breakout game
 */
class Brick {
 private:
  Rectf entire_location_;
  Color color_;
  int score_;
  ci::gl::Texture2dRef texture_;

 public:
  /**
   * default constructor
   */
  Brick();

  /**
   * constructs a brick given a location, color, and score
   * @param location
   * @param color
   * @param score
   */
  Brick(const Rectf& location, const Color& color, const int& score);

  /**
   * constructs a brick given a location, color, texture path, and score
   * @param location
   * @param color
   * @param texture_path
   * @param score
   */
  Brick(const Rectf& location, const Color& color, const string& texture_path,
        const int& score);

  /**
   * getter for location of brick
   * @return brick location
   */
  const Rectf& GetLocation() const;

  /**
   * getter for color of brick
   * @return color of brick
   */
  const Color& GetColor() const;

  /**
   * getter for score associated with brick
   * @return score of brick
   */
  const int& GetScore() const;

  /**
   * method to draw brick
   */
  void Draw() const;
};

}  //  namespace breakout