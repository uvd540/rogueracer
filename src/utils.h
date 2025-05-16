#pragma once

#include "raylib.h"

#define TAU 2*PI

float angle_wrap_zero_tau(float angle);
bool is_angle_between(float angle, float min, float max);
