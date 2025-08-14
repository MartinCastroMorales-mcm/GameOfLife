#include "Button.hpp"
#include "GameConfig.hpp"
#include "GameContainer.hpp"
#include "raylib.h"
#include <cstdio>
// Aparentemente pragma apaga las warnings para raygui
#define RAYGUI_IMPLEMENTATION
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include "raygui.h"
#pragma GCC diagnostic pop
#include "raymath.h"
#include <chrono>

void mDrawSquare(Square* square) {
  DrawRectangleRec(square->rect, BLACK);
  if (square->state == Square::SquareState::dead) {
    DrawRectangle(square->rect.x, square->rect.y, GameConfig::squareSize - 2,
                  GameConfig::squareSize - 2, WHITE);
  } else {
    DrawRectangle(square->rect.x, square->rect.y, GameConfig::squareSize - 2,
                  GameConfig::squareSize - 2, RED);
  }
}
void GameLoop(GameContainer gc) {
  std::vector<Square>* listOfSquares = gc.getListOfSquares();
  // using clock = std::chrono::steady_clock;
  // std::chrono::steady_clock::time_point lastTime =
  // std::chrono::steady_clock::now();
  std::chrono::steady_clock::time_point lastFrameTime =
      std::chrono::steady_clock::now();

  // Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 800;
  const int screenHeight = 500;

  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

  SetTargetFPS(60); // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  bool buttonPressed = false;

  bool showMessageBox = false;

  bool startGame = false;

  Rectangle bounds = {screenWidth - 50 - 100, screenHeight - 50 - 50, 100, 50};
  float turnTimer = 0.0f;
  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    std::chrono::duration<float> deltaTime =
        std::chrono::steady_clock::now() - lastFrameTime;
    lastFrameTime = std::chrono::steady_clock::now();
    gc.logMessage("deltaTime: ");
    gc.logMessage(std::to_string(deltaTime.count()).c_str());
    gc.logMessage("\n");
    turnTimer += deltaTime.count();
    if (turnTimer >= GameConfig::timePerTurn && startGame) {
      turnTimer = 0;
      gc.nextTurn();
    }
    // Update
    //----------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------
    Vector2 mousePoint = GetMousePosition();
    Vector2 gamePoint = {
        mousePoint.x * (gc.getWidth() / (float)GetScreenWidth()),
        mousePoint.y * (gc.getHeight() / (float)GetScreenHeight())};

    bool btnHover = CheckCollisionPointRec(mousePoint, bounds);
    buttonPressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    if (buttonPressed && !btnHover && !startGame) {
      Result<int, std::string> result = gc.changeStateOfSquare(
          gamePoint.x, gamePoint.y, Square::SquareState::alive);

      if (!result.isOk()) {
        gc.logMessage(result.getError().c_str());
      }
    }

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(RAYWHITE);

    // DrawText("Congrats! You created your first window!", 190, 200, 20,
    // LIGHTGRAY);

    for (size_t i = 0; i < listOfSquares->size(); i++) {
      Square* square = &listOfSquares->at(i);
      mDrawSquare(square);
    }
    //-------------------------------Draw-Gui--------------------------------------------------
    // mButton button;
    // button.bounds = bounds;
    // button.text = "Next Turn";
    // button.fontSize = 10;
    // button.hoverColor = LIGHTGRAY;
    // button.color = GRAY;
    // button.textColor = RED;
    // button.isHover = btnHover;

    // button.DrawButton();

    // Every frame
    if (!startGame) {
      if (GuiButton(bounds, "start")) {
        // Button was clicked
        startGame = true;
      }
    }

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
  FILE* file = fopen("debug.log", "w");
  GameContainer gc(file);
  gc.startGame();
  GameLoop(gc);
  return 0;
}