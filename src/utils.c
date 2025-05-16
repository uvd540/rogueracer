#include "utils.h"
#include <math.h>

float angle_wrap_zero_tau(float angle) {
  float result = fmodf(angle, 2.0f * TAU);
  if (result < 0.0f) {
    result += TAU;
  }
  return result;
}
bool is_angle_between(float angle, float min, float max) {
  angle = angle_wrap_zero_tau(angle);
  min = angle_wrap_zero_tau(min);
  max = angle_wrap_zero_tau(max);
  if (min <= max) {
    return angle >= min && angle <= max;
  } else {
    return angle >= min || angle <= max;
  }
}
