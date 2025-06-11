#include "tictactoetwo.hpp"
#include <raylib.h>

TicTacToeTwo::TicTacToeTwo()
    : x(100), y(100), speedX(5), speedY(5), radius(15), backButton("assets/start_button.png", {0, 0}, 0.10)
{
}

void TicTacToeTwo::Update()
{
    x += speedX;
    y += speedY;

    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    if ((x + radius >= screenWidth) || (x - radius <= 0))
    {
        speedX *= -1;
    }

    if ((y + radius >= screenHeight) || (y - radius <= 0))
    {
        speedY *= -1;
    }
}

void TicTacToeTwo::Draw() const
{

    BeginDrawing();
    ClearBackground(DARKGREEN);
    DrawCircle(x, y, radius, WHITE);
    backButton.Draw();
    EndDrawing();
}
