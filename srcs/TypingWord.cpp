#include "typos.hpp"

TypingWord::TypingWord() {}
TypingWord::TypingWord(int y, int x, std::string_view str)
    : pos(0), length(str.length()), color(COLORIZE_DEFAULT) {

  const size_t word_length = str.length();
  this->chars = new TypingChar[word_length + 1];

  for (size_t i = 0; word_length >= i; ++i) {
    this->chars[i] = TypingChar(y, x + i, str[i]);
  }
}
TypingWord::~TypingWord() {
  if (this->chars) {
    delete[] this->chars;
  }
}

bool TypingWord::is_ok(void) {
  for (size_t i = 0; this->length > i; ++i) {
    const color_t at_color = this->chars[i];
    if (COLORIZE_WARN == at_color || COLORIZE_ERROR == at_color) {
      return false;
    }
  }

  return true;
}
void TypingWord::validate(void) {
  this->color = this->is_ok() ? COLORIZE_OK : COLORIZE_ERROR;
}

const TypingChar *TypingWord::get_chars(void) const { return this->chars; }
const size_t &TypingWord::get_length(void) const { return this->length; }

TypingChar &TypingWord::get_char_at(void) const {
  return this->get_char_at(this->pos);
}
TypingChar &TypingWord::get_char_at(size_t pos) const {
  return this->chars[pos];
}

const size_t &TypingWord::get_current_pos(void) const { return this->pos; }
void TypingWord::inc_current_pos(void) { ++this->pos; }
void TypingWord::dec_current_pos(void) {
  if (0 != this->pos)
    --this->pos;
}
void TypingWord::set_pos(size_t pos) { this->pos = pos; }

const color_t &TypingWord::get_color(void) const { return this->color; }
void TypingWord::set_color(color_t color) { this->color = color; }

color_t TypingWord::get_color_at(void) const {
  return this->get_color_at(this->pos);
}
color_t TypingWord::get_color_at(size_t at_pos) const {
  return this->chars[at_pos];
}

void TypingWord::set_color_at(color_t color) {
  this->set_color_at(color, this->pos);
}
void TypingWord::set_color_at(color_t color, size_t at_pos) {
  this->chars[at_pos].set_color(color);
}

std::string TypingWord::to_str(void) const {
  char word_chars[128] = {0};

  for (size_t i = 0; this->length > i; ++i) {
    word_chars[i] = this->chars[i];
  }

  std::string out(word_chars);

  return out;
}
