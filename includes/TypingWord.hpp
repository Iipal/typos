#pragma once
#include "typos.hpp"

class TypingWord {
public:
  TypingWord();
  TypingWord(int y, int x, std::string str);
  virtual ~TypingWord();

  bool is_ok(void);
  void validate(void);

  const TypingChar *get_chars(void) const;
  const size_t &get_length(void) const;

  TypingChar &get_char_at(void) const;
  TypingChar &get_char_at(size_t pos) const;

  const size_t &get_current_pos(void) const;
  void inc_current_pos(void);
  void dec_current_pos(void);
  void set_pos(size_t pos);

  const color_t &get_color(void) const;
  void set_color(color_t color);

  color_t get_color_at(void) const;
  color_t get_color_at(size_t at_pos) const;
  void set_color_at(color_t color);
  void set_color_at(color_t color, size_t at_pos);

  std::string to_str(void) const;

private:
  TypingChar *chars;
  size_t pos;
  size_t length;
  color_t color;
};
