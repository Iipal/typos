#pragma once
#include "typos.hpp"

class TypingChar {
public:
  TypingChar();
  TypingChar(int y, int x, char ch);
  virtual ~TypingChar();

  int get_screen_y(void) const;
  int get_screen_x(void) const;
  char get_char(void) const;

  color_t get_color(void) const;
  void set_color(color_t clr);

private:
  int screen_y;
  int screen_x;
  char ch;
  color_t clr;
};
