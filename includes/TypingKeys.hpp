#pragma once
#include "typos.hpp"

struct TypingKeys {
  // custom keybindings:

  static const unsigned char KEY_CTRL_C = 0x3;
  static const unsigned char KEY_CTRL_D = 0x4;
  static const unsigned char KEY_CTRL_BACKSPACE = 0x8;
  static const unsigned char KEY_TAB = 0x9;
  static const unsigned char KEY_NEW_LINE = 0x0A;
  static const unsigned char KEY_CTRL_R = 0x12;
  static const unsigned char KEY_CTRL_S = 0x13;
  static const unsigned char KEY_ESC = 0x1B;

  // isprint(3) valid characters:

  static const unsigned char KEY_SPACE = ' ';
  static const unsigned char KEY_EXC_MARK = '!';
  static const unsigned char KEY_QUOTE = '"';
  static const unsigned char KEY_NUMBER_SIGN = '#';
  static const unsigned char KEY_DOLLAR_SIGN = '$';
  static const unsigned char KEY_PERCENT_SIGN = '%';
  static const unsigned char KEY_AMPERSAND = '&';
  static const unsigned char KEY_APOSTROPHE = '\'';
  static const unsigned char KEY_RND_BRACKET_OPEN = '(';
  static const unsigned char KEY_RND_BRACKET_CLOSE = ')';
  static const unsigned char KEY_ASTERISK = '*';
  static const unsigned char KEY_PLUS_SIGN = '+';
  static const unsigned char KEY_COMMA = ',';
  static const unsigned char KEY_HYPHEN = '-';
  static const unsigned char KEY_DOT = '.';
  static const unsigned char KEY_SLASH = '/';
  static const unsigned char KEY_ZERO = '0';
  static const unsigned char KEY_ONE = '1';
  static const unsigned char KEY_TWO = '2';
  static const unsigned char KEY_THREE = '3';
  static const unsigned char KEY_FOUR = '4';
  static const unsigned char KEY_FIVE = '5';
  static const unsigned char KEY_SIX = '6';
  static const unsigned char KEY_SEVEN = '7';
  static const unsigned char KEY_EIGHT = '8';
  static const unsigned char KEY_NINE = '9';
  static const unsigned char KEY_COLON = ':';
  static const unsigned char KEY_SEMICOLON = ';';
  static const unsigned char KEY_LESS_SIGN = '<';
  static const unsigned char KEY_EQUALS_SIGN = '=';
  static const unsigned char KEY_GREATER_SIGN = '>';
  static const unsigned char KEY_QUESTION = '?';
  static const unsigned char KEY_AT_SIGN = '@';
  static const unsigned char KEY_A = 'A';
  static const unsigned char KEY_B = 'B';
  static const unsigned char KEY_C = 'C';
  static const unsigned char KEY_D = 'D';
  static const unsigned char KEY_E = 'E';
  static const unsigned char KEY_F = 'F';
  static const unsigned char KEY_G = 'G';
  static const unsigned char KEY_H = 'H';
  static const unsigned char KEY_I = 'I';
  static const unsigned char KEY_J = 'J';
  static const unsigned char KEY_K = 'K';
  static const unsigned char KEY_L = 'L';
  static const unsigned char KEY_M = 'M';
  static const unsigned char KEY_N = 'N';
  static const unsigned char KEY_O = 'O';
  static const unsigned char KEY_P = 'P';
  static const unsigned char KEY_Q = 'Q';
  static const unsigned char KEY_R = 'R';
  static const unsigned char KEY_S = 'S';
  static const unsigned char KEY_T = 'T';
  static const unsigned char KEY_U = 'U';
  static const unsigned char KEY_V = 'V';
  static const unsigned char KEY_W = 'W';
  static const unsigned char KEY_X = 'X';
  static const unsigned char KEY_Y = 'Y';
  static const unsigned char KEY_Z = 'Z';
  static const unsigned char KEY_SQR_BRACKET_OPEN = '[';
  static const unsigned char KEY_BACKS_LASH = '\\';
  static const unsigned char KEY_SQR_BRACKET_CLOSE = ']';
  static const unsigned char KEY_CARET = '^';
  static const unsigned char KEY_UNDERSCORE = '_';
  static const unsigned char KEY_GRAVE = '`';
  static const unsigned char KEY_a = 'a';
  static const unsigned char KEY_b = 'b';
  static const unsigned char KEY_c = 'c';
  static const unsigned char KEY_d = 'd';
  static const unsigned char KEY_e = 'e';
  static const unsigned char KEY_f = 'f';
  static const unsigned char KEY_g = 'g';
  static const unsigned char KEY_h = 'h';
  static const unsigned char KEY_i = 'i';
  static const unsigned char KEY_j = 'j';
  static const unsigned char KEY_k = 'k';
  static const unsigned char KEY_l = 'l';
  static const unsigned char KEY_m = 'm';
  static const unsigned char KEY_n = 'n';
  static const unsigned char KEY_o = 'o';
  static const unsigned char KEY_p = 'p';
  static const unsigned char KEY_q = 'q';
  static const unsigned char KEY_r = 'r';
  static const unsigned char KEY_s = 's';
  static const unsigned char KEY_t = 't';
  static const unsigned char KEY_u = 'u';
  static const unsigned char KEY_v = 'v';
  static const unsigned char KEY_w = 'w';
  static const unsigned char KEY_x = 'x';
  static const unsigned char KEY_y = 'y';
  static const unsigned char KEY_z = 'z';
  static const unsigned char KEY_CRL_BRACKET_OPEN = '{';
  static const unsigned char KEY_VERTICAL_SLASH = '|';
  static const unsigned char KEY_CRL_BRACKET_CLOSE = '}';
  static const unsigned char KEY_TILDE = '~';

  // just a shortcuts

  static const chtype KEY_ARROW_LEFT = KEY_LEFT;
  static const chtype KEY_ARROW_RIGHT = KEY_RIGHT;
  static const chtype KEY_DEL = KEY_BACKSPACE;

  static chtype get_input(void);
  static bool is_valid_input_key(chtype input);

private:
  static const bool _valid_keys[KEY_MAX];
}; // namespace TypingKeys
