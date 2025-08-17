#include "TextureComponent.h"
#include "raymath.h"

TextureComponent::TextureComponent(const std::string& texturePath) {
    texture = LoadTexture(texturePath.c_str());
    
    // The source rectangle now covers the entire texture, as it's just one sprite
    sourceRect = { 0, 0, (float)texture.width, (float)texture.height };
}

TextureComponent::~TextureComponent() {
    UnloadTexture(texture);
}

void TextureComponent::Draw(Vector2 position, float rotation, float scale) {
    Vector2 origin = { sourceRect.width / 2.0f, sourceRect.height / 2.0f };
    DrawTexturePro(texture, sourceRect, { position.x, position.y, sourceRect.width * scale, sourceRect.height * scale }, origin, rotation, WHITE);
}