#pragma once
#include "typos.hpp"

class Typing : public TypingStats {
public:
  static int const KEY_DEL = 0x7F;
  static int const KEY_ESC = 0x1B;
  static int const KEY_NEW_LINE = 0x0A;
  static int const KEY_SPACE_BAR = 0x20;

  Typing();
  Typing(const std::string *strings, size_t strings_length);
  virtual ~Typing();

  static int get_input();

  void iterate(void);
  void backspace(void);
  bool validate_input(int input);
  bool validate_input(int input, TypingWord *word);

  void reset(void);

  TypingWord **get_words(void) const;
  size_t get_words_length(void) const;
  size_t get_current_word_pos(void) const;
  TypingWord *get_word(void) const;
  TypingWord *get_word(size_t pos) const;

private:
  TypingWord **words;
  size_t length;
  size_t current_word_pos;
};

extern Typing *g_Typing;
