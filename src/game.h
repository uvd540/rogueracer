#pragma once

#include "globals.h"
#include "raylib.h"

#include "car.h"
#include "history_node.h"

typedef struct {
  Texture2D car_texture;
  Car       car_current;
  Car       car_destination;
  bool      destination_valid;
  Camera2D  camera;
  HistoryNode history_nodes[MAX_MOVES];
} Game;

void game_init(Game *game);
void game_update(Game *game, float dt, double current_time);
void game_draw(Game *game);
void game_shutdown(Game *game);
