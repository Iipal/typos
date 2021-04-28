#pragma once

class Stats {
public:
  static void inc_cpm(void);
  static void inc_typos(void);

  static void dec_cpm(void);
  static void dec_typos(void);

  static void reset_all(void);
  static void reset_cpm(void);
  static void reset_typos(void);

  static float get_wpm(void);
  static float get_accuracy(void);
  static int get_cpm(void);
  static int get_typos(void);

private:
  Stats();

  static float _get_gross_wpm(void);

  static int _total_typos;
  static int _total_characters;
};
