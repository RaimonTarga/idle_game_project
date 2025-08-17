#include "SlashEffect.h"
#include "raymath.h"
#include <algorithm>

SlashEffect::SlashEffect(Vector2 position, Vector2 direction) : Effect(0.1f) {
    const int particleCount = 20; 

    for (int i = 0; i < particleCount; i++) {
        SlashParticle p;
        p.startPos = position;
        p.direction = direction;
        p.lifetime = this->lifetime;
        p.timer = (float)i / (float)particleCount * p.lifetime;
        particles.push_back(p);
    }
}

void SlashEffect::Update(float dt) {
    lifetime -= dt;
    for (size_t i = 0; i < particles.size(); ++i) {
        particles[i].timer += dt;
    }
}

void SlashEffect::Draw() {
    const float arcRadius = 25.0f; 
    
    for (const auto& p : particles) {
        float t = p.timer / p.lifetime;
        float easedT = t * t * (3.0f - 2.0f * t);
        
        Vector2 rotatedDirection = Vector2Rotate(p.direction, PI / 2.0f);

        Vector2 pos = Vector2Add(p.startPos, Vector2Scale(rotatedDirection, easedT * arcRadius));
        Vector2 prevPos = Vector2Add(p.startPos, Vector2Scale(rotatedDirection, (easedT - 0.05f) * arcRadius));

        // New: Use a cosine curve for a smoother, more gradual fade
        float alpha = (cosf(t * PI) + 1.0f) / 2.0f;
        Color particleColor = Fade(WHITE, alpha);

        DrawLineEx(prevPos, pos, 5.0f, particleColor);
    }
}