#pragma once
#include "typos.hpp"

class TypingChar {
public:
  TypingChar();
  TypingChar(int y, int x, chtype ch);
  virtual ~TypingChar();

  operator chtype() const;
  operator char() const;
  operator color_t() const;

  int get_screen_y(void) const;
  int get_screen_x(void) const;
  chtype get_char(void) const;

  color_t get_color(void) const;
  void set_color(color_t clr);

private:
  int screen_y;
  int screen_x;
  chtype ch;
  color_t clr;
};
