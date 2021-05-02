#pragma once

typedef struct s_typing_stats_data {
  struct {
    float net_wpm;
    float net_real_wpm;
    float gross_wpm;
  } wpm;

  float cps;

  float accuracy;
  float real_accuracy;

  int corrected_typos;
  int not_corrected_typos;
  int characters;
} TypingStatsData;

struct s_typing_stats_data_fmt {
  const char *fmt;
  float value;
};

typedef std::pair<const char *, s_typing_stats_data_fmt> TypingStatsDataFmt;

#define STATS_DATA_DELIMITER                                                   \
  {                                                                            \
    "", { "", .0f }                                                            \
  }

#define STATS_SAVE_FILE_NAME "./typos.log"

class TypingStats {
public:
  TypingStats();

  void inc_chars(void);
  void inc_typos(void);
  void inc_total_typos(void);

  void dec_chars(void);
  void dec_typos(void);

  void reset_stats(void);
  void reset_chars(void);
  void reset_typos(void);
  void reset_total_typos(void);

  float get_gross_wpm(void) const;
  float get_wpm(void) const;
  float get_real_wpm(void) const;

  float get_cps(void) const;

  float get_accuracy(void) const;
  float get_real_accuracy(void) const;

  int get_chars(void) const;
  int get_typos(void) const;
  int get_total_typos(void) const;

  TypingStatsData get_stats_data(void) const;

  static TypingStatsDataFmt *get_stats_data_fmt(const TypingStatsData &data);
  static void save_stats(const TypingStatsDataFmt *const fmt);

private:
  int _total_typos;
  int _not_corrected_typos;
  int _total_characters;

  float _wpm_calc(float typos) const;
  float _acc_calc(float typos) const;
};
