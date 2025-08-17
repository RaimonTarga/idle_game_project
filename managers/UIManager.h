#pragma once
#include "raylib.h"
#include "../UI/SkillBar.h"
#include "../Entities/Player.h"
#include <string>

class UIManager {
private:
    SkillBar* skillBar;
    std::string errorMessage;

    // Private constructor to prevent external instantiation
    UIManager() : skillBar(nullptr) {}
    // Delete copy constructor and assignment operator to prevent duplication
    UIManager(const UIManager&) = delete;
    UIManager& operator=(const UIManager&) = delete;

public:
    // Static method to get the single instance of the manager
    static UIManager& GetInstance() {
        static UIManager instance; // The single instance
        return instance;
    }
    
    // A generic function to draw a health bar
    void DrawHealthBar(Vector2 position, float radius, float currentHP, float maxHP);
    
    void SetPlayer(const Player& player) {
        if (!skillBar) {
            skillBar = new SkillBar(player);
        }
    }
    
    void SetErrorMessage(const std::string& message) {
        errorMessage = message;
    }

    void Update(float dt);
    
    void Draw();
};