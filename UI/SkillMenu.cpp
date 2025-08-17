#include "SkillMenu.h"
#include "raylib.h"
#include "../managers/SkillIconManager.h"
#include <vector>
#include "raymath.h"

// Constructor implementation
SkillMenu::SkillMenu(Player& player)
    : nonConstPlayer(player), isDragging(false), draggedSkill(nullptr), draggedSkillOriginalIndex(-1) {}


void SkillMenu::Update() {
    int iconSize = 64;
    int padding = 20;
    int iconPadding = 10;
    
    // Define the rects for both panels
    int availableSkillsX = padding;
    int availableSkillsY = 80;
    int skillQueueX = padding;
    int skillQueueY = (GetScreenHeight() / 2) + 20;
    int skillQueueHeight = (GetScreenHeight() / 2) - 80;
    
    if (isDragging) {
        // Handle dropping the skill
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            Rectangle skillQueueRect = {(float)skillQueueX, (float)skillQueueY, (float)(GetScreenWidth() - 40), (float)skillQueueHeight};

            if (CheckCollisionPointRec(mousePos, skillQueueRect)) {
                // Drop inside the queue: reorder or add
                int newIndex = 0;
                const std::vector<Skill*>& skillQueue = nonConstPlayer.GetSkillQueue();
                for (size_t i = 0; i < skillQueue.size(); ++i) {
                    float iconCenter = (float)skillQueueX + padding + (i * (iconSize + iconPadding)) + (iconSize / 2.0f);
                    if (mousePos.x > iconCenter) {
                        newIndex = i + 1;
                    }
                }

                if (draggedSkillOriginalIndex != -1) {
                    // Reorder the skill
                    if (newIndex > draggedSkillOriginalIndex) {
                        newIndex--;
                    }
                    nonConstPlayer.ReorderSkillInQueue(draggedSkillOriginalIndex, newIndex);
                } else {
                    // Add a new skill
                    nonConstPlayer.AddSkillToQueue(draggedSkill);
                }
            } else {
                // Drop outside the queue: remove if it was from the queue
                if (draggedSkillOriginalIndex != -1) {
                    nonConstPlayer.RemoveSkillFromQueue(draggedSkillOriginalIndex);
                }
            }
            
            // Reset drag state
            isDragging = false;
            draggedSkill = nullptr;
            draggedSkillOriginalIndex = -1;
        }
    } else { // Not dragging, check if a new drag has started
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            
            // --- Check for drag start from the AVAILABLE skills ---
            const std::vector<Skill*>& availableSkills = nonConstPlayer.GetAvailableSkills();
            for (size_t i = 0; i < availableSkills.size(); ++i) {
                int iconX = availableSkillsX + padding + i * (iconSize + iconPadding);
                int iconY = availableSkillsY + 50;
                Rectangle iconRect = {(float)iconX, (float)iconY, (float)iconSize, (float)iconSize};

                if (CheckCollisionPointRec(mousePos, iconRect)) {
                    isDragging = true;
                    draggedSkill = availableSkills[i];
                    draggedOffset = Vector2Subtract(mousePos, {(float)iconX, (float)iconY});
                    draggedSkillOriginalIndex = -1;
                    return;
                }
            }

            // --- Check for drag start from the SKILL QUEUE ---
            const std::vector<Skill*>& skillQueue = nonConstPlayer.GetSkillQueue();
            for (size_t i = 0; i < skillQueue.size(); ++i) {
                int iconX = skillQueueX + padding + i * (iconSize + iconPadding);
                int iconY = skillQueueY + 50;
                Rectangle iconRect = {(float)iconX, (float)iconY, (float)iconSize, (float)iconSize};
                
                if (CheckCollisionPointRec(mousePos, iconRect)) {
                    isDragging = true;
                    draggedSkill = skillQueue[i];
                    draggedOffset = Vector2Subtract(mousePos, {(float)iconX, (float)iconY});
                    draggedSkillOriginalIndex = i;
                    return;
                }
            }
        }
    }
}

