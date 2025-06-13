#include <raylib.h>
#include <iostream>

#include "config.hpp"
#include "globals.hpp"
#include "button.hpp"

Config::Config()
{
  showModal = false;
  modalWidth = virtualWidth * 0.4f;
  modalHeight = virtualHeight * 0.6f;
  modalX = (virtualWidth - modalWidth) / 2.0f;
  modalY = (virtualHeight - modalHeight) / 2.0f;
  modalRect = {modalX, modalY, modalWidth, modalHeight};
  closeModalRect = {modalX + modalWidth - 30, modalY + 10, 16, 16};
}

void Config::Update(bool mousePressed, Vector2 mousePosition)
{
  if (mousePressed)
  {
    if (!CheckCollisionPointRec(mousePosition, modalRect) || CheckCollisionPointRec(mousePosition, closeModalRect))
    {
      showModal = false;
    }
  }
}

void Config::Draw() const
{
  DrawRectangleRec(modalRect, palette[0]);
  DrawRectangleLinesEx(modalRect, 2, palette[2]);

  DrawRectangleRec(closeModalRect, palette[3]);
  DrawRectangleLinesEx(closeModalRect, 2, palette[2]);

  const char *xText = "x";
  int xFontSize = fontSize / 2;
  int xTextWidth = MeasureText(xText, xFontSize);
  int xTextX = (int)(closeModalRect.x + (closeModalRect.width - xTextWidth) / 2);
  int xTextY = (int)(closeModalRect.y + (closeModalRect.height - xFontSize) / 2);

  DrawText(xText, xTextX, xTextY, xFontSize, palette[0]);

  const char *title = "Config";
  int titleWidth = MeasureText(title, fontSize);
  int titleX = (int)(modalX + (modalWidth - titleWidth) / 2);
  int titleY = (int)(modalY + closeModalRect.height);
  DrawText(title, titleX, titleY, fontSize, palette[3]);
}
