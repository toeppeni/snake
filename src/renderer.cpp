#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}
void Renderer::RenderSnake(Snake const snake){
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Render snake's body
  if (snake.alive) {
    if(!snake.poison_mode){
      SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF); // normal mode
    }else{
      SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xFF, 0x30, 0xFF); // poison mode
    }
  }else{
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    if(snake.id == 1){
      SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
    }else{
      SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x66, 0xB2, 0xFF);
    }
  }else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);
}

void Renderer::RenderObjects(SDL_Point const &food, SDL_Point const &poison, Obstacles const obstacles) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Render Obstacles
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x50, 0x50, 0xFF);
  auto obst = obstacles.obstacle_map;
  for (int i = 0; i<32; i++) {
    for (int j = 0; j<32; j++) {
      if (obst[j][i] == 1){
        block.x = i * block.w;
        block.y = j * block.h;
        SDL_RenderFillRect(sdl_renderer, &block);
      }
    }
  }

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render poison
  SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xFF, 0x30, 0xFF);
  block.x = poison.x * block.w;
  block.y = poison.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

}
void Renderer::ClearScreen(){
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

}
void Renderer::UpdateScreen(){
  SDL_RenderPresent(sdl_renderer);
}
void Renderer::UpdateWindowTitle(int score1, int score2, int fps) {
  std::string title{"Blue score: " + std::to_string(score1) + ", Pink score: " + std::to_string(score2) + ", FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
void Renderer::UpdateWindowTitlePlayer1Wins(int score1, int score2, int fps) {
  std::string title{"Blue wins!!! Blue score: " + std::to_string(score1) + ", Pink score: " + std::to_string(score2) + ", FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
void Renderer::UpdateWindowTitlePlayer2Wins(int score1, int score2, int fps) {
  std::string title{"Pink wins!!! Blue score: " + std::to_string(score1) + ", Pink score: " + std::to_string(score2) + ", FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
void Renderer::UpdateWindowTitleNoWinner(int score1, int score2, int fps){
    std::string title{"Nobody wins!!! Blue score: " + std::to_string(score1) + ", Pink score: " + std::to_string(score2) + ", FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}