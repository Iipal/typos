#include "typos.hpp"
#include <string.h>

int Print::_text_y = Print::_text_y_default;
int Print::_text_x = 1;

void Print::current_char(const TypingChar &ch, unsigned attrs) {
  int y = ch.get_screen_y();
  int x = ch.get_screen_x();
  chtype _ch = !(chtype)ch ? TypingKeys::KEY_SPACE : (chtype)ch;

  unsigned _attrs = attrs;
  if (ch.get_color() == COLORIZE_ERROR) {
    _attrs |= A_BOLD;
  }

  Colorize::cmvaddch(ch, _attrs, y, x, _ch);
}

void Print::current_char(const TypingChar &ch) {
  Print::current_char(ch, A_UNDERLINE);
}

void Print::clear_current_char(const TypingChar &ch) {
  int y = ch.get_screen_y();
  int x = ch.get_screen_x();
  chtype _ch = !(chtype)ch ? TypingKeys::KEY_SPACE : (chtype)ch;

  Colorize::cmvaddch(COLORIZE_DEFAULT, y, x, _ch);
}

void Print::render_all(const Typing &text) {
  curs_set(0);
  Print::text(text);
  Print::text_delimiter();
  Print::timer(Timer::get_remaining_seconds());
  Print::input_word(text.get_prev_word(), text.get_word(),
                    text.get_next_word());
  box(stdscr, 0, 0);
}

void Print::text(const Typing &text) { Print::text(text, text.get_length()); }
void Print::text(const Typing &text, size_t n_words) {
  clear();

  TypingWord **words = text.get_words();
  const size_t current_word_pos = text.get_current_word_pos();

  const size_t max_x = stdscr->_maxx - 2;
  int text_y = Print::_text_y_default;

  for (size_t i = 0, start_print_pos_x = 0; words[i] && n_words > i; ++i) {
    const TypingWord *word = words[i];
    const std::string str = word->to_str();

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
        const char ch = str[i];
        color_t current_ch_color = word->get_color_at(i);
        Colorize::cmvaddch(current_ch_color, y, x + start_print_pos_x + i,
                           ch ? ch : ' ');
      }
    } else {
      Colorize::cmvprintw(clr, y, x + start_print_pos_x, "%s ", str.c_str());
    }

    start_print_pos_x += word->get_length() + 1;
  }

  Print::_text_y = text_y;
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

void Print::clean_input(void) {
  const int y = Print::get_input_y();
  const int x = Print::get_timer_x() + 6;

  Print::clean_line(y, x);

  // clear the current character underline
  Colorize::cmvaddch(COLORIZE_DEFAULT, y + 1, Print::get_center_x(2), ' ');
}

void Print::timer(int seconds) {
  if (Flags::is_free_mode) {
    return;
  }

  curs_set(0);

  int min = seconds / 60;
  int sec = seconds % 60;
  int y = Print::get_timer_y();
  int x = Print::get_timer_x();

  Colorize::cmvprintw(COLORIZE_INFO, y, x, "%02d:%02d", min, sec);
}

void Print::input_word(const Typing &text) {
  Print::input_word(text.get_prev_word(), text.get_word(),
                    text.get_next_word());
}
void Print::input_word(const TypingWord *const prev,
                       const TypingWord *const word,
                       const TypingWord *const next) {
  Print::clean_input();

  const int y = Print::get_input_y();
  const int center_x = Print::get_center_x(2);
  const int x = center_x - (word ? word->get_current_pos() : 0);

  if (!word) {
    Colorize::cmvprintw(COLORIZE_INFO, y, x, "end of words");
    return;
  }

  auto print_word = [y](const TypingWord *const _w, int start_x,
                        unsigned attrs) {
    for (size_t i = 0; _w->get_length() > i; ++i) {
      Colorize::cmvaddch(_w->get_color_at(i), attrs, y, start_x + i,
                         _w->get_char_at(i));
    }
  };

  if (prev) {
    unsigned a = A_DIM;
    if (2 > word->get_current_pos()) {
      a = 0;
    }
    print_word(prev, x - prev->get_length() - 1, a);
  }

  print_word(word, x, 0);

  if (next) {
    unsigned a = A_DIM;
    if (word->get_current_pos() + 2 >= word->get_length()) {
      a = 0;
    }
    print_word(next, x + word->get_length() + 1, a);
  }

  mvhline(y + 1, center_x, ACS_BSBS, 1);

  move(y, center_x);
}

void Print::stats(const TypingStatsData &data) {
  const int y = Print::get_stats_y();

  const char *msg1 = "YOU TIMED OUT";
  const char *msg2 = "Restart: `Tab` | Exit: `Ctrl+C` | Save Result: `Ctrl+S`";

  Colorize::cmvprintw(COLORIZE_OK, y, Print::get_center_x(strlen(msg1) - 1),
                      msg1);

  TypingStatsDataFmt *fmt = TypingStats::get_stats_data_fmt(data);

  char fmt_buff[64] = {0};
  size_t data_y = y + 2;
  size_t data_x = Print::get_center_x(20);
  for (size_t i = 0; fmt[i].first; ++i) {
    snprintf(fmt_buff, sizeof(fmt_buff) - 1, "%%10s | %s", fmt[i].second.fmt);
    Colorize::cmvprintw(fmt[i].second.clr, data_y++, data_x, fmt_buff,
                        fmt[i].first, fmt[i].second.value);
  }

  delete[] fmt;

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
  const chtype ch = word ? word->get_char_at().get_char() : 0;

  int y = Print::get_input_status_y();
  int x = Print::get_input_status_x();

  Print::clean_line(y);

  if (ch) {
    if (is_ok) {
      Colorize::cmvprintw(COLORIZE_OK, y, x, "correct char");
    } else {
      Colorize::cmvprintw(COLORIZE_ERROR, y, x, "invalid char");
    }
  } else if (is_ok) {
    Colorize::cmvprintw(COLORIZE_OK, y, x, "ok, next word");
  } else {
    Colorize::cmvprintw(COLORIZE_WARN, y, x, "WTF");
  }

  Print::clean_line(y + 1);
  if (word) {
    Colorize::cmvprintw(
        COLORIZE_INFO, y + 1, x, "WPos: %zu; WClr: %s; CPosAtW: %zu;",
        text.get_current_word_pos(), Colorize::clrtostr(word->get_color()),
        word->get_current_pos());
  }

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
