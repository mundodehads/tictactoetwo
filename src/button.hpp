#pragma once

#include <raylib.h>

class Button
{
public:
    Button(const char *label, Vector2 pos, float width, float height, int fontSize);
    ~Button();

    void Draw() const;
    bool isPressed(Vector2 mousePos, bool mousePressed);

private:
    Vector2 position;
    float width, height;
    int fontSize;
    char *text;
};
