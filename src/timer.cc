// Copyright (c) 2018 Gwangmin Lee
#include <timer.h>
#include <chrono> // NOLINT
#include <iostream>
#include <type_traits>
#include <vector>

template <class T>
Timer<T>::Timer(const std::string& description)
  : begin_(std::chrono::steady_clock::now()), description_(description) {
  split_ = begin_;
  if (std::is_same<T, std::chrono::hours>()) {
    time_suffix_ = "h";
  } else if (std::is_same<T, std::chrono::minutes>()) {
    time_suffix_ = "m";
  } else if (std::is_same<T, std::chrono::seconds>()) {
    time_suffix_ = "s";
  } else if (std::is_same<T, std::chrono::milliseconds>()) {
    time_suffix_ = "ms";
  } else if (std::is_same<T, std::chrono::microseconds>()) {
    time_suffix_ = "us";
  } else if (std::is_same<T, std::chrono::nanoseconds>()) {
    time_suffix_ = "ns";
  } else {
    time_suffix_ = "";
  }
}

template <class T>
Timer<T>::~Timer() {
  if (verbose_) {
    const auto now = std::chrono::steady_clock::now();
    const auto elapsed = std::chrono::duration_cast<T>(now - begin_);
    for (const auto& p : splits_) {
      std::cout << description_ << ": " << p.first << " took " << p.second.count() << time_suffix_ << "\n";
    }
    std::cout << description_ << ": Total " << elapsed.count() << time_suffix_ << "\n";
  }
}

template <class T>
void Timer<T>::Split(const std::string& description) {
  const auto now = std::chrono::steady_clock::now();
  const auto elapsed = std::chrono::duration_cast<T>(now - split_);
  splits_.emplace_back(description, elapsed);
  split_ = now;
}

template <class T>
std::vector<std::pair<std::string, T>> Timer<T>::GetRecords(const TimerOption& option) const {
  const auto now = std::chrono::steady_clock::now();
  const auto elapsed = std::chrono::duration_cast<T>(now - begin_);
  std::vector<std::pair<std::string, T>> record(splits_);
  if (option == TimerOption::IncludeNow) {
    record.emplace_back(description_, elapsed);
  }
  return record;
}

template <class T>
std::vector<typename T::rep> Timer<T>::GetCounts(const TimerOption& option) const {
  const auto now = std::chrono::steady_clock::now();
  const auto elapsed = std::chrono::duration_cast<T>(now - begin_);
  std::vector<typename T::rep> record;
  record.reserve(splits_.size() + 1);
  for (const auto& split : splits_) {
    record.emplace_back(split.second.count());
  }
  if (option == TimerOption::IncludeNow) {
    record.emplace_back(elapsed.count());
  }
  return record;
}

template class Timer<std::chrono::hours>;
template class Timer<std::chrono::minutes>;
template class Timer<std::chrono::seconds>;
template class Timer<std::chrono::milliseconds>;
template class Timer<std::chrono::microseconds>;
template class Timer<std::chrono::nanoseconds>;
