#pragma once
#include "typos.hpp"
#include "Colorize.hpp"
#include "TypingChar.hpp"

class TypingWord {
public:
  constexpr TypingWord()
      : _chars(NULL), _pos(0), _length(), _color(Colorize::COLORIZE_DEFAULT) {
    ;
  }
  constexpr TypingWord(int y, int x, std::string_view str)
      : _pos(0), _length(str.length()), _color(Colorize::COLORIZE_DEFAULT) {
    const size_t len = str.length();
    _chars           = new TypingChar *[len + 1];

    for (size_t i = 0; len >= i; ++i) {
      _chars[i] = new TypingChar(y, x + i, str[i]);
    }
  }
  constexpr ~TypingWord() {
    if (_chars) {
      delete[] _chars;
    }
  }

  bool is_ok(void) const {
    for (size_t i = 0; _length > i; ++i) {
      const Colorize::color_t at_color = _chars[i]->clr();
      if (Colorize::COLORIZE_WARN == at_color || Colorize::COLORIZE_ERROR == at_color) {
        return false;
      }
    }

    return true;
  }
  void validate(void) {
    _color = is_ok() ? Colorize::COLORIZE_OK : Colorize::COLORIZE_ERROR;
  }

  constexpr TypingChar ** get_chars(void) const { return _chars; }

  constexpr const size_t & get_length(void) const { return _length; }

  constexpr TypingChar * get_char_at(size_t pos) const { return get_chars()[pos]; }
  constexpr TypingChar * get_char_at(void) const {
    return get_char_at(get_current_pos());
  }

  constexpr size_t get_current_pos(void) const { return _pos; }

  constexpr void inc_current_pos(void) { ++_pos; }
  constexpr void dec_current_pos(void) {
    if (0 != _pos) {
      --_pos;
    }
  }

  constexpr Colorize::color_t get_color(void) const { return _color; }
  constexpr void              set_color(const Colorize::color_t color) { _color = color; }

  constexpr Colorize::color_t get_color_at(const size_t at_pos) const {
    return get_chars()[at_pos]->clr();
  }
  constexpr Colorize::color_t get_color_at(void) const {
    return get_color_at(get_current_pos());
  }

  void set_pos(const size_t & pos) { _pos = pos; }

  void set_color_at(const Colorize::color_t & color, const size_t & at_pos) {
    get_chars()[at_pos]->set_color(color);
  }
  void set_color_at(const Colorize::color_t & color) {
    set_color_at(color, get_current_pos());
  }

  std::string to_str(void) const {
    char word_chars[128] = {0};

    for (size_t i = 0; _length > i && sizeof(word_chars) - 1 > i; ++i) {
      word_chars[i] = _chars[i]->ch();
    }

    std::string out(word_chars);

    return out;
  }

private:
  TypingChar **     _chars;
  size_t            _pos;
  size_t            _length;
  Colorize::color_t _color;
};
