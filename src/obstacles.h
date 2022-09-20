#ifndef OBSTACLES_H
#define OBSTACLES_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::cout;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;

class Obstacles{
    public:
        Obstacles(const std::size_t kGridWidth,const std::size_t kGridHeight){
            //vector<vector<int>> obstacle_map(kGridWidth, std::vector<int>(kGridHeight,0));
            
        }
      
        vector<vector<int>> obstacle_map;
        vector<int> ParseLine(string line);
        void ReadBoardFile(string path);
        void PrintBoard(const vector<vector<int>> board);
        bool ObstacleCell(int x, int y);
};

#endif