// Copyright (c) 2018 Gwangmin Lee
#include <timer.h>
#include <thread> // NOLINT

int main() {
  Timer<std::chrono::milliseconds> t_ms("ms timer test");
  Timer<std::chrono::seconds> t_s("s timer test");
  std::this_thread::sleep_for(std::chrono::seconds(1));
  t_ms.Split("sleep 1 sec");
  t_s.Split("sleep 1 sec");
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  t_ms.Split("sleep 0.5 sec");
  t_s.Split("sleep 0.5 sec");

  return EXIT_SUCCESS;
}
