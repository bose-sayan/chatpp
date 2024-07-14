#include "helper.hpp"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

std::string get_current_time() {
  auto now = std::chrono::system_clock::now();
  auto timestamp = std::chrono::system_clock::to_time_t(now);
  auto utcTime = std::gmtime(&timestamp);
  std::stringstream ss;
  ss << std::put_time(utcTime, "%Y-%m-%d %H:%M:%S");
  return ss.str();
}

void Logger::log(const std::string &message) {
  std::cout << get_current_time() << " - " << __LINE__ << " : " << message
            << std::endl;
}