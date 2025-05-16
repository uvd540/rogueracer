#include "history_node.h"
#include "globals.h"

void history_nodes_reset(HistoryNode *history_nodes) {
  for (int i = 0; i < MAX_MOVES; i++) {
    history_nodes[i] = (HistoryNode){0};
  }
}

void history_node_init(HistoryNode *history_node, Vector2 position, HistoryNodeType type, double current_time) {
  // *history_node = (HistoryNode){ 0 };
  history_node->active = true;
  history_node->inner_radius = 0.0f;
  history_node->outer_radius = 6.0f;
  history_node->position = position;
  history_node->type = type;
  timer_init(&history_node->timer, false, 0.5f, current_time);
  
}

void history_nodes_update(HistoryNode *history_nodes, float dt, double current_time) {
  for (int i = 0; i < MAX_MOVES; i++) {
    if (history_nodes[i].active) {
      if (!timer_is_finished(&history_nodes[i].timer, current_time)) {
        history_nodes[i].inner_radius += 8.0f * dt;
      }
    }
  }
}
void history_nodes_draw(HistoryNode *history_nodes) {
  for (int i = 0; i < MAX_MOVES; i++) {
    if (history_nodes[i].active) {
      DrawCircleV(history_nodes[i].position, history_nodes[i].outer_radius, BLACK);
      DrawCircleV(history_nodes[i].position, history_nodes[i].inner_radius, GREEN);
    }
  }
}
