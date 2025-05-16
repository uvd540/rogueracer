#pragma once

#include "globals.h"
#include "raylib.h"

#include "car.h"
#include "history_node.h"

typedef struct {
  bool move;
  bool debug;
} GameInputs;

typedef struct {
  bool        debug_mode;
  // game entities
  Car         car_current;
  Car         car_destination;
  bool        destination_valid;
  HistoryNode history_nodes[MAX_MOVES];
  // rendering
  Camera2D    camera;
  Texture2D   car_texture;
  // move animation
  bool        is_moving;
  Timer       move_timer;
  float       move_progress; // a float of range [0, 1] that indicates the progress of the current move animation
  // inputs
  GameInputs  inputs;
} Game;

void game_init(Game *game);
void game_handle_inputs(Game *game);
void game_update(Game *game, float dt, double current_time);
void game_draw(Game *game);
void game_shutdown(Game *game);
