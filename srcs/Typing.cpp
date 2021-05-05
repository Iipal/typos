#include "Typing.hpp"
#include "Colorize.hpp"
#include "Flags.hpp"
#include "Print.hpp"
#include "TypingKeys.hpp"
#include "Words.hpp"

Typing::Typing(const std::vector<std::string_view> strings, size_t strings_length)
    : TypingStats(), length(strings_length), current_word_pos(0) {
  this->_new_words(strings, strings_length);
}

void Typing::_new_words(const std::vector<std::string_view> strings,
                        size_t                              strings_length) {
  try {
    this->words = new TypingWord *[strings_length + 1];

    const size_t max_x = stdscr->_maxx - 2;
    int          y     = 1;
    int          x     = 0;
    for (size_t i = 0; strings_length > i; ++i) {
      if (x + strings[i].length() > max_x) {
        ++y;
        x = 0;
      }

      this->words[i] = new TypingWord(y, x + 1, strings[i]);

      x += strings[i].length() + 1;
    }

    this->words[strings_length] = NULL;
  } catch (std::exception & e) {
    endwin();
    std::cerr << "Allocation failed: " << e.what() << std::endl;
    exit(EXIT_FAILURE);
  }
}

Typing::~Typing() { this->_delete_words(); }
void Typing::_delete_words(void) {
  if (this->words) {
    for (size_t i = 0; this->words[i]; ++i) {
      delete this->words[i];
    }
    delete[] this->words;
  }
  this->words = NULL;
}

void Typing::iterate(void) {
  const bool is_accessible_at_word =
      !!this->words && !!this->words[this->current_word_pos];
  TypingWord * word                  = NULL;
  bool         is_accessible_at_char = false;

  if (is_accessible_at_word) {
    word                  = this->words[this->current_word_pos];
    is_accessible_at_char = !!word && !!word->get_char_at()->ch();
  }

  if (is_accessible_at_word && !is_accessible_at_char) {
    if (this->current_word_pos != this->length) {
      ++this->current_word_pos;
      Print::clean_input();
    }

    word->validate();
  } else if (word) {
    word->inc_current_pos();
  }

  this->inc_chars();
  if (!this->get_word()) {
    this->reset();
    Print::render_all(*this);
  }
}

void Typing::backspace(void) {
  TypingWord * word = this->words[this->current_word_pos];
  const key_t  ch   = word->get_char_at()->ch();

  if (!word || (!word->get_current_pos() && this->current_word_pos)) {
    --this->current_word_pos;
    Print::clean_input();
  } else {
    if (!ch) {
      word->set_color_at(Colorize::COLORIZE_DEFAULT);
    }

    word->dec_current_pos();
    if (word->get_color_at(word->get_current_pos()) != Colorize::COLORIZE_OK) {
      this->dec_typos();
    }
    word->set_color_at(Colorize::COLORIZE_DEFAULT);

    bool is_word_ok_now = word->is_ok();
    if (is_word_ok_now) {
      word->set_color(Colorize::COLORIZE_OK);
    }
  }
}

void Typing::reset_word() {
  TypingWord * word     = this->get_word();
  const size_t word_pos = word->get_current_pos();

  auto clear_word = [this](TypingWord * _w) {
    const size_t _w_pos = _w->get_current_pos();
    for (size_t i = 0; _w_pos >= i; ++i) {
      const Colorize::color_t ch_clr = _w->get_char_at(i)->clr();
      if (Colorize::COLORIZE_ERROR == ch_clr || Colorize::COLORIZE_WARN == ch_clr) {
        this->dec_typos();
      }

      _w->set_color_at(Colorize::COLORIZE_DEFAULT, i);
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
  TypingWord * word = this->get_word();

  if (word->get_color_at() != Colorize::COLORIZE_DEFAULT) {
    if (word->get_current_pos() >= word->get_length()) {
      Print::clean_input();
      ++this->current_word_pos;
    } else {
      word->inc_current_pos();
    }
  }
}

void Typing::move_to_prev_ch(void) {
  TypingWord * word     = this->get_word();
  const size_t word_pos = word->get_current_pos();

  const TypingChar * ch  = word->get_char_at();
  const int          chx = ch->x();
  const int          chy = ch->y();

  if (1 == chx && chy > 1) {
    Print::clean_input();
    --this->current_word_pos;
  } else if (1 < chx) {
    if (word_pos) {
      word->dec_current_pos();
    } else {
      Print::clean_input();
      --this->current_word_pos;
    }
  }
}

bool Typing::validate_input(int input) {
  TypingWord * current_word = this->words[this->current_word_pos];
  return this->validate_input(input, current_word);
}
bool Typing::validate_input(int input, TypingWord * const word) {
  if (!word) {
    return true;
  }

  const key_t ch    = word->get_char_at()->ch();
  bool        is_ok = true;

  Colorize::color_t clr = Colorize::COLORIZE_OK;
  is_ok =
      (ch == input ||
       (!ch && (input == TypingKeys::KEY_SPACE || input == TypingKeys::KEY_NEW_LINE)));
  if (!is_ok) {
    clr = Colorize::COLORIZE_ERROR;
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
  Print::clean_input();
  this->current_word_pos = 0;
  for (size_t i = 0; this->words[i]; ++i) {
    TypingWord * word        = this->words[i];
    const size_t word_length = word->get_length();

    word->set_pos(0);
    word->set_color(Colorize::COLORIZE_DEFAULT);
    for (size_t i = 0; word_length > i; ++i) {
      word->set_color_at(Colorize::COLORIZE_DEFAULT, i);
    }
  }
}

void Typing::new_words(void) {
  this->_delete_words();
  this->_new_words(Words::get_words(Flags::max_words), Flags::max_words);
}

TypingWord ** Typing::get_words(void) const { return this->words; }

TypingWord * Typing::get_word(void) const {
  return this->get_word(this->current_word_pos);
}
TypingWord * Typing::get_word(size_t at_pos) const {
  TypingWord * out = this->words[at_pos];
  return out;
}
TypingWord * Typing::get_prev_word(void) const {
  TypingWord * out = NULL;

  if (this->current_word_pos) {
    out = this->words[this->current_word_pos - 1];
  }

  return out;
}
TypingWord * Typing::get_next_word(void) const {
  TypingWord * out = NULL;

  if (this->length > this->current_word_pos + 1) {
    out = this->words[this->current_word_pos + 1];
  }

  return out;
}

TypingChar * Typing::get_char_at(void) const { return this->get_word()->get_char_at(); };
TypingChar * Typing::get_char_at(size_t ch_pos) const {
  return this->get_char_at(ch_pos, this->current_word_pos);
}
TypingChar * Typing::get_char_at(size_t ch_pos, size_t w_pos) const {
  return this->get_word(w_pos)->get_char_at(ch_pos);
}

size_t Typing::get_length(void) const { return this->length; }
size_t Typing::get_current_word_pos(void) const { return this->current_word_pos; }

void Typing::run(void) {
  Print::render_all(this);

  TypingKeys::key_t k    = 0;
  bool              stop = false;

  while (!stop) {
    Print::current_char(this->get_char_at());
    Print::input_word(this);

    k    = TypingKeys::get_input();
    stop = TypingKeys::procced_input(k, this);

#ifdef TYPOS_DEBUG
    Print::input_status(*this, this->validate_input(k), k);
#endif
  }
}
