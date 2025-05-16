#pragma once

#include "raylib.h"

#include "car.h"

typedef struct {
  Texture2D car_texture;
  Car car_current;
  Car car_destination;
  bool destination_valid;
  Camera2D camera;
} Game;

void game_init(Game *game);
void game_update(Game *game, float dt);
void game_draw(Game *game);
void game_shutdown(Game *game);
