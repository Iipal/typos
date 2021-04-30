#include "typos.hpp"

TypingChar::TypingChar() {}
TypingChar::TypingChar(int y, int x, chtype ch)
    : screen_y(y), screen_x(x), ch(ch), clr(COLORIZE_DEFAULT) {}
TypingChar::~TypingChar() {}

TypingChar::operator chtype() const { return this->ch; }
TypingChar::operator char() const { return (char)this->ch; }
TypingChar::operator color_t() const { return this->clr; }

int TypingChar::get_screen_y(void) const { return this->screen_y; }
int TypingChar::get_screen_x(void) const { return this->screen_x; }
chtype TypingChar::get_char(void) const { return this->ch; }

color_t TypingChar::get_color(void) const { return this->clr; }
void TypingChar::set_color(color_t clr) { this->clr = clr; }
