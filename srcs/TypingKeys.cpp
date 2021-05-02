#include "typos.hpp"

chtype TypingKeys::get_input(void) {
  chtype ch = 0;

  curs_set(1);

  while ((ch = getch())) {
    if (~0u != ch && TypingKeys::is_valid_input_key(ch)) {
      break;
    }
    napms(25);
  }

  curs_set(0);

  return ch;
}

bool TypingKeys::is_valid_input_key(chtype input) { return _valid_keys[input]; }

#pragma clang diagnostic ignored "-Wc99-designator"

const bool TypingKeys::_valid_keys[KEY_MAX] = {
    [TypingKeys::KEY_CTRL_C] = true,
    [TypingKeys::KEY_CTRL_D] = true,
    [TypingKeys::KEY_CTRL_BACKSPACE] = true,
    [TypingKeys::KEY_TAB] = true,
    [TypingKeys::KEY_NEW_LINE] = true,
    [TypingKeys::KEY_CTRL_R] = true,
    [TypingKeys::KEY_CTRL_S] = true,
    [TypingKeys::KEY_ESC] = true,

    [TypingKeys::KEY_SPACE] = true,
    [TypingKeys::KEY_EXC_MARK] = true,
    [TypingKeys::KEY_QUOTE] = true,
    [TypingKeys::KEY_NUMBER_SIGN] = true,
    [TypingKeys::KEY_DOLLAR_SIGN] = true,
    [TypingKeys::KEY_PERCENT_SIGN] = true,
    [TypingKeys::KEY_AMPERSAND] = true,
    [TypingKeys::KEY_APOSTROPHE] = true,
    [TypingKeys::KEY_RND_BRACKET_OPEN] = true,
    [TypingKeys::KEY_RND_BRACKET_CLOSE] = true,
    [TypingKeys::KEY_ASTERISK] = true,
    [TypingKeys::KEY_PLUS_SIGN] = true,
    [TypingKeys::KEY_COMMA] = true,
    [TypingKeys::KEY_HYPHEN] = true,
    [TypingKeys::KEY_DOT] = true,
    [TypingKeys::KEY_SLASH] = true,
    [TypingKeys::KEY_ZERO] = true,
    [TypingKeys::KEY_ONE] = true,
    [TypingKeys::KEY_TWO] = true,
    [TypingKeys::KEY_THREE] = true,
    [TypingKeys::KEY_FOUR] = true,
    [TypingKeys::KEY_FIVE] = true,
    [TypingKeys::KEY_SIX] = true,
    [TypingKeys::KEY_SEVEN] = true,
    [TypingKeys::KEY_EIGHT] = true,
    [TypingKeys::KEY_NINE] = true,
    [TypingKeys::KEY_COLON] = true,
    [TypingKeys::KEY_SEMICOLON] = true,
    [TypingKeys::KEY_LESS_SIGN] = true,
    [TypingKeys::KEY_EQUALS_SIGN] = true,
    [TypingKeys::KEY_GREATER_SIGN] = true,
    [TypingKeys::KEY_QUESTION] = true,
    [TypingKeys::KEY_AT_SIGN] = true,
    [TypingKeys::KEY_A] = true,
    [TypingKeys::KEY_B] = true,
    [TypingKeys::KEY_C] = true,
    [TypingKeys::KEY_D] = true,
    [TypingKeys::KEY_E] = true,
    [TypingKeys::KEY_F] = true,
    [TypingKeys::KEY_G] = true,
    [TypingKeys::KEY_H] = true,
    [TypingKeys::KEY_I] = true,
    [TypingKeys::KEY_J] = true,
    [TypingKeys::KEY_K] = true,
    [TypingKeys::KEY_L] = true,
    [TypingKeys::KEY_M] = true,
    [TypingKeys::KEY_N] = true,
    [TypingKeys::KEY_O] = true,
    [TypingKeys::KEY_P] = true,
    [TypingKeys::KEY_Q] = true,
    [TypingKeys::KEY_R] = true,
    [TypingKeys::KEY_S] = true,
    [TypingKeys::KEY_T] = true,
    [TypingKeys::KEY_U] = true,
    [TypingKeys::KEY_V] = true,
    [TypingKeys::KEY_W] = true,
    [TypingKeys::KEY_X] = true,
    [TypingKeys::KEY_Y] = true,
    [TypingKeys::KEY_Z] = true,
    [TypingKeys::KEY_SQR_BRACKET_OPEN] = true,
    [TypingKeys::KEY_BACKS_LASH] = true,
    [TypingKeys::KEY_SQR_BRACKET_CLOSE] = true,
    [TypingKeys::KEY_CARET] = true,
    [TypingKeys::KEY_UNDERSCORE] = true,
    [TypingKeys::KEY_GRAVE] = true,
    [TypingKeys::KEY_a] = true,
    [TypingKeys::KEY_b] = true,
    [TypingKeys::KEY_c] = true,
    [TypingKeys::KEY_d] = true,
    [TypingKeys::KEY_e] = true,
    [TypingKeys::KEY_f] = true,
    [TypingKeys::KEY_g] = true,
    [TypingKeys::KEY_h] = true,
    [TypingKeys::KEY_i] = true,
    [TypingKeys::KEY_j] = true,
    [TypingKeys::KEY_k] = true,
    [TypingKeys::KEY_l] = true,
    [TypingKeys::KEY_m] = true,
    [TypingKeys::KEY_n] = true,
    [TypingKeys::KEY_o] = true,
    [TypingKeys::KEY_p] = true,
    [TypingKeys::KEY_q] = true,
    [TypingKeys::KEY_r] = true,
    [TypingKeys::KEY_s] = true,
    [TypingKeys::KEY_t] = true,
    [TypingKeys::KEY_u] = true,
    [TypingKeys::KEY_v] = true,
    [TypingKeys::KEY_w] = true,
    [TypingKeys::KEY_x] = true,
    [TypingKeys::KEY_y] = true,
    [TypingKeys::KEY_z] = true,
    [TypingKeys::KEY_CRL_BRACKET_OPEN] = true,
    [TypingKeys::KEY_VERTICAL_SLASH] = true,
    [TypingKeys::KEY_CRL_BRACKET_CLOSE] = true,
    [TypingKeys::KEY_TILDE] = true,

    [TypingKeys::KEY_ARROW_LEFT] = true,
    [TypingKeys::KEY_ARROW_RIGHT] = true,
    [TypingKeys::KEY_DEL] = true,
};
