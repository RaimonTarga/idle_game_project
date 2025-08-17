#pragma once
#include "raylib.h"
#include <string>
#include <vector>
#include "../managers/DamageNumberManager.h" // Include the new manager header

class Entity {
protected:
    Vector2 position;
    float radius;
    Color color;
    float hp;
    float maxHp;

public:
    Entity(Vector2 pos, float r, Color c, float health = 100.0f);
    virtual ~Entity() = default;
    virtual void Update(float dt);
    virtual void Draw();
    
    // TakeDamage no longer needs the manager as a parameter
    virtual void TakeDamage(float amount);
    
    bool IsDead() const;
    Vector2 GetPosition() const;
    float GetRadius() const;
    float GetCurrentHP() const;
    float GetMaxHP() const;
};