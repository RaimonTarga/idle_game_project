#pragma once
#include "raylib.h"

// The base class for all visual effects
class Effect {
protected:
    float lifetime;

public:
    Effect(float life) : lifetime(life) {}
    virtual ~Effect() = default;

    virtual void Update(float dt) = 0; // Pure virtual function
    virtual void Draw() = 0;           // Pure virtual function
    
    // Check if the effect has expired
    bool IsAlive() const { return lifetime > 0.0f; }
};