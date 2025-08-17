#include "SkillBar.h"
#include <iostream>
#include <algorithm>
#include "../managers/SkillIconManager.h"


SkillBar::SkillBar(const Player& player) : player(player) {
    // The constructor is now empty. The UIManager or SkillMenu will handle this logic.
}

void SkillBar::Draw() {
    int iconSize = 64;
    int padding = 10;
    int xOffset = 20;
    int yOffset = GetScreenHeight() - iconSize - padding;

    // Get the unique, available skills
    const std::vector<Skill*>& availableSkills = player.GetAvailableSkills();

    // Check if the current skill exists to prevent a crash
    const Skill* currentSkillInQueue = player.GetCurrentSkill();

    float backgroundPadding = 5.0f;
    float backgroundX = (float)xOffset - backgroundPadding;
    float backgroundY = (float)yOffset - backgroundPadding;
    float backgroundWidth = (float)availableSkills.size() * (iconSize + padding) - padding + 2 * backgroundPadding;
    float backgroundHeight = (float)iconSize + 2 * backgroundPadding;

    DrawRectangle(backgroundX, backgroundY, backgroundWidth, backgroundHeight, BLACK);

    for (size_t i = 0; i < availableSkills.size(); ++i) {
        Skill* uniqueSkill = availableSkills[i];

        Texture2D icon = SkillIconManager::GetInstance().GetIcon(uniqueSkill->GetName());

        Vector2 iconPosition = { (float)xOffset + (float)i * (iconSize + padding), (float)yOffset };

        DrawTextureEx(icon, iconPosition, 0.0f, 1.0f, WHITE);

        // Highlight the unique skill if it matches the current skill in the queue
        if (currentSkillInQueue && uniqueSkill->GetName() == currentSkillInQueue->GetName()) {
            DrawRectangleLinesEx({ iconPosition.x, iconPosition.y, (float)iconSize, (float)iconSize }, 4.0f, YELLOW);
        }

        if (!uniqueSkill->CanUse()) {
            float cooldownRatio = uniqueSkill->GetCooldownTimer() / uniqueSkill->GetCooldown();
            float barHeight = (float)iconSize * cooldownRatio;
            
            DrawRectangle(iconPosition.x, iconPosition.y, iconSize, iconSize, Fade(BLACK, 0.5f));
            DrawRectangle(iconPosition.x, iconPosition.y + (iconSize - barHeight), iconSize, barHeight, Fade(GRAY, 0.5f));
        }
        
    }
}