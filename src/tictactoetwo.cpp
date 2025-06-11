#include "tictactoetwo.hpp"
#include <raylib.h>
#include <iostream>

TicTacToeTwo::TicTacToeTwo()
    : backButton("assets/back_button.png", {10, 10}, 0.15), returnToMenu(false), gameOverTimer(0.0f)
{
    Reset();
}

void TicTacToeTwo::Reset()
{
    // Initialize empty board
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = EMPTY;
        }
    }

    currentPlayer = PLAYER_X;
    gameResult = ONGOING;
    returnToMenu = false;
    gameOverTimer = 0.0f;
}

void TicTacToeTwo::Update()
{
    Vector2 mousePosition = GetMousePosition();
    bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

    // Check back button
    if (backButton.isPressed(mousePosition, mousePressed))
    {
        returnToMenu = true;
        return;
    }

    // Handle game logic only if game is ongoing
    if (gameResult == ONGOING)
    {
        if (mousePressed)
        {
            Vector2 cell = GetCellFromMousePos(mousePosition);
            if (cell.x >= 0 && cell.y >= 0)
            {
                HandleCellClick((int)cell.y, (int)cell.x);
            }
        }

        gameResult = CheckGameResult();
    }
    else
    {
        // Game is over, start timer for auto-return to menu
        gameOverTimer += GetFrameTime();
        if (gameOverTimer > 3.0f)
        { // Return to menu after 3 seconds
            returnToMenu = true;
        }

        // Or allow immediate return with any click
        if (mousePressed)
        {
            returnToMenu = true;
        }
    }
}

void TicTacToeTwo::Draw() const
{
    BeginDrawing();
    ClearBackground(DARKBLUE);

    // Draw game title
    DrawText("Tic Tac Toe Two!", 250, 30, 40, WHITE);

    // Draw current player indicator
    if (gameResult == ONGOING)
    {
        const char *playerText = (currentPlayer == PLAYER_X) ? "Player X's Turn" : "Player O's Turn";
        DrawText(playerText, 300, 80, 20, WHITE);
    }

    // Draw the game board
    DrawBoard();

    // Draw game result
    if (gameResult != ONGOING)
    {
        DrawGameResult();
    }

    // Draw back button
    backButton.Draw();

    EndDrawing();
}

void TicTacToeTwo::HandleCellClick(int row, int col)
{
    if (board[row][col] == EMPTY)
    {
        board[row][col] = currentPlayer;

        // Switch player
        currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;

        std::cout << "Cell clicked: " << row << ", " << col << std::endl;
    }
}

GameResult TicTacToeTwo::CheckGameResult()
{
    // Check rows
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] != EMPTY && board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            return (board[i][0] == PLAYER_X) ? PLAYER_X_WINS : PLAYER_O_WINS;
        }
    }

    // Check columns
    for (int j = 0; j < 3; j++)
    {
        if (board[0][j] != EMPTY && board[0][j] == board[1][j] && board[1][j] == board[2][j])
        {
            return (board[0][j] == PLAYER_X) ? PLAYER_X_WINS : PLAYER_O_WINS;
        }
    }

    // Check diagonals
    if (board[0][0] != EMPTY && board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        return (board[0][0] == PLAYER_X) ? PLAYER_X_WINS : PLAYER_O_WINS;
    }

    if (board[0][2] != EMPTY && board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        return (board[0][2] == PLAYER_X) ? PLAYER_X_WINS : PLAYER_O_WINS;
    }

    // Check for draw
    bool boardFull = true;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == EMPTY)
            {
                boardFull = false;
                break;
            }
        }
        if (!boardFull)
            break;
    }

    if (boardFull)
    {
        return DRAW;
    }

    return ONGOING;
}

void TicTacToeTwo::DrawBoard() const
{
    const float boardSize = 300.0f;
    const float cellSize = boardSize / 3.0f;
    const float boardX = (800 - boardSize) / 2.0f; // Center horizontally
    const float boardY = 150.0f;

    // Draw grid lines
    for (int i = 1; i < 3; i++)
    {
        // Vertical lines
        DrawLine(boardX + i * cellSize, boardY, boardX + i * cellSize, boardY + boardSize, WHITE);
        // Horizontal lines
        DrawLine(boardX, boardY + i * cellSize, boardX + boardSize, boardY + i * cellSize, WHITE);
    }

    // Draw cells
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            float cellX = boardX + j * cellSize;
            float cellY = boardY + i * cellSize;
            DrawCell(i, j, cellX, cellY, cellSize);
        }
    }
}

void TicTacToeTwo::DrawCell(int row, int col, float x, float y, float size) const
{
    const float margin = 20.0f;
    const float centerX = x + size / 2.0f;
    const float centerY = y + size / 2.0f;

    if (board[row][col] == PLAYER_X)
    {
        // Draw X
        DrawLine(x + margin, y + margin, x + size - margin, y + size - margin, RED);
        DrawLine(x + size - margin, y + margin, x + margin, y + size - margin, RED);
    }
    else if (board[row][col] == PLAYER_O)
    {
        // Draw O
        DrawCircleLines(centerX, centerY, (size - 2 * margin) / 2.0f, BLUE);
    }
}

void TicTacToeTwo::DrawGameResult() const
{
    const char *resultText = "";
    Color textColor = WHITE;

    switch (gameResult)
    {
    case PLAYER_X_WINS:
        resultText = "Player X Wins!";
        textColor = RED;
        break;
    case PLAYER_O_WINS:
        resultText = "Player O Wins!";
        textColor = BLUE;
        break;
    case DRAW:
        resultText = "It's a Draw!";
        textColor = YELLOW;
        break;
    default:
        break;
    }

    if (resultText[0] != '\0')
    {
        int textWidth = MeasureText(resultText, 30);
        DrawText(resultText, (800 - textWidth) / 2, 480, 30, textColor);
        DrawText("Click anywhere or wait to return to menu", 230, 520, 16, WHITE);
    }
}

Vector2 TicTacToeTwo::GetCellFromMousePos(Vector2 mousePos)
{
    const float boardSize = 300.0f;
    const float cellSize = boardSize / 3.0f;
    const float boardX = (800 - boardSize) / 2.0f;
    const float boardY = 150.0f;

    // Check if mouse is within board bounds
    if (mousePos.x < boardX || mousePos.x > boardX + boardSize ||
        mousePos.y < boardY || mousePos.y > boardY + boardSize)
    {
        return {-1, -1}; // Outside board
    }

    // Calculate cell coordinates
    int col = (int)((mousePos.x - boardX) / cellSize);
    int row = (int)((mousePos.y - boardY) / cellSize);

    return {(float)col, (float)row};
}

bool TicTacToeTwo::shouldReturnToMenu()
{
    return returnToMenu;
}
