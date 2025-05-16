#pragma once

#include "globals.h"
#include "raylib.h"

#include "car.h"
#include "history_node.h"

// TODO: move move_progress from car.c to game.c
typedef struct {
  bool        debug_mode;
  Texture2D   car_texture;
  Car         car_current;
  Car         car_destination;
  bool        destination_valid;
  Camera2D    camera;
  HistoryNode history_nodes[MAX_MOVES];
  bool        is_moving;
  Timer       move_timer;
  float       move_progress; // a float of range [0, 1] that indicates the progress of the current move animation
} Game;

void game_init(Game *game);
void game_update(Game *game, float dt, double current_time);
void game_draw(Game *game);
void game_shutdown(Game *game);
