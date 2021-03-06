// Copyright (c) 2018 Gwangmin Lee
#ifndef SRC_TIMER_H_
#define SRC_TIMER_H_

#include <chrono> // NOLINT
#include <vector>
#include <utility>
#include <string>

using TimerOptionType = size_t;
enum class TimerOption : TimerOptionType { None = 0, IncludeNow };

template <class T>
class Timer {
 public:
  explicit Timer(const std::string& description = "");
  ~Timer();
  void Split(const std::string& description);
  std::vector<std::pair<std::string, T>> GetRecords(const TimerOption& option = TimerOption::None) const;
  std::vector<typename T::rep> GetCounts(const TimerOption& option = TimerOption::None) const;
  void SetVerbose(bool verbose) { verbose_ = verbose; }
  bool Verbose() const { return verbose_; }

 private:
  std::chrono::time_point<std::chrono::steady_clock> begin_, split_;
  std::string description_;
  std::string time_suffix_;
  std::vector<std::pair<std::string, T>> splits_;
  bool verbose_ = true;
};

#endif // SRC_TIMER_H_
