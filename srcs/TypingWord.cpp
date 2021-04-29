#include "typos.hpp"

TypingWord::TypingWord() {}
TypingWord::TypingWord(std::string word_string)
    : string(word_string.c_str()), at_pos_colors(NULL), pos(0),
      length(word_string.length()), string_color(COLORIZE_DEFAULT) {
  const size_t word_length = word_string.length();
  this->at_pos_colors = new color_t[word_length];
  for (size_t i = 0; word_length > i; ++i) {
    this->at_pos_colors[i] = COLORIZE_DEFAULT;
  }
}
TypingWord::~TypingWord() {
  if (this->at_pos_colors) {
    delete[] this->at_pos_colors;
  }
}

bool TypingWord::is_ok(void) {
  for (size_t i = 0; this->length > i; ++i) {
    color_t at_color = this->at_pos_colors[i];
    if (COLORIZE_WARN == at_color || COLORIZE_ERROR == at_color) {
      return false;
    }
  }

  return true;
}
void TypingWord::validate(void) {
  this->string_color = this->is_ok() ? COLORIZE_OK : COLORIZE_ERROR;
}

const std::string &TypingWord::get_string(void) const { return this->string; }
const size_t &TypingWord::get_length(void) const { return this->length; }

const char &TypingWord::get_char(void) const { return this->string[this->pos]; }
const char &TypingWord::get_char(size_t pos) const { return this->string[pos]; }

const size_t &TypingWord::get_current_pos(void) const { return this->pos; }
void TypingWord::inc_current_pos(void) { ++this->pos; }
void TypingWord::dec_current_pos(void) {
  if (0 != this->pos)
    --this->pos;
}
void TypingWord::set_pos(size_t pos) { this->pos = pos; }

const color_t &TypingWord::get_color(void) const { return this->string_color; }
void TypingWord::set_color(color_t color) { this->string_color = color; }

const color_t &TypingWord::get_color_at(void) const {
  return this->at_pos_colors[this->pos];
}
const color_t &TypingWord::get_color_at(size_t at_pos) const {
  return this->at_pos_colors[at_pos];
}

void TypingWord::set_color_at(color_t color) {
  this->at_pos_colors[this->pos] = color;
}
void TypingWord::set_color_at(color_t color, size_t at_pos) {
  this->at_pos_colors[at_pos] = color;
}
