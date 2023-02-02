#include "brick.h"
#include <fstream>
#include <iostream>
using namespace std;


namespace breakout {

Brick::Brick() {
}

Brick::Brick(const Rectf& location, const Color& color, const int& score) {
  entire_location_ = location;
  color_ = color;
  score_ = score;
}


Brick::Brick(const Rectf& location, const Color& color,
             const string& texture_path, const int& score) {
  entire_location_ = location;
  color_ = color;
  score_ = score;
  auto img = cinder::loadImage(texture_path);
  texture_ = ci::gl::Texture2d::create(img);
}

const Rectf& Brick::GetLocation() const {
  return entire_location_;
}

const Color& Brick::GetColor() const {
  return color_;
}

const int& Brick::GetScore() const {
  return score_;
}

void Brick::Draw() const {
  ci::gl::color(ci::Color(color_));
  ci::gl::draw(texture_, entire_location_);
  ci::gl::color(ci::Color("black"));
  ci::gl::drawStrokedRect(entire_location_);
}

}  //  namespace breakout