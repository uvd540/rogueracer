#pragma once

#include "raylib.h"

typedef enum {
  HISTORY_NODE_START,
  HISTORY_NODE_ACCLERATION,
  HISTORY_NODE_DECELERATION,
} HistoryNodeType;

typedef struct {
  bool active;
  Vector2 position;
  HistoryNodeType type;
  float inner_radius;
  float outer_radius;
} HistoryNode;

void history_nodes_reset(HistoryNode *history_nodes);
void history_node_init(HistoryNode *history_node, Vector2 position, HistoryNodeType type, double current_time);
void history_nodes_draw(HistoryNode *history_nodes);
