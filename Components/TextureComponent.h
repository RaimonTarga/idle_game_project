#pragma once
#include "raylib.h"
#include <string>

class TextureComponent {
private:
    Texture2D texture;
    Rectangle sourceRect; // The part of the texture sheet to draw

public:
    // We only need the texture file path now
    TextureComponent(const std::string& texturePath);
    ~TextureComponent();

    void Draw(Vector2 position, float rotation, float scale);
};