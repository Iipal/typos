#pragma once
#include "typos.hpp"

#if defined(TYPOS_DEBUG) || defined(TYPOS_SANITIZE)
#  define LOGGER_IS_DEFINED 1

#  define LOGGER_FILE "./typos.debug.log"
#  define LOGGER_WRITE(...) \
    { \
      Logger _l(__FILE__, __LINE__); \
      _l << __VA_ARGS__; \
    }

class Logger {
protected:
  std::ofstream __log_file;

public:
  Logger(const char * file, int line) {
    try {
      if (!__log_file.is_open()) {
        __log_file.open(LOGGER_FILE, std::ios::app);

        time_t now  = time(0);
        tm *   _tmp = localtime(&now);
        __log_file << std::put_time(_tmp, "%y.%m.%d-%T") << " ";
        __log_file.width(23);
        __log_file << std::left << file << ":";
        __log_file.width(4);
        __log_file << std::left << line << ": ";
      }
    } catch (std::exception & e) {
      endwin();
      std::cerr << "Can't open or write to `" LOGGER_FILE "`: " << e.what() << std::endl;
      exit(EXIT_FAILURE);
    }
  }

  ~Logger() {
    if (__log_file.is_open()) {
      __log_file << std::endl;
      __log_file.close();
    }
  }

  template <typename ARGS> std::ofstream & operator<<(const ARGS & args) {
    __log_file << args;
    return __log_file;
  };
};

#else

#  define LOGGER_IS_DEFINED 0

#endif
