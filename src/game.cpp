#include "game.h"
#include <iostream>
#include "SDL.h"
#include <future>
#include <thread>

Game::Game(std::size_t grid_width, std::size_t grid_height, Obstacles& obstacles)
    : snake1(grid_width, grid_height, 1),snake2(grid_width, grid_height, 2),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
      obstacles1(obstacles) {
  PlaceFood();
  
  snake1.id = 1;
  snake1.head_x = 0;
  snake1.head_y = 15;
  snake1.direction = Snake::Direction::kRight;

  snake2.id = 2;
  snake2.head_x = 31;
  snake2.head_y = 15;
  snake2.direction = Snake::Direction::kLeft;

}
void Game::SetLevel(int level_input){
  level = level_input;
}

void Game::Run(Controller const &controller, Renderer &renderer, Obstacles &obstacles,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake1, snake2);
      
    std::vector<std::future<void>> futures;

    //futures.emplace_back(std::async(&Game::Update, std::move(snake1)));
    /*futures.emplace_back(std::async(&Snake::Update, snake2));    
    */
    for(const std::future<void> &f: futures)
      f.wait();
    

    Update(snake1);
    Update(snake2);
    CheckSnakeCollision();

    renderer.ClearScreen();
    renderer.RenderObjects(food, poison, obstacles);


    renderer.RenderSnake(snake1);
    renderer.RenderSnake(snake2);
    
    renderer.UpdateScreen();

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    int score1 = GetScorePlayer1();
    int score2 = GetScorePlayer2();
    if (frame_end - title_timestamp >= 1000) {
      if (snake1.alive && snake2.alive){
        renderer.UpdateWindowTitle(score1, score2, frame_count);
      }else if(!snake1.alive && snake2.alive){
        if(score1 < score2){
          renderer.UpdateWindowTitlePlayer2Wins(score1, score2, frame_count);
        }else{
          renderer.UpdateWindowTitle(score1, score2, frame_count);
        }
      }else if(snake1.alive && !snake2.alive){
        if(score1 > score2){
          renderer.UpdateWindowTitlePlayer1Wins(score1, score2, frame_count);
        }else{
          renderer.UpdateWindowTitle(score1, score2, frame_count);
        }
      }else{
        if(score1 > score2){
          renderer.UpdateWindowTitlePlayer1Wins(score1, score2, frame_count);
        }else if(score1 < score2){
          renderer.UpdateWindowTitlePlayer2Wins(score1, score2, frame_count);
        }else{
          renderer.UpdateWindowTitleNoWinner(score1, score2, frame_count);
        }
      }
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake1.SnakeCell(x, y) && !snake2.SnakeCell(x, y) && !obstacles1.ObstacleCell(x,y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::PlacePoison() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake1.SnakeCell(x, y) && !snake2.SnakeCell(x, y) && !obstacles1.ObstacleCell(x,y)) {
      poison.x = x;
      poison.y = y;
      return;
    }
  }
}


void Game::Update(Snake& snake) {
  if (!snake.alive) return;
  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    snake.score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    switch (level){
      case 1: snake.speed += 0.005; break;
      case 2: snake.speed += 0.02; break;
      case 3: snake.speed += 0.03; break;
    }
    snake.poison_mode = false;
  }
  // Check if there's poison over here
  if (poison.x == new_x && poison.y == new_y) {
    PlacePoison();
    // Grow snake and decrease speed.
    snake.GrowBody();
    snake.score++;
    snake.poison_mode = true;
    switch (level){
      case 1: snake.speed -= 0.02; break;
      case 2: snake.speed -= 0.02; break;
      case 3: snake.speed -= 0.01; break;
    }
    if(snake.speed < 0.05){snake.speed = 0.05;} // speed shouldn't be too slow
  }
  // Check if there's obstacle over here
  if (obstacles1.ObstacleCell(new_x, new_y) == true) {
    snake.alive = false;
  }
}

void Game::CheckSnakeCollision(){//detect collision between the 2 snakes

  SDL_Point current_head_cell1{
      static_cast<int>(snake1.head_x),
      static_cast<int>(snake1.head_y)};

  SDL_Point current_head_cell2{
      static_cast<int>(snake2.head_x),
      static_cast<int>(snake2.head_y)};
 
  for (auto const &item : snake1.body) {
    if (current_head_cell2.x == item.x && current_head_cell2.y == item.y) {
      snake2.alive = false;
    }
  }
  
  for (auto const &item : snake2.body) {
    if (current_head_cell1.x == item.x && current_head_cell1.y == item.y) {
      snake1.alive = false;
    }
  }
}



int Game::GetScorePlayer1() const { return snake1.score; }
int Game::GetScorePlayer2() const { return snake2.score; }

int Game::GetSizePlayer1() const { return snake1.size; }
int Game::GetSizePlayer2() const { return snake2.size; }