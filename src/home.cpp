#include <raylib.h>

#include "home.hpp"
#include "globals.hpp"
#include "button.hpp"

Home::Home()
    : startButton("Start", {virtualWidth / 2.0f - buttonWidth / 2.0f, virtualHeight / 2.0f - buttonHeight}, buttonWidth, buttonHeight, fontSize),
      exitButton("Exit", {virtualWidth / 2.0f - buttonWidth / 2.0f, (virtualHeight / 2.0f) + (buttonHeight * 0.5f)}, buttonWidth, buttonHeight, fontSize)
{
  gameExit = false;
  gameStart = false;
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
    gameExit = true;
  }

  if (startButton.isPressed(mousePosition, mousePressed))
  {
    gameStart = true;
  }
}

void Home::Draw() const
{
  ClearBackground(palette[3]);
  const char *gameTitle = "Tic-Tac-Toe Two!";
  int gameTitlePosition = fontSize;
  DrawText(gameTitle,
           virtualWidth / 2 - MeasureText(gameTitle, fontSize) / 2,
           gameTitlePosition,
           fontSize,
           palette[1]);
  const char *gameSubTitle = "Size matters. Strategy too.";
  int gameSubTitleSize = fontSize / 2;
  DrawText(gameSubTitle,
           virtualWidth / 2 - MeasureText(gameSubTitle, gameSubTitleSize) / 2,
           gameTitlePosition * 2,
           gameSubTitleSize,
           palette[0]);
  startButton.Draw();
  exitButton.Draw();
}
