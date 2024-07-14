#include <iostream>

std::string get_current_time();

class Logger {
public:
  Logger() = delete;
  static void log(const std::string &message);
};