#include "timer.h"

void timer_init(Timer *timer, bool repeating, double duration, double current_time) {
  timer->active = true;
  timer->repeating = repeating;
  timer->duration = duration;
  timer->start_time = current_time;
}

bool timer_is_finished(Timer *timer, double current_time) {
  if (current_time > timer->start_time + timer->duration) {
    if (timer->repeating) {
      timer->start_time += timer->duration;
    } else {
      timer->active = false;
    }
    return true;
  }
  return false;
}
