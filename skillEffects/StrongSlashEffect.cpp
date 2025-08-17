#include "StrongSlashEffect.h"
#include "raymath.h"
#include <algorithm>

StrongSlashEffect::StrongSlashEffect(Vector2 position, Vector2 direction) : Effect(0.2f) {
    // A longer lifetime for a more powerful feel
    const int particleCount = 50; // More particles for a denser, bigger effect

    for (int i = 0; i < particleCount; i++) {
        StrongSlashParticle p;
        p.startPos = position;
        p.direction = direction;
        p.lifetime = this->lifetime;
        p.timer = (float)i / (float)particleCount * p.lifetime;
        particles.push_back(p);
    }
}

void StrongSlashEffect::Update(float dt) {
    lifetime -= dt;
    for (size_t i = 0; i < particles.size(); ++i) {
        particles[i].timer += dt;
    }
}

void StrongSlashEffect::Draw() {
    const float arcRadius = 50.0f; // A larger radius for a wider arc
    
    for (const auto& p : particles) {
        float t = p.timer / p.lifetime;
        float easedT = t * t * (3.0f - 2.0f * t);
        
        Vector2 rotatedDirection = Vector2Rotate(p.direction, PI / 2.0f);

        Vector2 pos = Vector2Add(p.startPos, Vector2Scale(rotatedDirection, easedT * arcRadius));
        Vector2 prevPos = Vector2Add(p.startPos, Vector2Scale(rotatedDirection, (easedT - 0.05f) * arcRadius));

        float alpha = (cosf(t * PI) + 1.0f) / 2.0f;
        Color particleColor = Fade(YELLOW, alpha);

        DrawLineEx(prevPos, pos, 8.0f, particleColor); // A thicker line for a stronger look
    }
}