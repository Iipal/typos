#pragma once
#include "typos.hpp"

class Print {
public:
  static void render_all(const Typing &text);
  static void render_all(const Typing &text, int input);

  static void text(const Typing &text);
  static void text_delimiter(void);

  static void timer(int seconds);
  static void input_word(const TypingWord *const word, int input);

  static void stats(void);

#ifdef TYPOS_DEBUG
  static void status(const char ch, const bool is_ok);
#endif

  static void clean_prev_word(const TypingWord *const word);
  static void clean_line(int y);

  static int get_text_x(void);
  static int get_text_y(void);
  static int inc_text_y(void);
  static int reset_text_y(void);

  static int get_text_delimiter_y(void);

  static int get_timer_y(void);
  static int get_timer_x(void);

  static int get_input_y(void);

  static int get_stats_y(void);

#ifdef TYPOS_DEBUG
  static int get_info_y(void);
  static int get_info_x(void);
#endif

  static int get_center_x(size_t text_len);

private:
  Print();

  static const int _text_y_default = 1;
  static int _text_y;
  static int _text_x;

  static const int _input_shift_y = 2;
  static const int _timer_shift_y = _input_shift_y;
  static const int _timer_x = 5;

  static const int _stats_shift_y = 3;

#ifdef TYPOS_DEBUG
  static const int _info_shift_y = 2;
  static const int _info_x = 1;
#endif
};
