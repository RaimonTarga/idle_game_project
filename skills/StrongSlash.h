#pragma once
#include "Skill.h"
#include "raylib.h"
#include <cmath>

class Entity;

class StrongSlash : public Skill {
public:
    // This constructor sets the new cooldown (2.0s) and damage (15.0f)
    StrongSlash() : Skill(3.0f, 15.0f) {}

    void Use(const Vector2& userPosition, Entity& target) override;
};