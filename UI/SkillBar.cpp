#include "SkillBar.h"
#include <iostream>
#include <algorithm>

SkillBar::SkillBar(const Player& player) : player(player) {
    // Collect unique skills from the player's queue
    for (const auto& skill : player.GetSkills()) {
        bool isUnique = true;
        for (const auto& uniqueSkill : uniqueSkills) {
            if (skill->GetName() == uniqueSkill->GetName()) {
                isUnique = false;
                break;
            }
        }
        if (isUnique) {
            uniqueSkills.push_back(skill);
        }
    }
    LoadSkillIcons();
}

SkillBar::~SkillBar() {
    for (const auto& texture : skillIcons) {
        UnloadTexture(texture);
    }
}

void SkillBar::LoadSkillIcons() {
    for (const auto& skill : uniqueSkills) {
        std::string iconPath = "assets/icons/" + skill->GetName() + "Icon.png";
        Texture2D icon = LoadTexture(iconPath.c_str());
        if (icon.id == 0) {
            // Placeholder if the icon is not found
            std::cout << "Warning: Could not load skill icon: " << iconPath << std::endl;
            icon = LoadTexture("assets/icons/placeholder.png");
        }
        skillIcons.push_back(icon);
    }
}

void SkillBar::Update(float dt) {
    // No update logic needed here, as we get all info from the player in Draw()
}

void SkillBar::Draw() {
    int iconSize = 64;
    int padding = 10;
    int xOffset = 20;
    int yOffset = GetScreenHeight() - iconSize - padding;

    // Calculate the dimensions for the background rectangle
    // It should be slightly bigger than the skill bar itself.
    float backgroundPadding = 5.0f;
    float backgroundX = (float)xOffset - backgroundPadding;
    float backgroundY = (float)yOffset - backgroundPadding;
    float backgroundWidth = (float)uniqueSkills.size() * (iconSize + padding) - padding + 2 * backgroundPadding;
    float backgroundHeight = (float)iconSize + 2 * backgroundPadding;
    
    // Draw the dark gray background rectangle
    DrawRectangle(backgroundX, backgroundY, backgroundWidth, backgroundHeight, BLACK);

    for (size_t i = 0; i < uniqueSkills.size(); ++i) {
        Skill* uniqueSkill = uniqueSkills[i];
        Texture2D icon = skillIcons[i];

        // Position of the current icon
        Vector2 iconPosition = { (float)xOffset + (float)i * (iconSize + padding), (float)yOffset };

        // Draw the skill icon
        DrawTextureEx(icon, iconPosition, 0.0f, 1.0f, WHITE);

        // Highlight the current skill in the player's queue
        if (uniqueSkill->GetName() == player.GetCurrentSkill()->GetName()) {
            DrawRectangleLinesEx({ iconPosition.x, iconPosition.y, (float)iconSize, (float)iconSize }, 4.0f, YELLOW);
        }

        // Draw the cooldown overlay
        if (!uniqueSkill->CanUse()) {
            float cooldownRatio = uniqueSkill->GetCooldownTimer() / uniqueSkill->GetCooldown();
            float barHeight = (float)iconSize * cooldownRatio;
            
            // Draw a semi-transparent black rectangle
            DrawRectangle(iconPosition.x, iconPosition.y, iconSize, iconSize, Fade(BLACK, 0.5f));
            // Draw a bar that grows up
            DrawRectangle(iconPosition.x, iconPosition.y + (iconSize - barHeight), iconSize, barHeight, Fade(GRAY, 0.5f));
        }
    }
}