#include "typos.hpp"

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
    if (Typing::is_acceptable_input(ch)) {
      break;
    }
    napms(50);
  }

  curs_set(0);

  return ch;
}

bool Typing::is_acceptable_input(int input) {
  return isprint(input) || Typing::is_functionality_input(input);
}

bool Typing::is_functionality_input(int input) {
  return (Typing::KEY_NEW_LINE == input || Typing::KEY_ESC == input ||
          Typing::KEY_DEL == input || Typing::KEY_ARROW_LEFT == input ||
          Typing::KEY_ARROW_RIGHT == input ||
          Typing::KEY_CTRL_BACKSPACE == input);
}

void Typing::iterate(void) {
  const bool is_accessible_at_word =
      !!this->words && !!this->words[this->current_word_pos];
  TypingWord *word = NULL;
  bool is_accessible_at_char = false;

  if (is_accessible_at_word) {
    word = this->words[this->current_word_pos];
    is_accessible_at_char = !!(chtype)word->get_char_at();
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
  const chtype ch = word->get_char_at();

  if (!word || (!word->get_current_pos() && this->current_word_pos)) {
    --this->current_word_pos;
    Print::clean_prev_word(word);
  } else {
    if (!ch) {
      word->set_color_at(COLORIZE_DEFAULT);
    }

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

void Typing::reset_word() {
  TypingWord *word = this->get_word();
  const size_t word_pos = word->get_current_pos();

  auto clear_word = [](TypingWord *_w) {
    const size_t _w_pos = _w->get_current_pos();
    for (size_t i = 0; _w_pos >= i; ++i) {
      _w->set_color_at(COLORIZE_DEFAULT, i);
      Print::clear_current_char(_w->get_char_at(i));
    }
    _w->set_pos(0);
  };

  if (word_pos) {
    clear_word(word);
  } else {
    Print::clear_current_char(word->get_char_at());
    if (this->current_word_pos) {
      --this->current_word_pos;
      clear_word(this->get_word());
    }
  }
}

void Typing::move_to_next_ch(void) {
  TypingWord *word = this->get_word();
  const TypingChar ch = word->get_char_at();

  const size_t word_pos = word->get_current_pos();
  const size_t word_length = word->get_length();

  if (ch.get_color() != COLORIZE_DEFAULT) {
    if (word_pos >= word_length) {
      Print::clean_prev_word(word);
      ++this->current_word_pos;
    } else {
      word->inc_current_pos();
    }
  }
}

void Typing::move_to_prev_ch(void) {
  TypingWord *word = this->get_word();
  const TypingChar ch = word->get_char_at();

  const size_t word_pos = word->get_current_pos();
  const int chx = ch.get_screen_x();
  const int chy = ch.get_screen_y();

  if (1 == chx && chy > 1) {
    Print::clean_prev_word(word);
    --this->current_word_pos;
  } else if (1 < chx) {
    if (word_pos) {
      word->dec_current_pos();
    } else {
      Print::clean_prev_word(word);
      --this->current_word_pos;
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

  const chtype ch = word->get_char_at();
  bool is_ok = true;

  color_t clr = COLORIZE_OK;
  is_ok = ((int)ch == input || (!(int)ch && (input == Typing::KEY_SPACE_BAR ||
                                             input == Typing::KEY_NEW_LINE)));
  if (!is_ok) {
    clr = COLORIZE_WARN;
  }
  word->set_color(clr);
  word->set_color_at(clr);

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
