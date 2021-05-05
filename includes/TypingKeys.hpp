#pragma once
#include "typos.hpp"

namespace TypingKeys {
  typedef int key_t;
  // custom keybindings:

  constexpr auto KEY_CTRL_C         = 0x3;
  constexpr auto KEY_CTRL_D         = 0x4;
  constexpr auto KEY_CTRL_BACKSPACE = 0x8;
  constexpr auto KEY_TAB            = 0x9;
  constexpr auto KEY_NEW_LINE       = 0x0A;
  constexpr auto KEY_CTRL_R         = 0x12;
  constexpr auto KEY_CTRL_S         = 0x13;
  constexpr auto KEY_ESC            = 0x1B;

  // isprint(3) valid characters:

  constexpr auto KEY_SPACE             = ' ';
  constexpr auto KEY_EXC_MARK          = '!';
  constexpr auto KEY_QUOTE             = '"';
  constexpr auto KEY_NUMBER_SIGN       = '#';
  constexpr auto KEY_DOLLAR_SIGN       = '$';
  constexpr auto KEY_PERCENT_SIGN      = '%';
  constexpr auto KEY_AMPERSAND         = '&';
  constexpr auto KEY_APOSTROPHE        = '\'';
  constexpr auto KEY_RND_BRACKET_OPEN  = '(';
  constexpr auto KEY_RND_BRACKET_CLOSE = ')';
  constexpr auto KEY_ASTERISK          = '*';
  constexpr auto KEY_PLUS_SIGN         = '+';
  constexpr auto KEY_COMMA             = ',';
  constexpr auto KEY_HYPHEN            = '-';
  constexpr auto KEY_DOT               = '.';
  constexpr auto KEY_SLASH             = '/';
  constexpr auto KEY_ZERO              = '0';
  constexpr auto KEY_ONE               = '1';
  constexpr auto KEY_TWO               = '2';
  constexpr auto KEY_THREE             = '3';
  constexpr auto KEY_FOUR              = '4';
  constexpr auto KEY_FIVE              = '5';
  constexpr auto KEY_SIX               = '6';
  constexpr auto KEY_SEVEN             = '7';
  constexpr auto KEY_EIGHT             = '8';
  constexpr auto KEY_NINE              = '9';
  constexpr auto KEY_COLON             = ':';
  constexpr auto KEY_SEMICOLON         = ';';
  constexpr auto KEY_LESS_SIGN         = '<';
  constexpr auto KEY_EQUALS_SIGN       = '=';
  constexpr auto KEY_GREATER_SIGN      = '>';
  constexpr auto KEY_QUESTION          = '?';
  constexpr auto KEY_AT_SIGN           = '@';
  constexpr auto KEY_A                 = 'A';
  constexpr auto KEY_B                 = 'B';
  constexpr auto KEY_C                 = 'C';
  constexpr auto KEY_D                 = 'D';
  constexpr auto KEY_E                 = 'E';
  constexpr auto KEY_F                 = 'F';
  constexpr auto KEY_G                 = 'G';
  constexpr auto KEY_H                 = 'H';
  constexpr auto KEY_I                 = 'I';
  constexpr auto KEY_J                 = 'J';
  constexpr auto KEY_K                 = 'K';
  constexpr auto KEY_L                 = 'L';
  constexpr auto KEY_M                 = 'M';
  constexpr auto KEY_N                 = 'N';
  constexpr auto KEY_O                 = 'O';
  constexpr auto KEY_P                 = 'P';
  constexpr auto KEY_Q                 = 'Q';
  constexpr auto KEY_R                 = 'R';
  constexpr auto KEY_S                 = 'S';
  constexpr auto KEY_T                 = 'T';
  constexpr auto KEY_U                 = 'U';
  constexpr auto KEY_V                 = 'V';
  constexpr auto KEY_W                 = 'W';
  constexpr auto KEY_X                 = 'X';
  constexpr auto KEY_Y                 = 'Y';
  constexpr auto KEY_Z                 = 'Z';
  constexpr auto KEY_SQR_BRACKET_OPEN  = '[';
  constexpr auto KEY_BACKS_LASH        = '\\';
  constexpr auto KEY_SQR_BRACKET_CLOSE = ']';
  constexpr auto KEY_CARET             = '^';
  constexpr auto KEY_UNDERSCORE        = '_';
  constexpr auto KEY_GRAVE             = '`';
  constexpr auto KEY_a                 = 'a';
  constexpr auto KEY_b                 = 'b';
  constexpr auto KEY_c                 = 'c';
  constexpr auto KEY_d                 = 'd';
  constexpr auto KEY_e                 = 'e';
  constexpr auto KEY_f                 = 'f';
  constexpr auto KEY_g                 = 'g';
  constexpr auto KEY_h                 = 'h';
  constexpr auto KEY_i                 = 'i';
  constexpr auto KEY_j                 = 'j';
  constexpr auto KEY_k                 = 'k';
  constexpr auto KEY_l                 = 'l';
  constexpr auto KEY_m                 = 'm';
  constexpr auto KEY_n                 = 'n';
  constexpr auto KEY_o                 = 'o';
  constexpr auto KEY_p                 = 'p';
  constexpr auto KEY_q                 = 'q';
  constexpr auto KEY_r                 = 'r';
  constexpr auto KEY_s                 = 's';
  constexpr auto KEY_t                 = 't';
  constexpr auto KEY_u                 = 'u';
  constexpr auto KEY_v                 = 'v';
  constexpr auto KEY_w                 = 'w';
  constexpr auto KEY_x                 = 'x';
  constexpr auto KEY_y                 = 'y';
  constexpr auto KEY_z                 = 'z';
  constexpr auto KEY_CRL_BRACKET_OPEN  = '{';
  constexpr auto KEY_VERTICAL_SLASH    = '|';
  constexpr auto KEY_CRL_BRACKET_CLOSE = '}';
  constexpr auto KEY_TILDE             = '~';

  // just a shortcuts

  constexpr auto KEY_ARROW_LEFT  = KEY_LEFT;
  constexpr auto KEY_ARROW_RIGHT = KEY_RIGHT;
  constexpr auto KEY_DEL_CH      = KEY_BACKSPACE;

  constexpr auto KEY_MAPPER_MAX = KEY_DEL_CH + 1;

  key_t get_input(void);
  bool  procced_input(key_t k, void * t);
}; // namespace TypingKeys
