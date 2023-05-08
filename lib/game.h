#ifndef GAME_H
#define GAME_H
#include "board.h"
#include "consts.h"
#include <iostream>

class BaseGame {
protected:
  Board * board;
  virtual int solve() = 0;
public:
  BaseGame();
  ~BaseGame();
  int run();
};


class ControlGame : public BaseGame {
protected:
    int solve() override {
        int hits = 0;
        for(int i = 0; i < HEIGHT; i++)
        {
            for(int j = 0; j < WIDTH; j++)
            {
                if(this->board->guess(i, j) == ResponseType::HIT)
                {
                    hits += 1;
                }
            }
        }
        return hits;
    }
};

class AssignmentGame : public BaseGame {
  protected:
      int solve() override {

          int hits = 0;

          // this keeps track of the cells which are checked. Initially all are false i.e. yet to be checked
          bool checked[HEIGHT][WIDTH] = { false };

          for (int i = 0; i < HEIGHT; i++) {
              for (int j = 0; j < WIDTH; j++) {

                  if ( !checked[i][j] ) {

                      // mark this cell as checked
                      checked[i][j] = true;

                      ResponseType response = this->board->guess(i, j);
                     
                      // ship found
                      if (response == ResponseType::HIT) {
                          hits += 1;
                          
                      }
                      else if (response == ResponseType::MISS) {
                          // mark adjacent cells as checked because no ship will be in the adjacent cells
                          // if there were ships in the adjacent cells it would have returned near-miss
                          
                          mark_adjacent_checked(i, j, checked);
                      }
                  }
              }
          }
          return hits;
      }

    protected:
      void mark_adjacent_checked(int row, int col, bool checked[HEIGHT][WIDTH]) {
          const int directions[8][2] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                                        {0, 1},   {1, -1}, {1, 0},  {1, 1} };
          int rows = HEIGHT;
          int cols = WIDTH;

          for (const auto& dir : directions) {
              int new_row = row + dir[0];
              int new_col = col + dir[1];

              // check for cells on the border of the board
              if (new_row >= 0 && new_row < rows && new_col >= 0 && new_col < cols) {
                  checked[new_row][new_col] = true;
              }
          }
      }

};


#endif /* GAME_H */
