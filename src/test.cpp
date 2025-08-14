#include "GameConfig.hpp"
#include "GameContainer.hpp"
#include <cstdio>
#include <iostream>

Result<bool, std::string> testOneSquare(GameContainer* gc) {
  Result<bool, std::string> returnResult;
  // prepare
  {
    Result<int, std::string> result =
        gc->changeStateOfSquare(0, 0, Square::SquareState::alive);
    if (!result.isOk()) {
      returnResult.setValue(false);
      returnResult.setError("Error en changeStateOfSquare");
      return returnResult;
    }
  }
  gc->nextTurn();
  Result<Square*, std::string> result = gc->getSquareByXY(0, 0);
  if (!result.isOk()) {
    returnResult.setValue(false);
    returnResult.setError("Error en changeStateOfSquare");
    return returnResult;
  }
  if (result.getValue()->state == Square::SquareState::alive) {
    returnResult.setValue(false);
    returnResult.setError(
        "El estado de (0,0) es vivo cuando se esperaba muerto");
    return returnResult;
  } else {
    returnResult.setValue(true);
    return returnResult;
  }
}

void testStateOfSquare1(GameContainer* gc) {
  Square squares[8] = 
  {Square(0, 0, Square::dead), Square(1, 0, Square::alive), Square(2, 0, Square::alive), 
  Square(0, 1, Square::dead), Square(2, 1, Square::dead), 
  Square(0, 2, Square::dead), Square(1, 2, Square::dead), Square(2, 2, Square::dead)};
  Square center = {
    Square(1,1, Square::alive)
  };
  Square* centerPtr;
  Square* squarePtrs[8];
  for (int i = 0; i < 8; ++i) {
    squarePtrs[i] = &squares[i];
  }
  Result<Square*, std::string> result = gc->checkStateOfSquare(squarePtrs, centerPtr); 

  if(centerPtr->state == Square::SquareState::alive) {
    std::cout << "\033[32mTestStateOfSquare1: pass\033[0m\n";
  }else {
    std::cout << "\033[31mTestStateOfSquare1: " << result.getError() << "\033[0m\n";
  }
}

void testStateOfSquare2(GameContainer* gc) {
  Square squares[8] = 
  {Square(0, 0, Square::alive), Square(1, 0, Square::dead), Square(2, 0, Square::alive), 
  Square(0, 1, Square::dead), Square(2, 1, Square::dead), 
  Square(0, 2, Square::alive), Square(1, 2, Square::dead), Square(2, 2, Square::alive)};
  Square center = {
    Square(1,1, Square::alive)
  };
  Square* centerPtr = &center;
  Square* squarePtrs[8];
  for (int i = 0; i < 8; ++i) {
    squarePtrs[i] = &squares[i];
  }
  Result<Square*, std::string> result = gc->checkStateOfSquare(squarePtrs, centerPtr); 

  if(centerPtr->nextState == Square::SquareState::dead) {
    std::cout << "\033[32mTestStateOfSquare2: pass\033[0m\n";
  }else {
    std::cout << "\033[31mTestStateOfSquare2: " << result.getError() << "\033[0m\n";
  }
}

void testStateOfSquare3(GameContainer* gc) {
  Square squares[8] = 
  {Square(0, 0, Square::alive), Square(1, 0, Square::dead), Square(2, 0, Square::dead), 
  Square(0, 1, Square::alive), Square(2, 1, Square::dead), 
  Square(0, 2, Square::alive), Square(1, 2, Square::dead), Square(2, 2, Square::dead)};
  Square center = {
    Square(1,1, Square::dead)
  };
  Square* centerPtr = &center;
  Square* squarePtrs[8];
  for (int i = 0; i < 8; ++i) {
    squarePtrs[i] = &squares[i];
  }
  Result<Square*, std::string> result = gc->checkStateOfSquare(squarePtrs, centerPtr); 

  if(centerPtr->nextState == Square::SquareState::alive) {
    std::cout << "\033[32mTestStateOfSquare3: pass\033[0m\n";
  }else {
    std::cout << "\033[31mTestStateOfSquare3: " << result.getError() << "\033[0m\n";
  }
}

int main() {
  FILE* file = fopen("debug.log", "w");
  GameContainer gc(file);
  gc.startGame();
  //Result<bool, std::string> result = testOneSquare(&gc);
  //if (!result.isOk()) {
    //std::cout << "\033[31mTest1: " << result.getError() << "\033[0m\n";
  //} else {
    //std::cout << "\033[32mTest1: pass\033[0m\n";
  //}
  //testStateOfSquare1(&gc);
  testStateOfSquare2(&gc);
  testStateOfSquare3(&gc);
  return 0;
}