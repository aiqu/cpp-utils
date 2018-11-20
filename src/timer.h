// Copyright (c) 2018 Gwangmin Lee
#ifndef SRC_TIMER_H_
#define SRC_TIMER_H_

#include <chrono> // NOLINT
#include <vector>
#include <utility>
#include <string>

template <class T>
class Timer {
 public:
  explicit Timer(const std::string& description = "");
  ~Timer();
  void Split(const std::string& description);

 private:
  std::chrono::time_point<std::chrono::steady_clock> begin_, split_;
  std::string description_;
  std::string time_suffix_;
  std::vector<std::pair<std::string, T>> splits_;
};

#endif // SRC_TIMER_H_
