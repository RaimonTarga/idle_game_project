#pragma once
#include "raylib.h"

class UIManager {
private:
    // Private constructor to prevent external instantiation
    UIManager() {}
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
    
    // Optional: for future UI logic
    void Update(float dt);
    
    // Optional: for future UI drawing logic for other elements
    void Draw();
};