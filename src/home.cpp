
#include <raylib.h>
#include <iostream>

#include "home.hpp"
#include "button.hpp"

Home::Home()
    : startButton("assets/start_button.png", {300, 150}, 0.65),
      exitButton("assets/exit_button.png", {300, 300}, 0.65)
{
  background = LoadTexture("assets/background.png");
  gameExit = false;
  gameStart = false;
}

void Home::Update()
{
  Vector2 mousePosition = GetMousePosition();
  bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

  if (exitButton.isPressed(mousePosition, mousePressed))
  {
    std::cout << "Exit Button Pressed" << std::endl;
    gameExit = true;
  }

  if (startButton.isPressed(mousePosition, mousePressed))
  {
    std::cout << "Start Button Pressed" << std::endl;
    gameStart = true;
  }
}

void Home::Draw() const
{
  BeginDrawing();
  ClearBackground(BLACK);
  DrawTexture(background, 0, 0, WHITE);
  startButton.Draw();
  exitButton.Draw();
  EndDrawing();
}
