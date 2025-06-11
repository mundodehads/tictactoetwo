#include <raylib.h>
#include <iostream>

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
  InitWindow(800, 600, "Tic Tac Toe Two!");
  SetTargetFPS(60);

  Home home;
  TicTacToeTwo game;
  GameState currentState = MENU;

  while (!WindowShouldClose() && currentState != EXIT)
  {
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
        game.Reset(); // Reset the game when starting
      }
      break;

    case PLAYING:
      game.Update();
      game.Draw();

      if (game.shouldReturnToMenu())
      {
        currentState = MENU;
        home.gameStart = false; // Reset the home state
      }
      break;

    case EXIT:
      break;
    }
  }

  CloseWindow();
  return 0;
}
