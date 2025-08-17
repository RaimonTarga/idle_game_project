#pragma once
#include "Effect.h"
#include "raymath.h"
#include <vector>

// Define the particle struct here for use by the StrongSlashEffect
struct StrongSlashParticle {
    Vector2 startPos;
    Vector2 direction;
    float lifetime;
    float timer;
};

class StrongSlashEffect : public Effect {
private:
    std::vector<StrongSlashParticle> particles;

public:
    StrongSlashEffect(Vector2 position, Vector2 direction);
    ~StrongSlashEffect() override = default;

    void Update(float dt) override;
    void Draw() override;
};