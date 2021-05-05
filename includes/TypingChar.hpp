#pragma once
#include "TypingKeys.hpp"
#include "Colorize.hpp"

class TypingChar {
public:
  constexpr TypingChar() : _y(0), _x(0), _ch(0), _clr(Colorize::COLORIZE_DEFAULT) {}
  constexpr TypingChar(const int & y, const int & x, const TypingKeys::key_t & ch)
      : _y(y), _x(x), _ch(ch), _clr(Colorize::COLORIZE_DEFAULT) {
    ;
  }

  constexpr int         get_y(void) { return _y; };
  constexpr int         y(void) { return get_y(); };
  constexpr int const & get_y(void) const { return _y; };
  constexpr int const & y(void) const { return get_y(); };

  constexpr int         get_x(void) { return _x; };
  constexpr int         x(void) { return get_x(); };
  constexpr int const & get_x(void) const { return _x; };
  constexpr int const & x(void) const { return get_x(); };

  constexpr TypingKeys::key_t         get_char(void) { return _ch; };
  constexpr TypingKeys::key_t         ch(void) { return get_char(); };
  constexpr TypingKeys::key_t const & get_char(void) const { return _ch; };
  constexpr TypingKeys::key_t const & ch(void) const { return get_char(); };

  constexpr Colorize::color_t         get_color(void) { return _clr; };
  constexpr Colorize::color_t         clr(void) { return get_color(); };
  constexpr Colorize::color_t const & get_color(void) const { return _clr; };
  constexpr Colorize::color_t const & clr(void) const { return get_color(); };

  void set_color(const Colorize::color_t & clr) { _clr = clr; };

protected:
  const int               _y;
  const int               _x;
  const TypingKeys::key_t _ch;
  Colorize::color_t       _clr;
};
