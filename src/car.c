#include "car.h"
#include "globals.h"

void car_init(Car *car) {
  car->heading = PI / 4.0f;
  car->speed = 100.0f;
  car->acceleration = 50.0f;
  car->deceleration = 20.0f;
  car->steering = PI / 16.0f;
  car->scale = 0.4f;
}
// void car_update(Car *car, float dt);
void car_draw(Car *car, Texture2D texture, float alpha) {
  DrawTexturePro(
    texture,
    (Rectangle){0.0f, 0.0f, (float)texture.width, (float)texture.height},
    (Rectangle){car->position.x, car->position.y, texture.width * car->scale, texture.height * car->scale},
    (Vector2){texture.width * car->scale * 0.5f, texture.height * car->scale * 0.5f},
    car->heading * RAD2DEG,
    ColorAlpha(WHITE, alpha)
  );
  if (DEBUG_MODE) {
    DrawCircleV(car->position, 4, RED);
  }
}
