#include "typos.hpp"
#include <string.h>

int Print::_text_y = Print::_text_y_default;
int Print::_text_x = 1;

void Print::render_all(const Typing &text) {
  Print::text(text);
  Print::text_delimiter();
  Print::input_word(text.get_word());
}

void Print::text(const Typing &text) { Print::text(text, text.get_length()); }
void Print::text(const Typing &text, size_t n_words) {
  static bool is_text_y_set = false;

  curs_set(0);

  TypingWord **words = text.get_words();
  const size_t current_word_pos = text.get_current_word_pos();
  const TypingWord *current_word = text.get_word();
  const size_t current_ch_pos = current_word->get_current_pos();

  const size_t max_x = stdscr->_maxx - 2;
  int text_y = Print::_text_y_default;

  for (size_t i = 0, start_print_pos_x = 0; words[i] && n_words > i; ++i) {
    const TypingWord *word = words[i];
    const std::string str = word->get_string();

    color_t clr = COLORIZE_DEFAULT;
    if (current_word_pos > i) {
      clr = word->get_color();
    } else if (current_word_pos == i) {
      clr = COLORIZE_INFO;
    }

    if (start_print_pos_x + word->get_length() > max_x) {
      ++text_y;
      start_print_pos_x = 0;
    }

    const int y = text_y;
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

  if (!is_text_y_set) {
    is_text_y_set = true;
    Print::_text_y = text_y;
  }
}

void Print::text_delimiter(void) {
  const int y = Print::get_text_delimiter_y();
  mvhline(y, 1, ACS_BSBS, stdscr->_maxx - 1);
}

void Print::clean_line(int y) { Print::clean_line(y, 1); }
void Print::clean_line(int y, int x) {
  move(y, x);
  clrtoeol();
  mvhline(y, stdscr->_maxx, ACS_SBSB, 1);
}

void Print::clean_prev_word(const TypingWord *const word) {
  const int y = Print::get_input_y();
  const int x = Print::get_center_x(word ? word->get_length() : 30);

  Print::clean_line(y, x);
  Print::clean_line(y + 1, x); // clearing the word underline
}

void Print::timer(int seconds) {
  int min = seconds / 60;
  int sec = seconds % 60;
  int y = Print::get_timer_y();
  int x = Print::get_timer_x();

  Colorize::cmvprintw(COLORIZE_INFO, y, x, "%02d:%02d", min, sec);
  curs_set(0);
}

void Print::input_word(const TypingWord *const word) {
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

  move(y, x + (word ? word->get_current_pos() : 0));
  curs_set(1);
}

void Print::stats(const TypingStatsData &data) {
  const int y = Print::get_stats_y();

  const char *msg1 = "YOU TIMED OUT";
  const char *msg2 = "Enter: Restart; Esc: Exit;";

  Colorize::cmvprintw(COLORIZE_OK, y, Print::get_center_x(strlen(msg1) - 1),
                      msg1);

  struct __s_stats_data {
    const char *fmt;
    float value;
  };

#define STATS_DATA_DELIMITER                                                   \
  {                                                                            \
    "", { "", 0.0f }                                                           \
  }

  std::pair<const char *, __s_stats_data> stats_data[] = {
      {"WPM", {"%-7.2f", data.wpm.net_wpm}},
      {"RAW WPM", {"%-7.2f", data.wpm.gross_wpm}},
      {"REAL WPM", {"%-7.2f", data.wpm.net_real_wpm}},
      STATS_DATA_DELIMITER,
      {"TYPED", {"%-7.0f", static_cast<float>(data.characters)}},
      {"CPS", {"%-7.2f", data.cps}},
      STATS_DATA_DELIMITER,
      {"TYPOS", {"%-7.0f", static_cast<float>(data.corrected_typos)}},
      {"REAL TYPOS", {"%-7.0f", static_cast<float>(data.not_corrected_typos)}},
      STATS_DATA_DELIMITER,
      {"ACC", {"%-7.2f", data.accuracy}},
      {"REAL ACC", {"%-7.2f", data.real_accuracy}},
  };

  char fmt_buff[64] = {0};
  size_t data_y = y + 2;
  size_t data_x = Print::get_center_x(20);
  for (const auto &[key, v] : stats_data) {
    snprintf(fmt_buff, sizeof(fmt_buff) - 1, "%%10s | %s", v.fmt);
    Colorize::cmvprintw(COLORIZE_OK, data_y++, data_x, fmt_buff, key, v.value);
  }

  Colorize::cmvprintw(COLORIZE_OK, data_y + 1,
                      Print::get_center_x(strlen(msg2)), msg2);
}

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

int Print::get_center_x(size_t text_len) {
  return stdscr->_maxx / 2 - text_len / 2;
}

#ifdef TYPOS_DEBUG

void Print::input_status(const Typing &text, const bool is_ok,
                         const int input) {
  const TypingWord *const word = text.get_word();
  const char ch = word->get_char();

  int y = Print::get_input_status_y();
  int x = Print::get_input_status_x();

  Print::clean_line(y);

  if (ch) {
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

  Print::clean_line(y + 1);
  Colorize::cmvprintw(
      COLORIZE_INFO, y + 1, x, "WPos: %zu; WClr: %s; CPosAtW: %zu;",
      text.get_current_word_pos(), Colorize::clrtostr(word->get_color()),
      word->get_current_pos());

  Print::typing_status(text);

  {
    const size_t word_length = word ? word->get_length() : 24;

    y = Print::get_input_y();
    x = Print::get_center_x(word_length);

    Colorize::cmvprintw(COLORIZE_INFO, y, x + word_length,
                        " | last input: %3d:'%2c'", input, input ? input : ' ');
  }
}

void Print::typing_status(const Typing &text) {
  int y = Print::get_input_status_y() + 2;
  int x = Print::get_input_status_x();

  Print::clean_line(y);

  Colorize::cmvprintw(COLORIZE_INFO, y, x, "RAW: %.2f; REAL: %.2f; CPS: %.2f;",
                      text.get_gross_wpm(), text.get_real_accuracy(),
                      text.get_cps());
}

int Print::get_input_status_y(void) {
  return Print::get_input_y() + Print::_input_status_shift_y;
}
int Print::get_input_status_x(void) { return Print::_input_status_x; }

#endif
