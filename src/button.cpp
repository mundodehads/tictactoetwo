#include "button.hpp"
#include "globals.hpp"
#include <cstring>

Button::Button(const char *label, Vector2 pos, float width, float height, int fontSize)
    : position(pos), width(width), height(height), fontSize(fontSize)
{
    text = new char[strlen(label) + 1];
    strcpy(text, label);
}

Button::~Button()
{
    delete[] text;
}

void Button::Draw() const
{
    DrawRectangle(static_cast<int>(position.x), static_cast<int>(position.y),
                  static_cast<int>(width), static_cast<int>(height), palette[1]);

    DrawRectangleLines(static_cast<int>(position.x), static_cast<int>(position.y),
                       static_cast<int>(width), static_cast<int>(height), palette[0]);

    int textWidth = MeasureText(text, fontSize);
    int textX = static_cast<int>(position.x + (width - textWidth) / 2);
    int textY = static_cast<int>(position.y + (height - fontSize) / 2);

    DrawText(text, textX, textY, fontSize, palette[2]);
}

bool Button::isPressed(Vector2 mousePos, bool mousePressed)
{
    Rectangle rect = {position.x, position.y, width, height};
    return CheckCollisionPointRec(mousePos, rect) && mousePressed;
}
