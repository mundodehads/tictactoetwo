#include <raylib.h>
#include <iostream>

#include "home.hpp"
#include "globals.hpp"
#include "button.hpp"

Home::Home()
    : startButton("assets/start_button.png", {virtualWidth / 2.0f - buttonWidth / 4.0f, virtualHeight / 3.0f}, 0.5f),
      exitButton("assets/exit_button.png", {virtualWidth / 2.0f - buttonWidth / 4.0f, virtualHeight / 2.0f}, 0.5f)
{
  background = LoadTexture("assets/background.png");
  gameExit = false;
  gameStart = false;
}

Home::~Home()
{
  UnloadTexture(background);
}

void Home::Update()
{
  Vector2 mousePosition = GetMousePosition();

  float scaleX = virtualWidth / (float)windowWidth;
  float scaleY = virtualHeight / (float)windowHeight;
  mousePosition.x *= scaleX;
  mousePosition.y *= scaleY;
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
  ClearBackground(BLACK);
  DrawTexture(background, 0, 0, WHITE);
  startButton.Draw();
  exitButton.Draw();
}
