#pragma once
#include "raylib.h"
#include <vector>
#include <string>

// We'll move the struct definition here so it's only in one place
struct DamageNumber {
    std::string text;
    Vector2 position;
    Vector2 velocity;
    float alpha;
    float lifetime;
};

class DamageNumberManager {
private:
    std::vector<DamageNumber> activeNumbers;

    // Private constructor to prevent external instantiation
    DamageNumberManager() {}
    // Delete the copy constructor and assignment operator to prevent copying
    DamageNumberManager(const DamageNumberManager&) = delete;
    DamageNumberManager& operator=(const DamageNumberManager&) = delete;

public:
    // Static method to get the single instance of the manager
    static DamageNumberManager& GetInstance() {
        static DamageNumberManager instance; // The single instance
        return instance;
    }

    void AddDamageNumber(Vector2 position, float amount, Color color);
    void Update(float dt);
    void Draw();
};