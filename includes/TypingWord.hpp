#pragma once
#include "typos.hpp"

class TypingWord {
public:
  TypingWord();
  TypingWord(std::string word_string);
  virtual ~TypingWord();

  bool is_ok(void);
  void validate(void);

  const std::string &get_string(void) const;
  const size_t &get_length(void) const;

  const char &get_char(void) const;
  const char &get_char(size_t pos) const;

  const size_t &get_current_pos(void) const;
  void inc_current_pos(void);
  void dec_current_pos(void);
  void set_pos(size_t pos);

  const color_t &get_color(void) const;
  void set_color(color_t color);

  const color_t &get_color_at(void) const;
  const color_t &get_color_at(size_t at_pos) const;
  void set_color_at(color_t color);
  void set_color_at(color_t color, size_t at_pos);

private:
  std::string string;
  color_t *at_pos_colors;
  size_t pos;
  size_t length;
  color_t string_color;
};
