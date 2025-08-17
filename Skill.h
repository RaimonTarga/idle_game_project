#pragma once
#include "raylib.h"
#include <string>
#include <vector>
#include "Entity.h"

class Skill {
protected:
    float cooldown;
    float cooldownTimer;
    float damage;
    bool isActive;

public:
    Skill(float cooldown, float damage)
        : cooldown(cooldown), cooldownTimer(0.0f), damage(damage), isActive(false) {}

    virtual ~Skill() = default;

    // Use function now targets a single entity
    virtual void Use(const Vector2& userPosition, Entity& target) = 0;

    virtual void Update(float dt) = 0;

    virtual void Draw() {}

    void ResetCooldown() {
        cooldownTimer = cooldown;
    }

    bool CanUse() const {
        return cooldownTimer <= 0.0f;
    }

    float GetDamage() const {
        return damage;
    }
};