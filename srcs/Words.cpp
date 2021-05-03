#include "typos.hpp"
#include <cstdlib>
#include <ctime>

#include "./WORDS.cpp"

Words::Words() {}

std::vector<std::string_view> Words::get_words(size_t n_words) {
  std::srand(std::time(0));

  if (Flags::is_alphabetic) {
    return Words::_get_alpha_words(n_words);
  }

  return Words::_get_random_words(n_words);
}

std::vector<std::string_view> Words::_get_alpha_words(size_t n_words) {
  size_t start_slice_idx = std::rand() % (WORDS_ENG_LENGTH - n_words - 1);
  auto slice_start_iterator = WORDS_ENG.begin() + start_slice_idx;
  auto slice_end_iterator = slice_start_iterator + n_words;

  std::vector<std::string_view> out;

  out.assign(slice_start_iterator, slice_end_iterator);
  out.shrink_to_fit();
  return out;
}

std::vector<std::string_view> Words::_get_random_words(size_t n_words) {
  std::vector<std::string_view> out;

  for (size_t i = 0; n_words > i; ++i) {
    size_t random_idx = std::rand() % (WORDS_ENG_LENGTH - 1);
    out.push_back(WORDS_ENG[random_idx]);
  }

  out.shrink_to_fit();
  return out;
}
