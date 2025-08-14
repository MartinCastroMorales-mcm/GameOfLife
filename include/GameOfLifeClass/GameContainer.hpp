#ifndef GAME_CONTAINER_H
#define GAME_CONTAINER_H

#include "GameConfig.hpp"
#include "Result.hpp"
#include "Square.hpp"
#include <cstdio>
#include <map>
#include <sstream>
#include <string>
#include <vector>

class GameContainer {
public:
  GameContainer(FILE* file) { this->setDebugFile(file); }
  void setDebugFile(FILE* file) { this->debugFile = file; }
  FILE* getDebugFile() { return this->debugFile; }
  void logMessage(const char* format, ...) {
    if (this->debugFile) {
      va_list args;
      va_start(args, format);
      vfprintf(debugFile, format, args);
      fflush(debugFile);
      va_end(args);
    }
  }
  // definitions

  // methods

  void startGame() {
    for (int i = 0; i < this->height; i++) {
      for (int j = 0; j < this->width; j++) {
        Square square(j, i, Square::SquareState::dead);
        this->listOfSquares.push_back(square);
      }
    }
    printState();
  }
  Result<int, std::string> changeStateOfSquare(int x, int y,
                                               Square::SquareState newState) {
    Result<int, std::string> result;
    // TODO: check if the width was inclusive; could x = width?
    if (x < 0 || x > this->width) {
      result.setError("out of bounds");
      return result;
    }
    if (y < 0 || y > this->height) {
      result.setError("out of bounds");
      return result;
    }
    Square* square = &this->listOfSquares[y * this->width + x];
    square->state = newState;
    square->nextState = newState;
    result.setValue(1);
    return result;
  }
  void nextTurn() {
    logMessage("nextTurn is excecuted\n");
    Square* arr[8];
    // Square* up;
    // Square* up_right;
    // Square* right;
    // Square* right_down;
    // Square* down;
    // Square* down_left;
    // Square* left;
    // Square* left_up;
    Square* center;
    for (int i = 0; i < this->height; i++) {
      for (int j = 0; j < this->width; j++) {
        center = &this->listOfSquares[i * width + j];
        Result<Square*, std::string> resultUp = getSquareByXY(j, i - 1);
        if (!resultUp.isOk()) {
          arr[0] = NULL;
        } else {
          arr[0] = resultUp.getValue();
        }
        Result<Square*, std::string> resultUpRight = getSquareByXY(j + 1, i - 1);
        if (!resultUpRight.isOk()) {
          arr[1] = NULL;
          // up_right = NULL;
        } else {
          arr[1] = resultUpRight.getValue();
        }
        Result<Square*, std::string> resultRight = getSquareByXY(j + 1, i);
        if (!resultRight.isOk()) {
          // right = NULL;
          arr[2] = NULL;
        } else {
          arr[2] = resultRight.getValue();
        }
        Result<Square*, std::string> resultRightDown = getSquareByXY(j + 1, i + 1);
        if (!resultRightDown.isOk()) {
          // right_down = NULL;
          arr[3] = NULL;
        } else {
          arr[3] = resultRightDown.getValue();
        }
        Result<Square*, std::string> resultDown = getSquareByXY(j, i + 1);
        if (!resultDown.isOk()) {
          // down = NULL;
          arr[4] = NULL;
        } else {
          arr[4] = resultDown.getValue();
        }
        Result<Square*, std::string> resultDownLeft = getSquareByXY(j - 1, i + 1);
        if (!resultDownLeft.isOk()) {
          // down_left = NULL;
          arr[5] = NULL;
        } else {
          arr[5] = resultDownLeft.getValue();
        }
        Result<Square*, std::string> resultLeft = getSquareByXY(j - 1, i);
        if (!resultLeft.isOk()) {
          // left = NULL;
          arr[6] = NULL;
        } else {
          arr[6] = resultLeft.getValue();
        }
        Result<Square*, std::string> resultLeftUp = getSquareByXY(j - 1, i - 1);
        if (!resultLeftUp.isOk()) {
          // left_up = NULL;
          arr[7] = NULL;
        } else {
          arr[7] = resultLeftUp.getValue();
        }
        checkStateOfSquare(arr, center);
      }
    }
    for (size_t i = 0; i < this->listOfSquares.size(); i++) {
      Square* square = &this->listOfSquares[i];
      square->state = square->nextState;
    }
  }

  Result<Square*, std::string> checkStateOfSquare(Square* arr[], Square* center) {
    int neighbors = 0;
    for (int i = 0; i < 8; i++) {
      if (arr[i] != NULL) {
        if (arr[i]->state == Square::SquareState::alive) {
          neighbors++;
        }
      }
    }
    logMessage("debug checkStateOfSquare: %d\n", neighbors);
    logMessage((center->toString() + "\n").c_str());
    logMessage("neighbors: %d\n", neighbors);
    if (center->state == Square::SquareState::alive) {
      switch (neighbors) {
      case 0:
      case 1: {
        center->nextState = Square::SquareState::dead;
      } break;

      case 2:
      case 3: {
        // No pasa nada
      } break;
      // Mas de 3
      default: {
        center->nextState = Square::SquareState::dead;
      }
      }
    } else {
      if (neighbors == 3) {
        center->nextState = Square::SquareState::alive;
      }
    }
    Result<Square*, std::string> result;
    result.setValue(center);
    return result;
  }

  void printState() {
    logMessage("printState:\n");
    for (size_t i = 0; i < listOfSquares.size(); i++) {
      Square square = listOfSquares[i];
      logMessage("square (%d, %d) => %s\n", square.x, square.y,
                 square.stateToString(square.state).c_str());
    }
    logMessage("finishPrintingState:\n");
  }
  Result<Square*, std::string> getSquareByXY(int x, int y) {
    Result<Square*, std::string> result;
    if (x < 0) {
      result.setError("out of bounds");
      return result;
    }
    if (x >= width) {
      result.setError("out of bounds");
      return result;
    }
    if (y < 0) {
      result.setError("out of bounds");
      return result;
    }
    if (y >= height) {
      result.setError("out of bounds");
      return result;
    }
    Square* square = &this->listOfSquares[y * width + x];
    result.setValue(square);

    return result;
  }
  std::vector<Square>* getListOfSquares() { return &this->listOfSquares; }
  int getWidth() { return this->width; }
  int getHeight() { return this->height; }

private:
  int width = 8;
  int height = 5;
  FILE* debugFile;
  // state
  // std::map<std::pair<int, int>, Square*> grid;
  std::vector<Square> listOfSquares;
};

#endif
/* ------------------------------------------------------------------
//map is a tree, forget the vector and use only the map, for next turn do an
inorder. just use a vector, the board will be full anyways. and you will check
every square anyways.
-------------------------------------------------------------------*/