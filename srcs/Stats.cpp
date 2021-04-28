#include "typos.hpp"

#include <math.h>

int Stats::_total_characters = 0;
int Stats::_total_typos = 0;

Stats::Stats() {}

void Stats::inc_cpm(void) { ++Stats::_total_characters; }
void Stats::inc_typos(void) { ++Stats::_total_typos; }

void Stats::dec_cpm(void) { --Stats::_total_characters; }
void Stats::dec_typos(void) { --Stats::_total_typos; }

void Stats::reset_all(void) {
  Stats::reset_cpm();
  Stats::reset_typos();
}
void Stats::reset_cpm(void) { Stats::_total_characters = 0; }
void Stats::reset_typos(void) { Stats::_total_typos = 0; }

float Stats::_get_gross_wpm(void) {
  return (float)(Stats::_total_characters / 5.0f) /
         (Timer::get_elapsed_seconds() / 60.0f);
}

float Stats::get_wpm(void) {
  const float total_typos = Stats::get_typos();

  const float time_elapsed_sec = Timer::get_elapsed_seconds();
  const float time_elapsed_min = time_elapsed_sec / 60.0f;

  const float net_wpm =
      Stats::_get_gross_wpm() - (total_typos / time_elapsed_min);

  return fabs(net_wpm);
}
float Stats::get_accuracy(void) {
  const float total_typos = Stats::get_typos();
  float total_chars = Stats::get_cpm();
  if (!total_chars) {
    total_chars = 1;
  }

  return ((total_chars - total_typos) / total_chars) * 100;
}
int Stats::get_cpm(void) { return Stats::_total_characters; }
int Stats::get_typos(void) { return Stats::_total_typos; }
