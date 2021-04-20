#ifndef TYPING_SERVICE_H
#define TYPING_SERVICE_H

#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#undef TYPING_KEY_DEL
#define TYPING_KEY_DEL 0x7F
#undef TYPING_KEY_ESC
#define TYPING_KEY_ESC 0x1B
#undef TYPING_KEY_NEW_LINE
#define TYPING_KEY_NEW_LINE 0x0A
#undef TYPING_KEY_SPACE_BAR
#define TYPING_KEY_SPACE_BAR 0x20

typedef struct s_typing_word {
  char *string;
  typos_color_t *at_pos_colors;
  size_t pos;
  size_t length;
  typos_color_t string_color;
} __attribute__((aligned(__BIGGEST_ALIGNMENT__))) typing_word_t;

typedef struct s_typing_text {
  typing_word_t **words;
  size_t length;
  size_t current_word_pos;
} __attribute__((aligned(__BIGGEST_ALIGNMENT__))) typing_text_t;

extern typing_text_t *typing_text_init(const char **strings,
                                       const size_t strings_length);
extern void typing_text_free(typing_text_t *text);

extern bool typing_test_is_word_ok(const typing_word_t *restrict word);
extern void typing_text_iterate(typing_text_t *text);
extern void typing_text_backspace(typing_text_t *text);

extern typing_word_t **typing_get_words(const typing_text_t *restrict text);
extern typing_word_t *
typing_get_current_word(const typing_text_t *restrict text);
extern char *typing_get_current_string(const typing_text_t *restrict text);
extern char typing_get_current_char(const typing_text_t *restrict text);
extern size_t typing_get_current_word_pos(const typing_text_t *restrict text);
extern size_t typing_get_current_ch_pos(const typing_text_t *restrict text);

extern int typing_get_input(void);
extern bool typing_validate_input(const typing_word_t *restrict word,
                                  const int input);
#endif /* TYPING_SERVICE_H */
