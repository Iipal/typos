#pragma once

typedef struct s_typing_stats_data {
  float gross_wpm;
  float wpm;
  float accuracy;
  int typos;
  int characters;
} TypingStatsData;

class TypingStats {
public:
  TypingStats();

  void inc_chars(void);
  void inc_typos(void);

  void dec_chars(void);
  void dec_typos(void);

  void reset_stats(void);
  void reset_chars(void);
  void reset_typos(void);

  float get_gross_wpm(void);
  float get_wpm(void);
  float get_accuracy(void);
  int get_chars(void);
  int get_typos(void);
  TypingStatsData get_stats_data(void);

private:
  int _total_typos;
  int _total_characters;
};
