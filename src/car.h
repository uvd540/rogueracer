#pragma once

#include "raylib.h"

typedef struct {
  Vector2 position;
  float heading;
  float speed;
  float acceleration;
  float deceleration;
  float steering;
  float scale;
} Car;

void car_init(Car *car);
// void car_update(Car *car, float dt);
void car_draw(Car *car, Texture2D texture, float alpha);
