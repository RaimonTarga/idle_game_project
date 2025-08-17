#pragma once
#include "raylib.h"

class Entity {
public:
    Vector2 position;
    float radius;
    Color color;
    int hp;
    int maxHp; // new max health

    Entity(Vector2 pos, float r, Color c, int health = 100)
        : position(pos), radius(r), color(c), hp(health), maxHp(health) {}

    virtual ~Entity() {}

    virtual void Update(float dt) {}

    virtual void Draw() {
        // Draw the entity as a circle
        DrawCircleV(position, radius, color);

        // Draw health bar above the entity
        int barWidth = (int)(radius * 2);
        int barHeight = 5;
        int barX = (int)(position.x - radius);
        int barY = (int)(position.y - radius - 10);

        // Draw background bar (black)
        DrawRectangle(barX, barY, barWidth, barHeight, BLACK);

        // Draw hp proportionally to maxHp
        float hpRatio = (float)hp / (float)maxHp;
        int hpWidth = (int)(barWidth * hpRatio);
        DrawRectangle(barX, barY, hpWidth, barHeight, RED);
    }

    virtual void TakeDamage(float amount) {
        hp -= amount;
        if (hp < 0) hp = 0;
    }

    bool IsDead() const { return hp <= 0; }

    // Public getters for safe access
    Vector2 GetPosition() const { return position; }
    float GetRadius() const { return radius; }
};
