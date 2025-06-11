#pragma once

#include "button.hpp"
#include <raylib.h>

enum CellState
{
    EMPTY = 0,
    PLAYER_X = 1,
    PLAYER_O = 2
};

enum GameResult
{
    ONGOING,
    PLAYER_X_WINS,
    PLAYER_O_WINS,
    DRAW
};

class TicTacToeTwo
{
public:
    TicTacToeTwo();
    void Update();
    void Draw() const;
    void Reset();
    bool shouldReturnToMenu();

private:
    CellState board[3][3];
    CellState currentPlayer;
    GameResult gameResult;
    Button backButton;
    bool returnToMenu;
    float gameOverTimer;

    // Game logic methods
    void HandleCellClick(int row, int col);
    GameResult CheckGameResult();
    void DrawBoard() const;
    void DrawCell(int row, int col, float x, float y, float size) const;
    void DrawGameResult() const;
    Vector2 GetCellFromMousePos(Vector2 mousePos);
};
