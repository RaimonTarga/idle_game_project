#include "UIManager.h"
#include "raylib.h"

// The implementation for the health bar drawing
void UIManager::DrawHealthBar(Vector2 position, float radius, float currentHP, float maxHP) {
    int barWidth = (int)(radius * 2);
    int barHeight = 5;
    int barX = (int)(position.x - radius);
    int barY = (int)(position.y - radius - 10);

    // Draw background bar (black)
    DrawRectangle(barX, barY, barWidth, barHeight, BLACK);

    // Draw hp proportionally to maxHp
    float hpRatio = currentHP / maxHP;
    int hpWidth = (int)(barWidth * hpRatio);
    DrawRectangle(barX, barY, hpWidth, barHeight, RED);
}

// Update and Draw are currently empty but are good placeholders
void UIManager::Update(float dt) {
    // Implement any UI-specific update logic here in the future
}

void UIManager::Draw() {
    // Implement any general UI drawing logic here in the future
}