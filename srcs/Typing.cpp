#include "typos.hpp"

Typing *g_Typing = NULL;

Typing::Typing(const std::string *strings, size_t strings_length)
    : length(strings_length), current_word_pos(0) {
  this->words = new TypingWord *[strings_length + 1];

  const size_t max_x = stdscr->_maxx - 2;
  int y = 1;
  int x = 0;
  for (size_t i = 0; strings_length > i; ++i) {
    if (x + strings[i].length() > max_x) {
      ++y;
      x = 0;
    }
    this->words[i] = new TypingWord(y, x + 1, strings[i]);
    x += strings[i].length() + 1;
  }

  this->words[strings_length] = NULL;
}
Typing::~Typing() {
  if (this->words) {
    for (size_t i = 0; this->length > i; ++i) {
      if (this->words[i]) {
        delete this->words[i];
      }
    }
    delete[] this->words;
  }
}

int Typing::get_input(void) {
  int ch = 0;

  curs_set(1);

  while ((ch = getch())) {
    if (isprint(ch) || Typing::KEY_DEL == ch || Typing::KEY_ESC == ch ||
        Typing::KEY_NEW_LINE == ch) {
      break;
    }
    napms(50);
  }

  curs_set(0);

  return ch;
}

void Typing::iterate(void) {
  const bool is_accessible_at_word =
      !!this->words && !!this->words[this->current_word_pos];
  TypingWord *word = NULL;
  bool is_accessible_at_char = false;

  if (is_accessible_at_word) {
    word = this->words[this->current_word_pos];
    is_accessible_at_char = !!word->get_char().get_char();
  }

  if (is_accessible_at_word && !is_accessible_at_char) {
    if (this->current_word_pos != this->length) {
      ++this->current_word_pos;
      Print::clean_prev_word(word);
    }

    word->validate();
  } else if (word) {
    word->inc_current_pos();
  }

  this->inc_chars();
  if (!word) {
    this->reset();
  }
}

void Typing::backspace(void) {
  TypingWord *word = this->words[this->current_word_pos];

  if (!word || (!word->get_current_pos() && this->current_word_pos)) {
    --this->current_word_pos;
    Print::clean_prev_word(word);
  } else {
    word->dec_current_pos();
    if (word->get_color_at(word->get_current_pos()) != COLORIZE_OK) {
      this->dec_typos();
    }
    word->set_color_at(COLORIZE_DEFAULT);

    bool is_word_ok_now = word->is_ok();
    if (is_word_ok_now) {
      word->set_color(COLORIZE_OK);
    }
  }
}

bool Typing::validate_input(int input) {
  TypingWord *current_word = this->words[this->current_word_pos];
  return this->validate_input(input, current_word);
}
bool Typing::validate_input(int input, TypingWord *const word) {
  if (!word) {
    return true;
  }

  const char ch = word->get_char().get_char();
  bool is_ok = true;

  if (ch) {
    color_t clr = COLORIZE_OK;
    is_ok = (ch == input);
    if (!is_ok) {
      clr = COLORIZE_WARN;
    }
    word->set_color(clr);
    word->set_color_at(clr);
  } else if (!ch) {
    if ((input != Typing::KEY_SPACE_BAR && input != Typing::KEY_NEW_LINE)) {
      is_ok = false;
    }
  }

  if (!is_ok) {
    this->inc_typos();
    this->inc_total_typos();
  }

  return is_ok;
}

void Typing::reset(void) {
  Print::clean_prev_word(NULL);
  this->current_word_pos = 0;
  for (size_t i = 0; this->length > i; ++i) {
    TypingWord *word = this->words[i];
    const size_t word_length = word->get_length();

    word->set_pos(0);
    word->set_color(COLORIZE_DEFAULT);
    for (size_t i = 0; word_length > i; ++i) {
      word->set_color_at(COLORIZE_DEFAULT, i);
    }
  }

  this->reset_stats();
}

TypingWord **Typing::get_words(void) const { return this->words; }
size_t Typing::get_length(void) const { return this->length; }
size_t Typing::get_current_word_pos(void) const {
  return this->current_word_pos;
}
TypingWord *Typing::get_word(void) const {
  return this->words[this->current_word_pos];
}
TypingWord *Typing::get_word(size_t at_pos) const {
  return this->words[at_pos];
}
