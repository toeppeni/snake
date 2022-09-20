#ifndef GAME_H
#define GAME_H

#include <random>
#include <thread>
#include <future>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "obstacles.h"


class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, Obstacles &obstacles);
  void Run(Controller const &controller, Renderer &renderer, Obstacles &obstacles,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetScorePlayer1() const;
  int GetScorePlayer2() const;
  
  int GetSize() const;
  int GetSizePlayer1() const;
  int GetSizePlayer2() const;
  void SetLevel(const int level_input);
  void CheckSnakeCollision();
  //bool poison_mode{false};

 private:
  Snake snake1, snake2;

  Obstacles obstacles1;
  SDL_Point food;
  SDL_Point poison;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  int level{1};

  float GetSpeedDelta();
  void PlaceFood();
  void PlacePoison();
  void SwitchControl();
  void Update(Snake& snake);
};

#endif