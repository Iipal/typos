#include "typos.hpp"
#include <string.h>

int Print::_text_y = Print::_text_y_default;
int Print::_text_x = 1;

void Print::render_all(const Typing &text) { Print::render_all(text, 0); }
void Print::render_all(const Typing &text, int input) {
  Print::text(text);
  Print::text_delimiter();
  Print::input_word(text.get_word(), input);
}

void Print::text(const Typing &text) {
  curs_set(0);

  const size_t max_x = stdscr->_maxx - 2;

  TypingWord **words = text.get_words();
  const size_t current_word_pos = text.get_current_word_pos();
  const TypingWord *current_word = text.get_word();
  const size_t current_ch_pos = current_word->get_current_pos();

  Print::reset_text_y();

  for (size_t i = 0, start_print_pos_x = 0; words[i]; ++i) {
    const TypingWord *word = words[i];
    const std::string str = word->get_string();

    color_t clr = COLORIZE_DEFAULT;
    if (current_word_pos > i) {
      clr = word->get_color();
    } else if (current_word_pos == i) {
      clr = COLORIZE_INFO;
    }

    if (start_print_pos_x + word->get_length() > max_x) {
      Print::inc_text_y();
      start_print_pos_x = 0;
    }

    const int y = Print::get_text_y();
    const int x = Print::get_text_x();

    if (current_word_pos == i) {
      for (size_t i = 0; word->get_length() > i; ++i) {
        color_t current_ch_color = COLORIZE_DEFAULT;
        if (current_ch_pos == i) {
          current_ch_color = !str[i] ? COLORIZE_INFO_INVERT : COLORIZE_INFO;
        } else if (current_ch_pos > i) {
          current_ch_color = word->get_color_at(i);
        }

        Colorize::cmvaddch(current_ch_color, y, x + start_print_pos_x + i,
                           str[i] ? str[i] : ' ');
      }
    } else {
      Colorize::cmvprintw(clr, y, x + start_print_pos_x, "%s ", str.c_str());
    }

    start_print_pos_x += word->get_length() + 1;
  }
}

void Print::text_delimiter(void) {
  const int y = Print::get_text_delimiter_y();
  mvhline(y, 1, ACS_BSBS, stdscr->_maxx - 1);
}

void Print::clean_line(int y) {
  move(y, 1);
  clrtoeol();
}

void Print::clean_prev_word(const TypingWord *const word) {
  const int y = Print::get_input_y();
  const int x = Print::get_center_x(word ? word->get_length() : 30);

  move(y, x);
  clrtoeol();
  move(y + 1, x);
  clrtoeol();
}

void Print::timer(int seconds) {
  int min = seconds / 60;
  int sec = seconds % 60;
  int y = Print::get_timer_y();
  int x = Print::get_timer_x();

  Colorize::cmvprintw(COLORIZE_INFO, y, x, "%02d:%02d", min, sec);
  curs_set(0);
}

void Print::input_word(const TypingWord *const word, int input) {
  const size_t word_length = word ? word->get_length() : 12;
  const int y = Print::get_input_y();
  const int x = Print::get_center_x(word_length);

  if (!word) {
    Colorize::cmvprintw(COLORIZE_INFO, y, x, "end of words");
  } else {
    for (size_t i = 0; word_length > i; ++i) {
      Colorize::cmvaddch(word->get_color_at(i), y, x + i, word->get_char(i));
    }
  }

  mvhline(y + 1, x, ACS_BSBS, word ? word_length + 1 : 0);

  (void)input;
#ifdef TYPOS_DEBUG
  Colorize::cmvprintw(COLORIZE_INFO, y, x + (word ? word_length : 12),
                      " | last input: %3d:'%2c'", input, input ? input : ' ');
#endif

  move(y, x + (word ? word->get_current_pos() : 0));
  curs_set(1);
}

void Print::stats(void) {
  const char *msg1 = "YOU TIMED OUT";
  const char *msg2 = "Enter: Restart; Esc: Exit;";
  char buff[1024] = {0};

  snprintf(buff, sizeof(buff) - 1,
           "WPM: %.2f; CPM: %d; TYPOS: %d; ACC: %.2f %%", Stats::get_wpm(),
           Stats::get_cpm(), Stats::get_typos(), Stats::get_accuracy());

  const int y = Print::get_stats_y();

  Colorize::cmvprintw(COLORIZE_OK, y, Print::get_center_x(strlen(msg1)), msg1);
  Colorize::cmvprintw(COLORIZE_OK, y + 1, Print::get_center_x(strlen(buff)),
                      buff);
  Colorize::cmvprintw(COLORIZE_OK, y + 3, Print::get_center_x(strlen(msg2)),
                      msg2);
}

#ifdef TYPOS_DEBUG
void Print::status(const char current_ch, const bool is_ok) {
  const int y = Print::get_info_y();
  const int x = Print::get_info_x();

  if (current_ch) {
    if (is_ok) {
      Colorize::cmvprintw(COLORIZE_OK, y, x, "correct char\n");
    } else {
      Colorize::cmvprintw(COLORIZE_ERROR, y, x, "invalid char\n");
    }
  } else if (is_ok) {
    Colorize::cmvprintw(COLORIZE_OK, y, x, "ok, next word\n");
  } else {
    Colorize::cmvprintw(COLORIZE_WARN, y, x, "WTF\n");
  }
}

#endif

int Print::get_text_x(void) { return Print::_text_x; }
int Print::get_text_y(void) { return Print::_text_y; }
int Print::inc_text_y(void) { return ++Print::_text_y; }
int Print::reset_text_y(void) {
  return Print::_text_y = Print::_text_y_default;
}

int Print::get_text_delimiter_y(void) { return Print::_text_y + 1; }

int Print::get_timer_y(void) { return Print::_text_y + Print::_timer_shift_y; }
int Print::get_timer_x(void) { return Print::_timer_x; }

int Print::get_input_y(void) { return Print::_text_y + Print::_input_shift_y; }
int Print::get_stats_y(void) {
  return Print::get_input_y() + Print::_stats_shift_y;
}

#ifdef TYPOS_DEBUG
int Print::get_info_y(void) {
  return Print::get_input_y() + Print::_info_shift_y;
}
int Print::get_info_x(void) { return Print::_info_x; }
#endif

int Print::get_center_x(size_t text_len) {
  return stdscr->_maxx / 2 - text_len / 2;
}
