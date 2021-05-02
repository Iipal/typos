#pragma once
#include "typos.hpp"

class Typing : public TypingStats {
public:
  Typing();
  Typing(const std::vector<std::string> strings, size_t strings_length);
  virtual ~Typing();

  void iterate(void);
  void backspace(void);

  void reset_word(void);

  void move_to_next_ch(void);
  void move_to_prev_ch(void);

  bool validate_input(int input);
  bool validate_input(int input, TypingWord *word);

  void reset(void);

  TypingWord **get_words(void) const;

  TypingWord *get_word(void) const;
  TypingWord *get_word(size_t pos) const;
  TypingWord *get_prev_word(void) const;
  TypingWord *get_next_word(void) const;

  size_t get_length(void) const;
  size_t get_current_word_pos(void) const;

private:
  TypingWord **words;
  size_t length;
  size_t current_word_pos;
};
