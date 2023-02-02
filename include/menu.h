#pragma once

#include <string>
#include <vector>
#include "cinder/gl/gl.h"

using std::string;
using std::vector;
using cinder::Rectf;
using glm::vec2;

namespace breakout {

/**
 * Struct to hold buttons in menu, contains location and label
 */
struct Button {
  Rectf location_;
  string label_;
};

/**
 * Class to hold menu
 */
class Menu {
 private:
  string title_;
  vec2 title_location_;
  vector<Button> buttons_;

 public:
  /**
   * default constructor
   */
  Menu();

  /**
   * constructs a menu given a title, location of title, and font
   * @param title for menu
   * @param title_location for title
   * @param font for title
   */
  Menu(const string& title, const vec2& title_location,
       const cinder::Font& font);

  /**
   * method that adds a button given a name, top left position,
   * bottom right position, and font
   */
  void AddButton(const string& name, const vec2& top_left,
                 const vec2& bottom_right, const cinder::Font& font);

  /**
   * method that draws the menu
   * @param title_font of title
   * @param button_font of button
   */
  void Draw(const cinder::Font& title_font, const cinder::Font& button_font)
      const;

  /**
   * checks if a button is pressed given button name and mouse location
   * @param button_name
   * @param mouse_location
   * @return true if button is pressed
   */
  bool ButtonPressed(const string& button_name, const vec2& mouse_location);

};


}  //  namespace breakout