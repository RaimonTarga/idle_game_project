#pragma once
#include "Entity.h"
#include "Enemy.h"
#include "../skills/Skill.h"
#include "raylib.h"
#include <vector>

class Player : public Entity {
private:
    float speed;
    float meleeRange;
    float attackCooldown; // Time between each skill execution
    float attackTimer;    // Tracks when the next skill can be used
    std::vector<Skill*> skills;
    size_t currentSkillIndex; // New: Index of the current skill in the list

public:
    Player(Vector2 pos, float s = 200.0f);
    ~Player(); // New: Proper destructor to clean up memory

    // This function is not an override of the base Entity's Update
    void Update(float dt, std::vector<Enemy*>& enemies); 
    
    // Add a public getter for player position so external classes can access it
    Vector2 GetPosition() const { return position; }
};