#include "UIManager.h"
#include "../entities/Enemy.h"
#include <vector>

// The implementation for the health bar drawing
void UIManager::DrawHealthBar(Vector2 position, float radius, float currentHP, float maxHP) {
    int barWidth = (int)(radius * 2);
    int barHeight = 5;
    int barX = (int)(position.x - radius);
    int barY = (int)(position.y - radius - 10);

    DrawRectangle(barX, barY, barWidth, barHeight, BLACK);

    float hpRatio = currentHP / maxHP;
    int hpWidth = (int)(barWidth * hpRatio);
    DrawRectangle(barX, barY, hpWidth, barHeight, RED);
}

void UIManager::Draw() {
    // Draw the skill bar
    if (skillBar) {
        skillBar->Draw();
    } else {
        // Since we are in a non-static method, we can call this->SetErrorMessage directly
        this->SetErrorMessage("Error: SkillBar not initialized.");
    }

    // Draw the error message if it exists
    if (!errorMessage.empty()) {
        int fontSize = 30;
        int textWidth = MeasureText(errorMessage.c_str(), fontSize);
        DrawText(errorMessage.c_str(),
                 (GetScreenWidth() - textWidth) / 2,
                 GetScreenHeight() / 2,
                 fontSize,
                 RED);
    }
}