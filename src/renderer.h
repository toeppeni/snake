#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include "obstacles.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  //void Render(Snake const snake, SDL_Point const &food, SDL_Point const &poison, Obstacles const obstacles);
  void RenderSnake(Snake const snake);
  void RenderObjects(SDL_Point const &food, SDL_Point const &poison, Obstacles const obstacles);
  void ClearScreen();
  void UpdateScreen();
  void UpdateWindowTitle(int score1, int score2, int fps);
  void UpdateWindowTitlePlayer1Wins(int score1, int score2, int fps);
  void UpdateWindowTitlePlayer2Wins(int score1, int score2, int fps);
  void UpdateWindowTitleNoWinner(int score1, int score2, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif