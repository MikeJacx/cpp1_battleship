#ifndef GAME_H
#define GAME_H
#include "board.h"
#include "consts.h"
#include <iostream>
#include <list>
using namespace std;

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
        //IMPLEMENT YOUR SEARCH ALGORITHM HERE
       struct Guess
  {
    /* data */
    int x;
    int y;
  };

  list<Guess> guesses;
  list<Guess> correctGuess;
  list<Guess> wrongGuess;
    int solve() override {
        int hits= 0; 
        while (hits<=SHIP_COUNT)
        {
            int randomX= 1 +(rand()%100);
            int randomY= 1 +(rand()%100);
            Guess randomGuess;
            randomGuess.x = randomX;
            randomGuess.y = randomY;
            if(this->board->guess(randomX, randomY)== ResponseType::HIT)
            {
                correctGuess.push_back(randomGuess);
                hits += 1; 
            }
            else if(this->board->guess(randomX,randomY)== ResponseType::NEARMISS)
            {
                if (CheckTheGuess (randomX + 1, randomY) && GuessOnceAgain(randomX + 1, randomY))
                {
                    Guess guessNew;
                    guessNew.x = randomX + 1;
                    guessNew.y = randomY;
                    correctGuess.push_back(guessNew);
                    hits += 1;
                }
                else if (CheckTheGuess(randomX - 1, randomY) && GuessOnceAgain(randomX - 1, randomY))
                {
                    Guess guessNew;
                    guessNew.x = randomX - 1;
                    guessNew.y = randomY;
                    correctGuess.push_back(guessNew);
                    hits += 1;
                }
                else if (CheckTheGuess(randomX, randomY + 1) && GuessOnceAgain(randomX, randomY + 1))
                {
                    Guess guessNew;
                    guessNew.x = randomX;
                    guessNew.y = randomY + 1;
                    correctGuess.push_back(guessNew);
                    hits += 1;
                }
                else if (CheckTheGuess(randomX, randomY - 1) && GuessOnceAgain(randomX, randomY - 1))
                {
                    Guess guessNew;
                    guessNew.x = randomX;
                    guessNew.y = randomY - 1;
                    correctGuess.push_back(guessNew);
                    hits += 1;
                }
            }
            else if (this->board->guess(randomX, randomY) == ResponseType::MISS)
            {
                wrongGuess.push_back(randomGuess);
            }
        }
        return hits;
    }
    bool CheckedGuesses(int x, int y)
    {
        bool success = true;
        for (Guess g : correctGuess)
        {
            if (g.x == x && g.y == y)
            {
                success = false;
            }
        }
        for (Guess g : wrongGuess)
        {
            if (g.x == x && g.y == y)
            {
                success = false;
            }
        }
        return success;
    }
    bool GuessOnceAgain (int x, int y)
    {
        bool success = false;
        if (this->board->guess(x, y) == ResponseType::HIT)
        {
            success = true;
        }
        return success;
    }
    bool CheckTheGuess (int x, int y)
    {
        bool success = false;
        if (x <= WIDTH && y <= HEIGHT)
        {
            success = true;
        }
        return success;
    }
};
        return SHIP_COUNT;
    }
};


#endif /* GAME_H */
