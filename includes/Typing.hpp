#pragma once
#include "typos.hpp"

class Typing : public TypingStats {
public:
  static int const KEY_DEL = KEY_BACKSPACE;
  static int const KEY_ESC = 0x1B;
  static int const KEY_NEW_LINE = 0x0A;
  static int const KEY_SPACE_BAR = 0x20;

  static int const KEY_ARROW_LEFT = KEY_LEFT;
  static int const KEY_ARROW_RIGHT = KEY_RIGHT;

  Typing();
  Typing(const std::string *strings, size_t strings_length);
  virtual ~Typing();

  static int get_input();
  static bool is_acceptable_input(int input);
  static bool is_functionality_input(int input);

  void iterate(void);
  void backspace(void);

  void move_to_next_ch(void);
  void move_to_prev_ch(void);

  bool validate_input(int input);
  bool validate_input(int input, TypingWord *word);

  void reset(void);

  TypingWord **get_words(void) const;
  size_t get_length(void) const;
  size_t get_current_word_pos(void) const;
  TypingWord *get_word(void) const;
  TypingWord *get_word(size_t pos) const;

private:
  TypingWord **words;
  size_t length;
  size_t current_word_pos;
};

extern Typing *g_Typing;
