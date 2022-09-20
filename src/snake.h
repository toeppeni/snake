#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"
#include "obstacles.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height, int id)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}

  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y);

  Direction direction = Direction::kUp;

  int id;
  int score{0};
  float speed{0.1f};
  int size{1};
  bool alive{true};
  //bool alive1{true};
  //bool alive2{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;
  
  bool poison_mode{false};
  void SwitchControl();
  
 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
  int grid_width;
  int grid_height;
};

#endif