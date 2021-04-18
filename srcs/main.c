#include "typos.h"

void colouring() {
  if (has_colors()) {
    if (start_color() == OK) {
      g_colorsize_update_pair(TYPOS_COLOR_OK, COLOR_GREEN, COLOR_BLACK);
      g_colorsize_update_pair(TYPOS_COLOR_WARN, COLOR_YELLOW, COLOR_BLACK);
      g_colorsize_update_pair(TYPOS_COLOR_ERROR, COLOR_RED, COLOR_BLACK);
      g_colorsize_update_pair(TYPOS_COLOR_INFO, COLOR_MAGENTA, COLOR_BLACK);
    } else {
      addstr("Cannot start colours\n");
    }
  } else {
    addstr("Not colour capable\n");
  }
  refresh();
}

const char *just_a_strings[] = {"string1", "string2", NULL};
const size_t just_a_strings_length =
    (sizeof(just_a_strings) / sizeof(*just_a_strings)) - 1;
size_t current_array_iterator = 0;
size_t current_string_iterator = 0;
static inline void iterate() {
  bool is_current_array_item_accesible =
      !!just_a_strings[current_array_iterator];
  bool is_current_array_item_char_accesible =
      is_current_array_item_accesible &&
      !!just_a_strings[current_array_iterator][current_string_iterator];

  if (is_current_array_item_accesible &&
      !is_current_array_item_char_accesible) {
    if ((current_array_iterator + 1) != just_a_strings_length) {
      ++current_array_iterator;
    } else {
      current_array_iterator = 0;
    }
  }
  if (is_current_array_item_char_accesible) {
    ++current_string_iterator;
  } else {
    current_string_iterator = 0;
  }

  if (!is_current_array_item_accesible &&
      !is_current_array_item_char_accesible) {
    current_array_iterator = 0;
    current_string_iterator = 0;
  }
}
static inline const char *get_current_string() {
  return just_a_strings[current_array_iterator];
}
static inline char get_current_char() {
  return get_current_string()[current_string_iterator];
}

int main(void) {
  initscr();
  colouring();

  curs_set(0);
  noecho();

  int input = 0;
  bool is_input_ok = true;

  for (size_t i = 0, start_print_pos = 0; just_a_strings[i]; i++) {
    start_print_pos += (strlen(just_a_strings[i]) + 1) * i;
    g_colorize_mvprintw(TYPOS_COLOR_DEFAULT, 0, start_print_pos, "%s ",
                        just_a_strings[i]);
    if (!just_a_strings[i + 1]) {
      start_print_pos += (strlen(just_a_strings[i]) + 1) * i;
      g_colorize_mvaddch(TYPOS_COLOR_DEFAULT, 0, start_print_pos, '\n');
    }
  }

  const size_t input_line = 1;
  const size_t info_line = 3;

  for (;;) {
    const char current_ch = get_current_char();
    const char *current_str = get_current_string();
    const char prev_ch =
        !input ? current_ch : current_str[current_string_iterator - 1];

    if (!current_ch) {
      g_colorize_mvprintwe(TYPOS_COLOR_DEFAULT, input_line, 0, "delimiter");
    } else {
      g_colorize_mvprintw(TYPOS_COLOR_DEFAULT, input_line, 0, "%s%10c",
                          current_str, ' ');
      g_colorize_mvaddch(TYPOS_COLOR_INFO, input_line, current_string_iterator,
                         current_ch);

      if (input) {
        const enum e_colorize status_color =
            is_input_ok ? TYPOS_COLOR_OK : TYPOS_COLOR_ERROR;
        g_colorize_mvprintw(status_color, input_line,
                            current_string_iterator - 1, "%c", prev_ch);
      }
    }

    input = getch();
    is_input_ok = false;

    if (input) {
      g_colorize_mvprintw(TYPOS_COLOR_INFO, input_line,
                          strlen(current_str) + 10, " | input: %c\n", input);
    }

    if (current_ch) {
      is_input_ok = (current_ch == input);
      if (is_input_ok) {
        g_colorize_mvprintwe(TYPOS_COLOR_OK, info_line, 0, "correct char\n");
      } else {
        g_colorize_mvprintwe(TYPOS_COLOR_ERROR, info_line, 0, "invalid char\n");
      }
    } else if (!current_ch && input == ' ') {
      is_input_ok = true;
      g_colorize_mvprintwe(TYPOS_COLOR_OK, info_line, 0, "ok, next word\n");
    } else {
      g_colorize_mvprintwe(TYPOS_COLOR_WARN, info_line, 0, "WTF\n");
    }

    iterate();
  }

  endwin();
}
