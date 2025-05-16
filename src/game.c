#include "game.h"
#include "utils.h"
#include "raymath.h"
#include <math.h>

void game_init(Game *game) {
  game->car_texture = LoadTexture("../../assets/car_red_small_5.png");
  car_init(&game->car_current);
  car_init(&game->car_destination);
  game->camera.offset = (Vector2){400.0f, 300.0f};
  game->camera.target = game->car_current.position;
  game->camera.zoom = 1.0f;
}
void game_update(Game *game, float dt, double current_time) {
  if (DEBUG_MODE) {
    if (IsKeyDown(KEY_LEFT)) {
      game->car_current.heading -= 0.01f;
    }
    if (IsKeyDown(KEY_RIGHT)) {
      game->car_current.heading += 0.01f;
    }
  }
  game->destination_valid = false;
  Vector2 desired_position = GetScreenToWorld2D(GetMousePosition(), game->camera);
  Vector2 desired_move = Vector2Subtract(desired_position, game->car_current.position);
  float desired_speed = Vector2Length(desired_move);
  bool valid_speed = desired_speed > game->car_current.speed - game->car_current.deceleration &&
                     desired_speed < game->car_current.speed + game->car_current.acceleration;
  float desired_heading = atan2f(desired_move.y, desired_move.x);
  bool valid_heading = is_angle_between(desired_heading,
                                        game->car_current.heading - game->car_current.steering,
                                        game->car_current.heading + game->car_current.steering);
  game->destination_valid = valid_speed && valid_heading;
  if (game->destination_valid) {
    game->car_destination.position = desired_position;
    game->car_destination.heading = desired_heading;
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
      for (int i = 0; i < MAX_MOVES; i++) {
        if (!game->history_nodes[i].active) {
          history_node_init(&game->history_nodes[i], game->car_current.position, 0, current_time);
          break;
        }
      }
      game->car_current.position = game->car_destination.position;
      game->car_current.heading = game->car_destination.heading;
      game->car_current.speed = desired_speed;
    }
  }
  history_nodes_update(game->history_nodes, dt, current_time);
}
void game_draw(Game *game) {
  BeginMode2D(game->camera);
    DrawRing(
      game->car_current.position,
      game->car_current.speed - game->car_current.deceleration,
      game->car_current.speed,
      (game->car_current.heading - game->car_current.steering) * RAD2DEG,
      (game->car_current.heading + game->car_current.steering) * RAD2DEG,
      8,
      ORANGE
    );
    DrawRing(
      game->car_current.position,
      game->car_current.speed,
      game->car_current.speed + game->car_current.acceleration,
      (game->car_current.heading - game->car_current.steering) * RAD2DEG,
      (game->car_current.heading + game->car_current.steering) * RAD2DEG,
      8,
      GREEN
    );
    car_draw(&game->car_current, game->car_texture, 1.0f);
    if (game->destination_valid) {
      car_draw(&game->car_destination, game->car_texture, 0.5f);
    }
  history_nodes_draw(game->history_nodes);
  EndMode2D();
}
void game_shutdown(Game *game) {
  UnloadTexture(game->car_texture);
}

