#pragma once

#include "button.hpp"

class TicTacToeTwo
{
public:
    TicTacToeTwo();
    void Update();
    void Draw() const;

private:
    int x;
    int y;
    int speedX;
    int speedY;
    int radius;
    Button backButton;
};
