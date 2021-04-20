#ifndef PRINT_H
#define PRINT_H

#include "colorize.h"
#include "typing.h"

extern int print_line_text_inc_y(void);
extern int print_line_text_reset_y(void);
extern int print_line_text_get_y(void);
extern int print_line_text_get_x(void);
extern int print_line_text_delimiter_get_y(void);
extern int print_line_input_get_y(void);
extern int print_line_input_update_x(size_t word_len);
extern int print_line_input_get_x(void);
extern int print_line_timer_get_y(void);
extern int print_line_timer_get_x(void);
extern int print_line_info_get_y(void);
extern int print_line_info_get_x(void);
extern int print_line_get_center_x(size_t text_len);

extern void print_text(const typing_text_t *restrict text);
extern void print_text_delimiter(void);
extern void print_timer(int seconds);
extern void print_current_word(const typing_word_t *restrict word,
                               int input_ch);

extern void print_input_status(const char current_ch, const bool is_input_ok);
#endif /* PRINT_H */
