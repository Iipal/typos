#pragma once
#include "typos.hpp"

class Words {
public:
  static std::vector<std::string> get_words(size_t n_words);

private:
  Words();

  static std::vector<std::string> _get_alpha_words(size_t n_words);
  static std::vector<std::string> _get_random_words(size_t n_words);
};
