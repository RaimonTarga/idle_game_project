#pragma once
#include "Skill.h"
#include "raylib.h"
#include <vector>
#include <cmath>

class Entity;

// Define the SlashParticle struct here
struct SlashParticle {
    Vector2 startPos;
    Vector2 direction;
    float timer;
    float lifetime;
};

class Slash : public Skill {
private:
    std::vector<SlashParticle> particles;

public:
    Slash() : Skill(0.5f, 5.0f) {}

    void Use(const Vector2& userPosition, Entity& target) override;
    void Update(float dt) override;
    void Draw() override;
};