#include "typos.h"

inline typing_text_t *typing_text_init(const char **strings,
                                       const size_t strings_length) {
  typing_text_t *text = NULL;

  assert((text = calloc(sizeof(*text), 1)));
  text->length = strings_length;

  assert((text->words = calloc(text->length + 1, sizeof(*text->words))));
  for (size_t i = 0; text->length > i; ++i) {
    char *word = NULL;
    assert((word = strdup(strings[i])));

    const size_t word_length = strlen(strings[i]);
    typos_color_t *colors = NULL;
    assert((colors = calloc(sizeof(typos_color_t), word_length)));

    assert((text->words[i] = calloc(sizeof(typing_word_t), 1)));
    memcpy(text->words[i],
           &(typing_word_t){word, colors, 0, strlen(word), TYPOS_COLOR_DEFAULT},
           sizeof(typing_word_t));
  }

  return text;
}

inline void typing_text_free(typing_text_t *text) {
  if (!text) {
    return;
  }

  if (text->words) {
    for (size_t i = 0; text->length > i; ++i) {
      free(text->words[i]->string);
      free(text->words[i]->at_pos_colors);
      free(text->words[i]);
    }
    free(text->words);
  }
  free(text);
}

inline bool typing_test_is_word_ok(const typing_word_t *restrict word) {
  bool is_ok = true;

  for (size_t i = 0; word->length > i; ++i) {
    if (word->at_pos_colors[i] == TYPOS_COLOR_ERROR) {
      is_ok = false;
      break;
    }
  }

  return is_ok;
}

inline void typing_text_iterate(typing_text_t *text) {
  const bool is_accessible_at_word =
      !!text && !!text->words && !!text->words[text->current_word_pos];
  typing_word_t *word = NULL;
  bool is_accessible_at_char = false;

  if (is_accessible_at_word) {
    word = text->words[text->current_word_pos];
    is_accessible_at_char = !!word->string[word->pos];
  }

  if (is_accessible_at_word && !is_accessible_at_char) {
    if (text->current_word_pos != text->length) {
      ++text->current_word_pos;
      output_clean_prev_word();
    }

    bool is_word_ok = typing_test_is_word_ok(word);
    word->string_color = is_word_ok ? TYPOS_COLOR_OK : TYPOS_COLOR_ERROR;

  } else if (word) {
    ++word->pos;
  }

  if (!word) {
    output_clean_prev_word();
    text->current_word_pos = 0;
    for (size_t i = 0; text->length > i; ++i) {
      typing_word_t *word = text->words[i];
      word->pos = 0;
      bzero(word->at_pos_colors, sizeof(*word->at_pos_colors) * word->length);
    }
  }
}

inline void typing_text_backspace(typing_text_t *text) {
  typing_word_t *word = text->words[text->current_word_pos];

  if (!word->pos && text->current_word_pos) {
    --text->current_word_pos;
  } else {
    if (word->pos) {
      --word->pos;
    }
    word->at_pos_colors[word->pos] = TYPOS_COLOR_DEFAULT;

    bool is_word_ok = typing_test_is_word_ok(word);
    if (is_word_ok && word->pos) {
      word->string_color = TYPOS_COLOR_OK;
    } else {
      word->string_color = TYPOS_COLOR_DEFAULT;
    }
  }
}

inline typing_word_t **typing_get_words(const typing_text_t *restrict text) {
  return text ? text->words : NULL;
}

inline typing_word_t *
typing_get_current_word(const typing_text_t *restrict text) {
  typing_word_t **words = typing_get_words(text);

  return words ? words[text->current_word_pos] : NULL;
}
inline char *typing_get_current_string(const typing_text_t *restrict text) {
  typing_word_t *word = typing_get_current_word(text);

  return word ? word->string : NULL;
}
inline char typing_get_current_char(const typing_text_t *restrict text) {
  typing_word_t *word = typing_get_current_word(text);

  return (word && word->string) ? word->string[word->pos] : 0;
}

inline size_t typing_get_current_word_pos(const typing_text_t *restrict text) {
  return text ? text->current_word_pos : 0;
}
inline size_t typing_get_current_ch_pos(const typing_text_t *restrict text) {
  typing_word_t *word = typing_get_current_word(text);

  return word ? word->pos : 0;
}

inline int typing_get_input(void) {
  int ch = 0;

  curs_set(1);

  while ((ch = getch())) {
    if (isprint(ch) || ch == TYPING_KEY_DEL || ch == TYPING_KEY_ESC) {
      break;
    }
    napms(50);
  }

  curs_set(0);

  return ch;
}

inline bool typing_validate_input(const typing_word_t *restrict word,
                                  const int input) {
  if (!word)
    return true;

  const int current_ch_pos = word->pos;
  const char current_ch = word->string[current_ch_pos];
  bool is_input_ok = true;

  if (current_ch) {
    is_input_ok = (current_ch == input);
    if (is_input_ok) {
      word->at_pos_colors[current_ch_pos] = TYPOS_COLOR_OK;
    } else {
      word->at_pos_colors[current_ch_pos] = TYPOS_COLOR_ERROR;
    }
  } else if (!current_ch && input != ' ') {
    is_input_ok = false;
  }

  return is_input_ok;
}
