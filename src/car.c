#include "car.h"
#include "globals.h"
#include "raymath.h"

// #include <stdio.h>

void car_init(Car *car) {
  car->heading = PI / 4.0f;
  car->speed = 100.0f;
  car->acceleration = 50.0f;
  car->deceleration = 20.0f;
  car->steering = PI / 16.0f;
  car->scale = 0.4f;
}
void car_update(Car *car, float dt, double current_time) {
  float move_ratio = timer_progress_f(&car->move_timer, current_time);
  if (move_ratio <= 1.0f) {
    car->render_position = Vector2Lerp(car->render_position, car->position, timer_progress_f(&car->move_timer, current_time));
  }
  // printf("Render position: (%.4f, %.4f)\n", car->render_position.x, car->render_position.y);
  // printf("Position: (%.4f, %.4f)\n", car->position.x, car->position.y);
  // printf("%.4f\n", timer_progress_f(&car->move_timer, current_time));
}
void car_draw(Car *car, Texture2D texture, float alpha) {
  DrawTexturePro(
    texture,
    (Rectangle){0.0f, 0.0f, (float)texture.width, (float)texture.height},
    (Rectangle){car->render_position.x, car->render_position.y, texture.width * car->scale, texture.height * car->scale},
    (Vector2){texture.width * car->scale * 0.5f, texture.height * car->scale * 0.5f},
    car->heading * RAD2DEG,
    ColorAlpha(WHITE, alpha)
  );
  if (DEBUG_MODE) {
    DrawCircleV(car->render_position, 4, RED);
  }
}
