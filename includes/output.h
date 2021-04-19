#ifndef OUTPUT_H
#define OUTPUT_H

#include "colorize.h"
#include "typing_service.h"

extern const int output_line_text_y_default;
extern int output_line_text_y;
extern int output_line_text_x;
extern int output_line_input_shift_y;
extern int output_line_input_x;
extern int output_line_info_shift_y;
extern int output_line_info_x;

extern int output_line_text_inc_y(void);
extern int output_line_text_reset_y(void);
extern int output_line_text_get_y(void);
extern int output_line_text_get_x(void);
extern int output_line_text_delimiter_get_y(void);

extern int output_line_input_get_y(void);
extern int output_line_input_update_x(size_t word_len);
extern int output_line_input_get_x(void);

extern int output_line_info_get_y(void);
extern int output_line_info_get_x(void);

extern void output_text(const typing_text_t *restrict text);
extern void output_text_delimiter(void);
extern void output_clean_prev_word(void);
extern void output_current_word(const typing_word_t *restrict word,
                                int input_ch);

extern void output_input_status(const char current_ch, const bool is_input_ok);
#endif /* OUTPUT_H */
