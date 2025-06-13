#pragma once

#include <raylib.h>
#include "button.hpp"

class Config
{
public:
  Config();
  void Update(bool mousePressed, Vector2 mousePosition);
  void Draw() const;
  bool showModal;

private:
  Rectangle modalRect;
  Rectangle closeModalRect;
  float modalWidth;
  float modalHeight;
  float modalX;
  float modalY;
};
