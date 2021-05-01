#pragma once
#include "typos.hpp"

class Print {
public:
  static void current_char(const TypingChar &ch);
  static void current_char(const TypingChar &ch, unsigned attrs);
  static void clear_current_char(const TypingChar &ch);

  static void render_all(const Typing &text);

  static void text(const Typing &text);
  static void text(const Typing &text, size_t n_words);
  static void text_delimiter(void);

  static void timer(int seconds);
  static void input_word(const TypingWord *const word);

  static void stats(const TypingStatsData &data);

  static void clean_prev_word(const TypingWord *const word);
  static void clean_line(int y);
  static void clean_line(int y, int x);

  static int get_text_x(void);
  static int get_text_y(void);
  static int inc_text_y(void);
  static int reset_text_y(void);

  static int get_text_delimiter_y(void);

  static int get_timer_y(void);
  static int get_timer_x(void);

  static int get_input_y(void);

  static int get_stats_y(void);

  static int get_center_x(size_t text_len);

#ifdef TYPOS_DEBUG
  static void input_status(const Typing &text, const bool is_ok,
                           const int input);
  static void typing_status(const Typing &text);

  static int get_input_status_y(void);
  static int get_input_status_x(void);
#endif

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
  static const int _input_status_shift_y = 2;
  static const int _input_status_x = 1;
#endif
};
