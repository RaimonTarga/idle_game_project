#pragma once
#include "raylib.h"
#include <string>
#include <vector>

class Entity;

class Skill {
protected:
    float cooldown;
    float cooldownTimer;
    float damage;
    std::string name; // New: Unique name for the skill

public:
    Skill(float cooldown, float damage, const std::string& skillName)
        : cooldown(cooldown), cooldownTimer(0.0f), damage(damage), name(skillName) {}

    virtual ~Skill() = default;

    // Use function now targets a single entity
    virtual void Use(const Vector2& userPosition, Entity& target) = 0;

    // The base class will handle its own cooldown logic
    virtual void Update(float dt) {
        if (cooldownTimer > 0.0f) {
            cooldownTimer -= dt;
            if (cooldownTimer < 0.0f) {
                cooldownTimer = 0.0f;
            }
        }
    }

    // A default empty Draw function for skills that don't need one
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

    const std::string& GetName() const { 
        return name; 
    }

    // New: Getter for cooldown
    float GetCooldown() const {
        return cooldown;
    }

    // New: Getter for cooldown timer
    float GetCooldownTimer() const {
        return cooldownTimer;
    }

};