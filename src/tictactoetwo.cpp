#include <raylib.h>

#include "tictactoetwo.hpp"
#include "globals.hpp"

TicTacToeTwo::TicTacToeTwo()
    : backButton("<--", {fontSize / 2.0f, fontSize / 2.0f}, 16, 10, fontSize / 2), returnToMenu(false), gameOverTimer(0.0f)
{
    Reset();
}

void TicTacToeTwo::Reset()
{
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
    float scaleX = virtualWidth / (float)windowWidth;
    float scaleY = virtualHeight / (float)windowHeight;
    mousePosition.x *= scaleX;
    mousePosition.y *= scaleY;
    bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

    if (backButton.isPressed(mousePosition, mousePressed))
    {
        returnToMenu = true;
        return;
    }

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
        gameOverTimer += GetFrameTime();
        if (gameOverTimer > 10.0f) // Return to menu after 10 seconds
        {
            returnToMenu = true;
        }

        if (mousePressed) // Immediate return to menu
        {
            returnToMenu = true;
        }
    }
}

void TicTacToeTwo::Draw() const
{
    ClearBackground(palette[3]);

    if (gameResult == ONGOING)
    {
        const char *playerText = (currentPlayer == PLAYER_X) ? "Player X's Turn" : "Player O's Turn";
        int playerFontSize = fontSize / 2;
        DrawText(playerText,
                 virtualWidth / 2 - MeasureText(playerText, playerFontSize) / 2,
                 playerFontSize,
                 playerFontSize,
                 palette[1]);
    }

    DrawBoard();

    if (gameResult != ONGOING)
    {
        DrawGameResult();
    }

    backButton.Draw();
}

void TicTacToeTwo::HandleCellClick(int row, int col)
{
    if (board[row][col] == EMPTY)
    {
        board[row][col] = currentPlayer;
        currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
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
    const float boardSize = virtualWidth / 3.0f + 20.0f;
    const float cellSize = boardSize / 3.0f;
    const float boardX = (virtualWidth - boardSize) / 2.0f;
    const float boardY = 50.0f;

    for (int i = 1; i < 3; i++)
    {
        DrawLine(boardX + i * cellSize, boardY, boardX + i * cellSize, boardY + boardSize, palette[0]);
        DrawLine(boardX, boardY + i * cellSize, boardX + boardSize, boardY + i * cellSize, palette[0]);
    }

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
        int resultFontSize = fontSize / 2;
        DrawText(resultText,
                 virtualWidth / 2 - MeasureText(resultText, resultFontSize) / 2,
                 resultFontSize,
                 resultFontSize,
                 textColor);

        const char *infoText = "Click anywhere or wait to return to menu";
        int infoFontSize = resultFontSize / 2;
        DrawText(infoText,
                 virtualWidth / 2 - MeasureText(infoText, infoFontSize) / 2,
                 infoFontSize * 2 + resultFontSize,
                 infoFontSize,
                 palette[0]);
    }
}

Vector2 TicTacToeTwo::GetCellFromMousePos(Vector2 mousePos)
{
    const float boardSize = virtualWidth / 3.0f + 20.0f;
    const float cellSize = boardSize / 3.0f;
    const float boardX = (virtualWidth - boardSize) / 2.0f;
    const float boardY = 50.0f;

    if (mousePos.x < boardX || mousePos.x > boardX + boardSize ||
        mousePos.y < boardY || mousePos.y > boardY + boardSize)
    {
        return {-1, -1};
    }

    int col = (int)((mousePos.x - boardX) / cellSize);
    int row = (int)((mousePos.y - boardY) / cellSize);

    return {(float)col, (float)row};
}

bool TicTacToeTwo::shouldReturnToMenu()
{
    return returnToMenu;
}
