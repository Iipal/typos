#include "typos.h"

const int print_line_text_y_default = 1;
int print_line_text_y = print_line_text_y_default;
int print_line_text_x = 1;

const int print_line_input_shift_y = 2;
const int print_line_timer_shift_y = print_line_input_shift_y;
const int print_line_timer_x = 5;
const int print_line_input_x = print_line_timer_x + 1;

int print_line_info_shift_y = 2;
int print_line_info_x = 1;

inline int print_line_text_inc_y(void) { return ++print_line_text_y; };
inline int print_line_text_reset_y(void) {
  return print_line_text_y = print_line_text_y_default;
};
inline int print_line_text_get_y(void) { return print_line_text_y; };
inline int print_line_text_get_x(void) { return print_line_text_x; };
inline int print_line_text_delimiter_get_y(void) {
  return print_line_text_y + 1;
};

inline int print_line_input_get_y(void) {
  return print_line_text_y + print_line_input_shift_y;
}
inline int print_line_input_update_x(size_t word_len) {
  return print_line_get_center_x(word_len);
}
inline int print_line_input_get_x(void) { return print_line_input_x; }

inline int print_line_timer_get_y(void) {
  return print_line_text_y + print_line_timer_shift_y;
}
inline int print_line_timer_get_x(void) { return print_line_timer_x; }

inline int print_line_info_get_y(void) {
  return print_line_input_get_y() + print_line_info_shift_y;
}
inline int print_line_info_get_x(void) { return print_line_info_x; }

inline int print_line_get_center_x(size_t text_len) {
  return (stdscr->_maxx / 2) - (text_len / 2);
}

inline void print_text(const typing_text_t *restrict text) {
  typing_word_t **words = typing_get_words(text);
  size_t current_word_pos = typing_get_current_word_pos(text);
  size_t current_ch_pos = typing_get_current_ch_pos(text);
  const size_t max_x = stdscr->_maxx - 2;

  print_line_text_reset_y();

  for (size_t i = 0, start_print_pos_x = 0; words[i]; i++) {
    const typing_word_t *word = words[i];
    const char *current_string = word->string;

    color_t string_color = COLORIZE_DEFAULT;
    if (current_word_pos > i) {
      string_color = word->string_color;
    } else if (current_word_pos == i) {
      string_color = COLORIZE_INFO;
    }

    if (start_print_pos_x + word->length > max_x) {
      print_line_text_inc_y();
      start_print_pos_x = 0;
    }

    const int y = print_line_text_get_y();
    const int x = print_line_text_get_x();

    if (current_word_pos == i) {
      for (size_t i = 0; word->length >= i; ++i) {
        color_t current_ch_color = COLORIZE_DEFAULT;
        if (current_ch_pos == i) {
          current_ch_color =
              !current_string[i] ? COLORIZE_INFO_INVERT : COLORIZE_INFO;
        } else if (current_ch_pos > i) {
          current_ch_color = word->at_pos_colors[i];
        }

        colorize_mvaddch(current_ch_color, y, x + start_print_pos_x + i,
                         current_string[i] ? current_string[i] : ' ');
      }
    } else {
      colorize_mvprintw(string_color, y, x + start_print_pos_x, "%s ",
                        current_string);
    }

    start_print_pos_x += word->length + 1;
  }
}

inline void print_text_delimiter(void) {
  const int y = print_line_text_delimiter_get_y();
  mvhline(y, 1, ACS_BSBS, stdscr->_maxx - 1);
}

inline void print_clean_prev_word(const typing_word_t *restrict word) {
  const int y = print_line_input_get_y();
  const int x = print_line_get_center_x(word->length);

  move(y, x);
  clrtoeol();
  move(y + 1, x);
  clrtoeol();
}

inline void print_timer(int seconds) {
  int min = seconds / 60;
  int sec = seconds % 60;
  int y = print_line_timer_get_y();
  int x = print_line_timer_get_x();

  colorize_mvprintw(COLORIZE_INFO, y, x, "%02d:%02d", min, sec);
  curs_set(0);
}

inline void print_current_word(const typing_word_t *restrict word,
                               int input_ch) {
  const int y = print_line_input_get_y();
  const int x = print_line_input_update_x(word ? word->length : 12);

  if (!word) {
    colorize_mvprintwe(COLORIZE_INFO, y, x, "end of words");
  } else {
    for (size_t i = 0; word->length > i; ++i) {
      colorize_mvaddch(word->at_pos_colors[i], y, x + i, word->string[i]);
    }

    colorize_mvprintw(COLORIZE_DEFAULT, y, x + word->length, "%12c", ' ');
  }

  mvhline(y + 1, x, ACS_BSBS, word ? word->length + 1 : 0);

  (void)input_ch;
#ifdef TYPOS_DEBUG
  colorize_mvprintw(COLORIZE_INFO, y, x + (word ? word->length : 12),
                    " | last input: %3d:'%2c'", input_ch,
                    input_ch ? input_ch : ' ');
#endif

  move(y, x + (word ? word->pos : 0));
  curs_set(1);
}

inline void print_input_status(const char current_ch, const bool is_input_ok) {
  const int y = print_line_info_get_y();
  const int x = print_line_info_get_x();

  if (current_ch) {
    if (is_input_ok) {
      colorize_mvprintwe(COLORIZE_OK, y, x, "correct char\n");
    } else {
      colorize_mvprintwe(COLORIZE_ERROR, y, x, "invalid char\n");
    }
  } else if (is_input_ok) {
    colorize_mvprintwe(COLORIZE_OK, y, x, "ok, next word\n");
  } else {
    colorize_mvprintwe(COLORIZE_WARN, y, x, "WTF\n");
  }
}
