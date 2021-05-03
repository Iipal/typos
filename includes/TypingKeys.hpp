#pragma once
#include "typos.hpp"

namespace TypingKeys {
// custom keybindings:

const chtype KEY_CTRL_C = 0x3;
const chtype KEY_CTRL_D = 0x4;
const chtype KEY_CTRL_BACKSPACE = 0x8;
const chtype KEY_TAB = 0x9;
const chtype KEY_NEW_LINE = 0x0A;
const chtype KEY_CTRL_R = 0x12;
const chtype KEY_CTRL_S = 0x13;
const chtype KEY_ESC = 0x1B;

// isprint(3) valid characters:

const chtype KEY_SPACE = ' ';
const chtype KEY_EXC_MARK = '!';
const chtype KEY_QUOTE = '"';
const chtype KEY_NUMBER_SIGN = '#';
const chtype KEY_DOLLAR_SIGN = '$';
const chtype KEY_PERCENT_SIGN = '%';
const chtype KEY_AMPERSAND = '&';
const chtype KEY_APOSTROPHE = '\'';
const chtype KEY_RND_BRACKET_OPEN = '(';
const chtype KEY_RND_BRACKET_CLOSE = ')';
const chtype KEY_ASTERISK = '*';
const chtype KEY_PLUS_SIGN = '+';
const chtype KEY_COMMA = ',';
const chtype KEY_HYPHEN = '-';
const chtype KEY_DOT = '.';
const chtype KEY_SLASH = '/';
const chtype KEY_ZERO = '0';
const chtype KEY_ONE = '1';
const chtype KEY_TWO = '2';
const chtype KEY_THREE = '3';
const chtype KEY_FOUR = '4';
const chtype KEY_FIVE = '5';
const chtype KEY_SIX = '6';
const chtype KEY_SEVEN = '7';
const chtype KEY_EIGHT = '8';
const chtype KEY_NINE = '9';
const chtype KEY_COLON = ':';
const chtype KEY_SEMICOLON = ';';
const chtype KEY_LESS_SIGN = '<';
const chtype KEY_EQUALS_SIGN = '=';
const chtype KEY_GREATER_SIGN = '>';
const chtype KEY_QUESTION = '?';
const chtype KEY_AT_SIGN = '@';
const chtype KEY_A = 'A';
const chtype KEY_B = 'B';
const chtype KEY_C = 'C';
const chtype KEY_D = 'D';
const chtype KEY_E = 'E';
const chtype KEY_F = 'F';
const chtype KEY_G = 'G';
const chtype KEY_H = 'H';
const chtype KEY_I = 'I';
const chtype KEY_J = 'J';
const chtype KEY_K = 'K';
const chtype KEY_L = 'L';
const chtype KEY_M = 'M';
const chtype KEY_N = 'N';
const chtype KEY_O = 'O';
const chtype KEY_P = 'P';
const chtype KEY_Q = 'Q';
const chtype KEY_R = 'R';
const chtype KEY_S = 'S';
const chtype KEY_T = 'T';
const chtype KEY_U = 'U';
const chtype KEY_V = 'V';
const chtype KEY_W = 'W';
const chtype KEY_X = 'X';
const chtype KEY_Y = 'Y';
const chtype KEY_Z = 'Z';
const chtype KEY_SQR_BRACKET_OPEN = '[';
const chtype KEY_BACKS_LASH = '\\';
const chtype KEY_SQR_BRACKET_CLOSE = ']';
const chtype KEY_CARET = '^';
const chtype KEY_UNDERSCORE = '_';
const chtype KEY_GRAVE = '`';
const chtype KEY_a = 'a';
const chtype KEY_b = 'b';
const chtype KEY_c = 'c';
const chtype KEY_d = 'd';
const chtype KEY_e = 'e';
const chtype KEY_f = 'f';
const chtype KEY_g = 'g';
const chtype KEY_h = 'h';
const chtype KEY_i = 'i';
const chtype KEY_j = 'j';
const chtype KEY_k = 'k';
const chtype KEY_l = 'l';
const chtype KEY_m = 'm';
const chtype KEY_n = 'n';
const chtype KEY_o = 'o';
const chtype KEY_p = 'p';
const chtype KEY_q = 'q';
const chtype KEY_r = 'r';
const chtype KEY_s = 's';
const chtype KEY_t = 't';
const chtype KEY_u = 'u';
const chtype KEY_v = 'v';
const chtype KEY_w = 'w';
const chtype KEY_x = 'x';
const chtype KEY_y = 'y';
const chtype KEY_z = 'z';
const chtype KEY_CRL_BRACKET_OPEN = '{';
const chtype KEY_VERTICAL_SLASH = '|';
const chtype KEY_CRL_BRACKET_CLOSE = '}';
const chtype KEY_TILDE = '~';

// just a shortcuts

const chtype KEY_ARROW_LEFT = KEY_LEFT;
const chtype KEY_ARROW_RIGHT = KEY_RIGHT;
const chtype KEY_DEL = KEY_BACKSPACE;

chtype get_input(void);
}; // namespace TypingKeys
