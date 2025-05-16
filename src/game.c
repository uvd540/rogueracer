#include "game.h"
#include "raylib.h"
#include "utils.h"
#include "raymath.h"
#include <math.h>

void game_init(Game *game) {
  game->car_texture = LoadTexture(ASSETS_PATH "car_red_small_5.png");
  car_init(&game->car_current);
  car_init(&game->car_destination);
  game->camera.offset = (Vector2){400.0f, 300.0f};
  game->camera.target = game->car_current.position;
  game->camera.zoom = 1.0f;
}

void game_handle_inputs(Game *game) {
  game->inputs = (GameInputs){0};
  if (IsKeyDown(KEY_GRAVE)) {
    game->inputs.debug = true;
  }
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    game->inputs.move = true;
  }
}

void game_update(Game *game, float dt, double current_time) {
  if (game->inputs.debug) {
    game->debug_mode = !game->debug_mode;
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
    game->car_destination.render_position = desired_position;
    game->car_destination.heading = desired_heading;
    if (game->inputs.move) {
      game->is_moving = true;
      game->move_progress = 0.0f;
      timer_init(&game->move_timer, false, 0.5f, current_time);
      for (int i = 0; i < MAX_MOVES; i++) {
        if (!game->history_nodes[i].active) {
          history_node_init(&game->history_nodes[i], game->car_current.position, 0, current_time);
          break;
        }
      }
      timer_init(&game->car_current.move_timer, false, 1.0f, current_time);
      // snap the car to the last position in case
      // the user makes quick moves in succession
      game->car_current.render_position = game->car_current.position;
      game->car_current.position        = desired_position;
      game->car_current.heading         = desired_heading;
      game->car_current.speed           = desired_speed;
    }
  }
  if (game->is_moving) {
    game->move_progress = timer_progress_f(&game->move_timer, current_time);
    game->car_current.render_position = Vector2Lerp(game->car_current.render_position, game->car_current.position, game->move_progress);
    for (int i = 0; i < MAX_MOVES; i++) {
      game->history_nodes[i].inner_radius = Lerp(game->history_nodes[i].inner_radius, 0.6f * game->history_nodes[i].outer_radius, game->move_progress);
    }
    if (game->move_progress >= 1.0f) {
      game->is_moving = false;
    }
  }
  game->camera.target = game->car_current.render_position;
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
  if (game->debug_mode) {
    DrawCircleV(game->car_current.render_position, 4, RED);
  }
  EndMode2D();
}

void game_shutdown(Game *game) {
  UnloadTexture(game->car_texture);
}

