#pragma once

#include "raylib.h"
#include "timer.h"

typedef struct {
  // state
  Vector2 position;
  float heading;
  float speed;
  // stats
  float acceleration;
  float deceleration;
  float steering;
  // rendering
  Vector2 render_position;
  float scale;
  Timer move_timer;
} Car;

void car_init(Car *car);
void car_update(Car *car, float dt, double current_time);
void car_move(Car *car, double current_time);
void car_draw(Car *car, Texture2D texture, float alpha);
