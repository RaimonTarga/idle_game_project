#pragma once
#include "Entity.h"

class Enemy : public Entity {
public:
    float speed;

    Enemy(Vector2 spawnPos, float r = 16, Color c = RED, int hp = 50)
        : Entity(spawnPos, r, c, hp), speed(100.0f) {}

    virtual void Update(float dt) override {
        // Generic enemy does nothing by default
    }
};
