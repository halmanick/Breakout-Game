#include "ball.h"

namespace breakout {

Ball::Ball() {
}

Ball::Ball(const float radius, const Color& color, const vec2& position,
           const vec2& velocity) {
  radius_ = radius;
  color_ = color;
  position_ = position;
  velocity_ = velocity;
}

const float Ball::GetRadius() const {
  return radius_;
}

const vec2& Ball::GetPosition() const {
  return position_;
}

void Ball::SetPosition(const vec2& position) {
  position_ = position;
}

const vec2& Ball::GetVelocity() const {
  return velocity_;
}

void Ball::SetVelocity(const vec2& velocity) {
  velocity_ = velocity;
}

void Ball::Draw() const {
  ci::gl::color(ci::Color(color_));
  ci::gl::drawSolidCircle(position_, radius_);
}

void Ball::UpdatePosition() {
  position_ += velocity_;
}

void Ball::UpdateVelocityOnPlatformCollision(const Rectf& platform_location) {
  float platform_top = platform_location.getY1();
  if (position_.y + radius_ >= platform_top &&
      position_.x > platform_location.getX1() &&
      position_.x < platform_location.getX2()) {

    /* adds influence to ball speed depending on position of collision relative
     * to the center of the platform */
    float platform_center_x = platform_location.getCenter().x;
    float platform_width = platform_location.getWidth();
    float pos_relative_to_center = (position_.x - platform_center_x) /
                                   (platform_width / 2);
    float speed = length(velocity_);
    velocity_.x = speed * pos_relative_to_center * ball_speed_influence;
    velocity_.y = sqrt(pow(speed, 2) - pow(velocity_.x, 2))
                  * (velocity_.y > 0? -1 : 1);
  }
}

bool Ball::CollideWithBrick(const Rectf& brick_location) {
  float top = brick_location.getY1();
  float bottom = brick_location.getY2();
  float left = brick_location.getX1();
  float right = brick_location.getX2();
  if ((abs(position_.x - left) <= radius_) &&
      (position_.y > top && position_.y < bottom)) {
    velocity_ = vec2(-velocity_.x, velocity_.y);
    return true;
  }

  if ((abs(position_.x - right) <= radius_) &&
      (position_.y > top && position_.y < bottom)) {
    velocity_ = vec2(-velocity_.x, velocity_.y);
    return true;
  }

  if ((abs(position_.y - top) <= radius_) &&
      (position_.x >= left && position_.x <= right)) {
    velocity_ = vec2(velocity_.x, -velocity_.y);
    return true;
  }

  if ((abs(position_.y - bottom) <= radius_) &&
      (position_.x >= left && position_.x <= right)) {
    velocity_ = vec2(velocity_.x, -velocity_.y);
    return true;
  }

  return false;
}

void Ball::UpdateVelocityOnWallCollisions(const float top, const float bottom,
                                          const float left, const float right) {
  if (position_.y - radius_ <= top) {
    velocity_.y = -velocity_.y;
  }

  if (position_.y + radius_ >= bottom) {
    velocity_ = vec2();
  }

  if ((position_.x - radius_ <= left) | (position_.x + radius_ >= right)) {
    velocity_.x = -velocity_.x;
  }
}

bool Ball::ReachedBottom(const float bottom) const {
  return (position_.y + radius_ >= bottom);
}

}  //  namespace breakout