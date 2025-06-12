#pragma once

#include <raylib.h>
#include "button.hpp"

class Home
{
public:
  Home();
  void Update();
  void Draw() const;
  bool gameExit;
  bool gameStart;

private:
  Button startButton;
  Button exitButton;
};
