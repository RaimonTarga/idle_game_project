#pragma once
#include "Skill.h"
#include "raylib.h"
#include "../managers/EffectManager.h" // The manager that will handle our effect
#include <cmath>

class Entity;

class Slash : public Skill {
public:
    Slash() : Skill(0.0f, 5.0f, "Slash") {}

    void Use(const Vector2& userPosition, Entity& target) override;
};