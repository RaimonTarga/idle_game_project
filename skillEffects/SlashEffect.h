#pragma once
#include "Effect.h"
#include "raymath.h"
#include <vector>

// Define the particle struct here for use by the SlashEffect
struct SlashParticle {
    Vector2 startPos;
    Vector2 direction;
    float lifetime;
    float timer;
};

class SlashEffect : public Effect {
private:
    std::vector<SlashParticle> particles;

public:
    SlashEffect(Vector2 position, Vector2 direction);
    ~SlashEffect() override = default;

    void Update(float dt) override;
    void Draw() override;
};