#include "Slash.h"
#include "Entity.h"
#include "raymath.h"
#include <cmath>
#include <vector>
#include <algorithm>

void Slash::Use(const Vector2& userPosition, Entity& target) {
    if (!CanUse()) return;
    ResetCooldown();

    target.TakeDamage(GetDamage());

    Vector2 attackDirection = Vector2Normalize(Vector2Subtract(target.GetPosition(), userPosition));

    // Spawn 15 particles in a rapid, arcing motion
    for (int i = 0; i < 15; i++) {
        SlashParticle p;
        p.startPos = target.GetPosition();
        p.direction = attackDirection;
        p.lifetime = 0.2f;
        p.timer = (float)i / 15.0f * p.lifetime;
        particles.push_back(p);
    }
}

void Slash::Update(float dt) {
    cooldownTimer -= dt;
    if (cooldownTimer < 0.0f) cooldownTimer = 0.0f;

    for (auto& p : particles) {
        p.timer -= dt;
    }

    // Remove dead particles
    particles.erase(
        std::remove_if(particles.begin(), particles.end(),
            [](const SlashParticle& p) { return p.timer <= 0.0f; }),
        particles.end()
    );
}

void Slash::Draw() {
    const float arcRadius = 50.0f;
    const float arcOffsetAngle = 90.0f * DEG2RAD; // 90 degrees for a perpendicular arc

    for (auto& p : particles) {
        float t = 1.0f - (p.timer / p.lifetime);
        float easedT = t * t * (3.0f - 2.0f * t);

        // Calculate the perpendicular vector directly from the stored direction
        float currentAngle = atan2f(p.direction.y, p.direction.x) + arcOffsetAngle;
        Vector2 rotatedPerpendicular = { cosf(currentAngle), sinf(currentAngle) };

        Vector2 pos;
        // The particle's position is now calculated based on the target's position and the rotated vector
        pos.x = p.startPos.x + rotatedPerpendicular.x * easedT * arcRadius;
        pos.y = p.startPos.y + rotatedPerpendicular.y * easedT * arcRadius;

        Vector2 prevPos;
        prevPos.x = p.startPos.x + rotatedPerpendicular.x * (easedT - 0.05f) * arcRadius;
        prevPos.y = p.startPos.y + rotatedPerpendicular.y * (easedT - 0.05f) * arcRadius;

        Color particleColor = Fade(WHITE, p.timer / p.lifetime);
        DrawLineEx(prevPos, pos, 5.0f, particleColor);
    }
}