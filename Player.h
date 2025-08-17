#pragma once
#include "Entity.h"
#include "Enemy.h"
#include "Skill.h"
#include "raylib.h"
#include <vector>

class Player : public Entity {
private:
    float speed;
    float meleeRange;
    float attackCooldown;
    float attackTimer;
    std::vector<Skill*> skills;

public:
    Player(Vector2 pos, float s = 200.0f);

    // This function is not an override of the base Entity's Update
    void Update(float dt, std::vector<Enemy*>& enemies); 
    
    // Draw is a concrete implementation of the base class's pure virtual function
    void Draw() override;
    
    // Add a public getter for player position so external classes can access it
    Vector2 GetPosition() const { return position; }
};