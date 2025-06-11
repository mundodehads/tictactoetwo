#include <raylib.h>
#include <iostream>

#include "globals.hpp"
#include "button.hpp"
#include "home.hpp"
#include "tictactoetwo.hpp"

enum GameState
{
  MENU,
  PLAYING,
  EXIT
};

int main()
{
  InitWindow(windowWidth, windowHeight, "Tic Tac Toe Two!");
  SetTargetFPS(60);
  RenderTexture2D target = LoadRenderTexture(virtualWidth, virtualHeight);

  Home home;
  TicTacToeTwo game;
  GameState currentState = MENU;

  while (!WindowShouldClose() && currentState != EXIT)
  {
    BeginTextureMode(target);
    ClearBackground(BLACK);

    switch (currentState)
    {
    case MENU:
      home.Update();
      home.Draw();

      if (home.gameExit)
      {
        currentState = EXIT;
      }
      else if (home.gameStart)
      {
        currentState = PLAYING;
        game.Reset();
      }
      break;

    case PLAYING:
      game.Update();
      game.Draw();

      if (game.shouldReturnToMenu())
      {
        currentState = MENU;
        home.gameStart = false;
      }
      break;

    case EXIT:
      break;
    }
    EndTextureMode();

    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexturePro(
        target.texture,
        (Rectangle){0, 0, (float)virtualWidth, -(float)virtualHeight},
        (Rectangle){0, 0, (float)windowWidth, (float)windowHeight},
        (Vector2){0, 0},
        0.0f,
        WHITE);
    EndDrawing();
  }

  UnloadRenderTexture(target);
  CloseWindow();
  return 0;
}
