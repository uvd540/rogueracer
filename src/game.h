#pragma once

#include "globals.h"
#include "raylib.h"

#include "car.h"
#include "timer.h"

// TODO: move history node to its own file
typedef enum {
  HISTORY_NODE_START,
  HISTORY_NODE_ACCLERATION,
  HISTORY_NODE_DECELERATION,
} HistoryNodeType;

typedef struct {
  bool active;
  Vector2 position;
  HistoryNodeType type;
  Timer timer;
  float inner_radius;
  float outer_radius;
} HistoryNode;

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

void history_nodes_reset(HistoryNode *history_nodes);
void history_node_init(HistoryNode *history_node, Vector2 position, HistoryNodeType type, double current_time);
void history_nodes_update(HistoryNode *history_nodes, float dt, double current_time);
void history_nodes_draw(HistoryNode *history_nodes);
