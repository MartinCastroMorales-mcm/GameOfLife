#ifndef SQUARE_H
#define SQUARE_H

#include "raylib.h"
#include <string>
#include "GameConfig.hpp"

class Square {
public:
  enum SquareState { alive, dead };
  Square(int x, int y, Square::SquareState state) {
    this->x = x;
    this->y = y;
    Rectangle rect = {
        (float)x * GameConfig::squareSize,
        (float)y * GameConfig::squareSize,
        GameConfig::squareSize,
        GameConfig::squareSize,
    };
    this->rect = rect;
    this->state = state;
    this->nextState = state;
  }
  int x;
  int y;
  Rectangle rect;
  SquareState state;
  SquareState nextState;
  // methods
  std::string stateToString(SquareState state) const {
    switch (state) {
    case alive: {
      return "alive";
    } break;
    case dead: {
      return "dead";
    } break;
    default: {
      return "error in stateToString";
    }
    }
  }
  // std::string toString() {
  // return std::format("Square: x: {}, y: {}, state: {}", this->x, this->y,
  // this->stateToString(this->state))
  //}
  std::string toString() const {
    return "Square(" + std::to_string(x) + ", " + std::to_string(y) + ", " +
           this->stateToString(state) + ")";
  }
};

/*
  typedef struct square {
    int x;
    int y;
    std::string state;
  } Square;
*/

#endif