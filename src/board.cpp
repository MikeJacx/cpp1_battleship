#include "../lib/board.h"
#include "../lib/consts.h"
#include <iostream>
#include <random>
#include <set>



Board::Board(const int &width, const int &height) {
  this->width = width;
  this->height = height;
  this->board = new bool *[height];
  for (int i = 0; i < height; i++) {
    this->board[i] = new bool[width];

    // changed --------------------------------------------------------------------------
    // add this loop to set all elements to false to avoid unpredictable or garbage values, which can be neither true nor false
    for (int j = 0; j < width; j++) {  
        this->board[i][j] = false;
    }
    //-----------------------------------------------------------------------------
    this->move_count = 0;
  }
}

struct Point {
  int x, y;

  Point(const int &x, int &y) {
    this->x = x;
    this->y = y;
  }

  static Point random(const int &max_width, const int &max_height) {
    std::default_random_engine random_engine(std::random_device{}());

    std::uniform_int_distribution<int> x_distribution(0, max_width - 1);
    std::uniform_int_distribution<int> y_distribution(0, max_height - 1);

    auto x = x_distribution(random_engine);
    auto y = y_distribution(random_engine);
    return Point(x, y);
  }
};

struct PointCompare {
  bool operator()(const Point &a, const Point &b) const {
    if (a.x == b.x) {
      return a.y < b.y;
    }
    return a.x < b.x;
  }
};

Board::~Board() {
  for (int i = 0; i < this->height; i++) {
    delete[] this->board[i];
  }
  delete[] this->board;
}

void Board::init(const int &num_ships) {
  std::set<Point, PointCompare> points;
  while (points.size() < num_ships) {
    auto p = Point::random(this->width, this->height);
    points.insert(p);
  }

  for (auto p : points) {
    this->board[p.x][p.y] = true;
  }
}

// changed ----------------------------------------------------------
// has_adjacent takes a point x,y and returns true if there is a ship in the cells adjacent to it

bool Board::has_adjacent(const int& x, const int& y) {

    int rows = HEIGHT;
    int cols = WIDTH;

    const int directions[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                                {0, 1},   {1, -1}, {1, 0},  {1, 1}};
  
    for (const auto &dir : directions) {
        int new_x = x + dir[0];
        int new_y = y + dir[1];

        if (new_x >= 0 && new_x < rows && new_y >= 0 &&
            new_y < cols && this->board[new_x][new_y]) {
        return true;
        }
    }
  return false;
}
//-----------------------------------------------------------------------

ResponseType Board::guess(const int &x, const int &y) {
  this->move_count += 1;
  if (this->board[x][y]) {
    return ResponseType::HIT;
  }
  return this->has_adjacent(x, y) ? ResponseType::NEARMISS : ResponseType::MISS;
}

void Board::print() {
  for (int i = 0; i < this->height; i++) {
    for (int j = 0; j < this->width; j++) {
      std::cout << this->board[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

int Board::get_move_count() { return this->move_count; }
