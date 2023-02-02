#include "platform.h"

namespace breakout {

Platform::Platform() {
}

Platform::Platform(const vec2& starting_location, const float width,
                   const float height, const Color& color) {
  vec2 top_left = vec2(starting_location.x - (width / 2),
                       starting_location.y - height);
  vec2 bottom_right = vec2(starting_location.x + (width / 2),
                           starting_location.y);
  entire_location_ = Rectf(top_left, bottom_right);
  width_ = width;
  height_ = height;
  color_ = color;
}

Platform::Platform(const vec2& starting_location, const float width,
                   const float height, const Color& color,
                   const string& texture_path) {
  vec2 top_left = vec2(starting_location.x - (width / 2),
                       starting_location.y - height);
  vec2 bottom_right = vec2(starting_location.x + (width / 2),
                           starting_location.y);
  entire_location_ = Rectf(top_left, bottom_right);
  width_ = width;
  height_ = height;
  color_ = color;
  auto img = cinder::loadImage(texture_path);
  texture_ = ci::gl::Texture2d::create(img);
}

const Rectf& Platform::GetLocation() const {
  return entire_location_;
}

void Platform::SetLocation(const Rectf& location) {
  entire_location_ = location;
}

void Platform::Draw() const {
  ci::gl::color(ci::Color(color_));
  ci::gl::draw(texture_, entire_location_);
}

void Platform::MoveRightKey(const float right_edge) {

  /* if movement will put platform past right edge, then only move it enough to
   * be at the right edge */
  if (entire_location_.getX2() + kKeyMovement > right_edge) {
    float movement = right_edge - entire_location_.getX2();
    entire_location_ = entire_location_ + Rectf(vec2(movement, 0),
                                                vec2(movement, 0));
  } else {
    entire_location_ = entire_location_ + Rectf(vec2(kKeyMovement, 0),
                                                vec2(kKeyMovement, 0));
  }
}

void Platform::MoveLeftKey(const float left_edge) {

  /* if movement will put platform past left edge, then only move it enough to
   * be at the left edge */
  if (entire_location_.getX1() - kKeyMovement < left_edge) {
    float movement = entire_location_.getX1() - left_edge;
    entire_location_ = entire_location_ + Rectf(vec2(-movement, 0),
                                                vec2(-movement, 0));
  } else {
    entire_location_ = entire_location_ + Rectf(vec2(-kKeyMovement, 0),
                                                vec2(-kKeyMovement, 0));
  }
}

void Platform::MoveWithMouse(const vec2& mouse_location, const float left_edge,
                             const float right_edge) {
  float platform_left_x = mouse_location.x - (width_/2);
  float platform_right_x = mouse_location.x + (width_/2);
  Rectf new_position;

  // if mouse is past right border, make sure platform is located at very edge
  if (platform_left_x < left_edge) {
    new_position =
        Rectf(vec2(left_edge, entire_location_.getY1()),
              vec2(left_edge + width_, entire_location_.getY2()));

  // if mouse is past left border, make sure platform is located at very edge
  } else if (platform_right_x > right_edge) {
    new_position =
        Rectf(vec2(right_edge - width_, entire_location_.getY1()),
              vec2(right_edge, entire_location_.getY2()));

  // otherwise, have platform center follow the mouse
  } else {
    new_position =
        Rectf(vec2(platform_left_x, entire_location_.getY1()),
              vec2(platform_right_x, entire_location_.getY2()));
  }

  entire_location_ = new_position;
}


}  // namespace breakout