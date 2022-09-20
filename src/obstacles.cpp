#include <obstacles.h>

enum class State {kEmpty, kObstacle};

vector<int> Obstacles::ParseLine(string line) {
    istringstream sline(line);
    int n;
    char c;
    vector<int> row;
    while (sline >> n >> c && c == ',') {
      row.push_back(n);
    }
    return row;
}

void Obstacles::ReadBoardFile(string path) {
  ifstream myfile (path);
  vector<vector<int>> board{};
  if (myfile) {
    string line;
    while (getline(myfile, line)) {
      vector<int> row = ParseLine(line);
      board.push_back(row);
    }
  }
  obstacle_map = board; ////////////////!
  //return board;
}

void Obstacles::PrintBoard(const vector<vector<int>> board) {
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[i].size(); j++) {
      std::cout << board[i][j];
    }
    cout << "\n";
  }
}

bool Obstacles::ObstacleCell(int x, int y){
  if (obstacle_map[y][x] == 1){
    return true;
  }else{
    return false;
  }
}