// Draw the entire skill menu screen
void SkillMenu::Draw() {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    
    // Draw a semi-transparent background over the game
    DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.8f));

    // Define dimensions for the two main panels
    int panelWidth = screenWidth - 40;
    int panelHeight = (screenHeight / 2) - 80;
    int padding = 20;
    int iconSize = 64;
    int iconPadding = 10;

    // --- Top Panel: Available Skills ---
    int availableSkillsX = padding;
    int availableSkillsY = 80;
    DrawRectangle(availableSkillsX, availableSkillsY, panelWidth, panelHeight, GRAY);
    DrawText("Available Skills", availableSkillsX + padding, availableSkillsY + padding, 20, WHITE);

    // Draw the available skill icons
    const std::vector<Skill*>& availableSkills = nonConstPlayer.GetAvailableSkills();
    int iconX = availableSkillsX + padding;
    int iconY = availableSkillsY + 50;
    for (const auto& skill : availableSkills) {
        // Skip drawing the dragged icon at its original location if it's being reordered
        if (isDragging && draggedSkillOriginalIndex == -1 && skill == draggedSkill) {
            continue;
        }
        Texture2D icon = SkillIconManager::GetInstance().GetIcon(skill->GetName());
        DrawTextureEx(icon, {(float)iconX, (float)iconY}, 0.0f, 1.0f, WHITE);
        iconX += iconSize + iconPadding;
    }

    // --- Bottom Panel: Skill Queue ---
    int skillQueueX = padding;
    int skillQueueY = (screenHeight / 2) + 20;
    DrawRectangle(skillQueueX, skillQueueY, panelWidth, panelHeight, DARKGRAY);
    DrawText("Skill Queue", skillQueueX + padding, skillQueueY + padding, 20, WHITE);

    // Draw the skills in the player's queue
    const std::vector<Skill*>& skillQueue = nonConstPlayer.GetSkillQueue();
    iconX = skillQueueX + padding;
    iconY = skillQueueY + 50;
    for (size_t i = 0; i < skillQueue.size(); ++i) {
        Skill* skill = skillQueue[i];
        // Skip drawing the dragged icon at its original location if it's being reordered
        if (isDragging && draggedSkillOriginalIndex != -1 && i == draggedSkillOriginalIndex) {
            continue;
        }

        Texture2D icon = SkillIconManager::GetInstance().GetIcon(skill->GetName());
        DrawTextureEx(icon, {(float)iconX, (float)iconY}, 0.0f, 1.0f, WHITE);
        iconX += iconSize + iconPadding;
    }

    // --- Title ---
    const char* menuTitle = "Skill Management";
    int titleFontSize = 40;
    int titleWidth = MeasureText(menuTitle, titleFontSize);
    DrawText(menuTitle, (screenWidth - titleWidth) / 2, 40, titleFontSize, WHITE);

    // --- Draw the visual drop indicator ---
    if (isDragging) {
        Vector2 mousePos = GetMousePosition();
        
        int skillQueueX = padding;
        int skillQueueY = (screenHeight / 2) + 20;
        int skillQueueHeight = (screenHeight / 2) - 80;
        Rectangle skillQueueRect = {(float)skillQueueX, (float)skillQueueY, (float)(screenWidth - 40), (float)skillQueueHeight};

        if (CheckCollisionPointRec(mousePos, skillQueueRect)) {
            // Find the index where the icon would be dropped
            int dropIndex = 0;
            for (size_t i = 0; i < skillQueue.size(); ++i) {
                float iconCenter = (float)skillQueueX + padding + (i * (iconSize + iconPadding)) + (iconSize / 2.0f);
                if (mousePos.x > iconCenter) {
                    dropIndex = i + 1;
                }
            }

            // Calculate the position for the drop indicator based on the new index
            float dropIndicatorX = skillQueueX + padding + dropIndex * (iconSize + iconPadding);
            float dropIndicatorY = skillQueueY + 50;
            
            // Draw the blue outline with a dashed effect
            DrawRectangleLinesEx({(float)dropIndicatorX, (float)dropIndicatorY, (float)iconSize, (float)iconSize}, 4.0f, BLUE);
        }
    }
    
    // --- Draw the dragged skill on top of everything else ---
    if (isDragging && draggedSkill != nullptr) {
        Vector2 mousePos = GetMousePosition();
        Vector2 drawPos = Vector2Subtract(mousePos, draggedOffset);
        
        Texture2D icon = SkillIconManager::GetInstance().GetIcon(draggedSkill->GetName());
        DrawTextureEx(icon, drawPos, 0.0f, 1.0f, WHITE);
    }
}