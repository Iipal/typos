#ifndef TYPING_SERVICE_H
#define TYPING_SERVICE_H

#include <assert.h>
#include <stdlib.h>
#include <string.h>

const char *__test_strings[] = {
    "text",   "test",   "spring", "lmao", "vm", "syka", "vim",  "emacs", "ls",
    "design", "chunks", "alias",  "cd",   "mv", ":3",   "damn", "text",  "test",
};
const size_t __test_strings_length =
    sizeof(__test_strings) / sizeof(*__test_strings);

typedef struct s_typing_word {
  char *string;
  size_t pos;
  size_t length;
  enum e_colorize string_color;
  enum e_colorize *at_pos_colors;
} typing_word_t;
typedef typing_word_t **typing_t;

static typing_t g_typing_text = NULL;
static size_t g_typing_text_length = 0;
static size_t g_typing_iterator_at_word = 0;

static inline typing_t typing_init_text() {
  g_typing_text_length = __test_strings_length;
  assert((g_typing_text =
              calloc(g_typing_text_length + 1, sizeof(*g_typing_text))));
  for (size_t i = 0; g_typing_text_length > i; ++i) {
    const size_t word_length = strlen(__test_strings[i]);
    char *word = NULL;
    enum e_colorize *colors = NULL;
    assert((word = strdup(__test_strings[i])));
    assert((colors = calloc(sizeof(enum e_colorize), word_length)));
    assert((g_typing_text[i] = calloc(sizeof(typing_word_t), 1)));
    memcpy(g_typing_text[i],
           &(typing_word_t){word, 0, strlen(word), TYPOS_COLOR_DEFAULT, colors},
           sizeof(typing_word_t));
  }
  return g_typing_text;
}

static inline void typing_iterate() {
  const bool is_accessible_at_word =
      !!g_typing_text && !!g_typing_text[g_typing_iterator_at_word];
  typing_word_t *word = NULL;
  bool is_accessible_at_char = false;

  if (is_accessible_at_word) {
    word = g_typing_text[g_typing_iterator_at_word];
    is_accessible_at_char = !!word->string[word->pos];
  }

  if (is_accessible_at_word && !is_accessible_at_char) {
    if (g_typing_iterator_at_word != g_typing_text_length) {
      ++g_typing_iterator_at_word;
    }
  } else if (word) {
    ++word->pos;
  }

  if (!is_accessible_at_word && !word) {
    g_typing_iterator_at_word = 0;
    for (size_t i = 0; g_typing_text_length > i; ++i) {
      typing_word_t *word = g_typing_text[i];
      word->pos = 0;
      bzero(word->at_pos_colors, sizeof(*word->at_pos_colors) * word->length);
    }
  }
}
static inline void typing_backspace() {
  typing_word_t *word = g_typing_text[g_typing_iterator_at_word];

  if (!word->pos && g_typing_iterator_at_word) {
    --g_typing_iterator_at_word;
  } else {
    if (word->pos) {
      --word->pos;
    }
    word->at_pos_colors[word->pos] = TYPOS_COLOR_DEFAULT;
  }
}

static inline typing_t typing_get_text() { return g_typing_text; }

static inline typing_word_t *typing_get_current_word() {
  return typing_get_text()[g_typing_iterator_at_word];
}
static inline char *typing_get_current_string() {
  return typing_get_current_word()->string;
}
static inline char typing_get_current_char() {
  typing_word_t *word = typing_get_current_word();
  return word->string[word->pos];
}

static inline size_t typing_get_current_at_word() {
  return g_typing_iterator_at_word;
}
static inline size_t typing_get_current_ch_pos() {
  return typing_get_current_word()->pos;
}

#endif /* TYPING_SERVICE_H */
