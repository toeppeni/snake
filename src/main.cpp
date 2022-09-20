#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "obstacles.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  
  int level;
  std::cout << "Select level 1 (easy), level 2 (intermediate) or level 3 (hard): ";
  std::cin >> level;

  Obstacles obstacles(kGridWidth,kGridHeight);
  if (level == 1){
    obstacles.ReadBoardFile("../level1.txt");
    std::cout << "You selected Level "<< level<< ". Have fun! ";
  }else if (level == 2){
    obstacles.ReadBoardFile("../level2.txt");
    std::cout << "You selected Level "<< level<< ". Have fun! ";
  }else if (level == 3){
    obstacles.ReadBoardFile("../level3.txt");
    std::cout << "You selected Level "<< level<< ". Have fun! ";
  }else{
    std::cout << "Invalid input! " << std::endl;
    std::cout << "--> Default selected (Level 1)" << std::endl;
    obstacles.ReadBoardFile("../level1.txt");
  }  

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight, obstacles);
  game.SetLevel(level);
  game.Run(controller, renderer, obstacles, kMsPerFrame);


  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScorePlayer1() << "\n";
  std::cout << "Size: " << game.GetSizePlayer2() << "\n";

  return 0;
}