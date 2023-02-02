#include "menu.h"

namespace breakout {

Menu::Menu() {
}

Menu::Menu(const string &title, const vec2 &title_location,
           const cinder::Font &font){
    title_ = title;
    title_location_ = title_location;
}

void Menu::AddButton(const string &name, const vec2 &top_left,
                     const vec2 &bottom_right, const cinder::Font &font) {
  Button button;
  button.label_ = name;
  button.location_ = Rectf(top_left, bottom_right);
  buttons_.push_back(button);
}

void Menu::Draw(const cinder::Font &title_font, const cinder::Font &button_font)
    const {
  ci::gl::drawStringCentered(title_, title_location_, "white",
                             title_font);
  for (size_t i = 0; i < buttons_.size(); i++) {
    Button button = buttons_[i];
    vec2 button_center = button.location_.getCenter();
    ci::gl::drawStringCentered(button.label_, button_center, "white",
                               button_font);
    ci::gl::color(ci::Color("white"));
    ci::gl::drawStrokedRect(button.location_);
  }
}

bool Menu::ButtonPressed(const string &button_name, const vec2& mouse_location)
{
  for (size_t i = 0; i < buttons_.size(); i++) {
    float button_top = buttons_[i].location_.getY1();
    float button_bottom = buttons_[i].location_.getY2();
    float button_left = buttons_[i].location_.getX1();
    float button_right = buttons_[i].location_.getX2();
    if (mouse_location.x > button_left && mouse_location.x < button_right
        && mouse_location.y > button_top && mouse_location.y < button_bottom
        && buttons_[i].label_ == button_name) {
      std::cout << "yes" << std::endl;
      return true;
    }
  }

  return false;
}

}  //  namespace breakout