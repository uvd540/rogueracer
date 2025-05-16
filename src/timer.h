#pragma once

#include <stdbool.h>

typedef struct Timer {
  bool active;
  bool repeating;
  double duration;
  double start_time;
} Timer;

void timer_init(Timer *timer, bool repeating, double duration, double current_time);
bool timer_is_finished(Timer* timer, double current_time);
