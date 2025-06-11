#include <raylib.h>
#include <iostream>

#include "button.hpp"
#include "home.hpp"
#include "tictactoetwo.hpp"

int main()
{
  Home home;
  TicTacToeTwo game;

  InitWindow(800, 600, "Tic Tac Toe Two!");

  SetTargetFPS(60);

  Button backButton{"assets/back_button.png", {0, 0}, 0.10};

  while (!WindowShouldClose() && !home.gameExit)
  {
    if (!home.gameStart)
    {
      home.Update();
      home.Draw();
    }
    else
    {
      game.Update();
      game.Draw();
    }
  }

  CloseWindow();
}
