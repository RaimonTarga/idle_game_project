#pragma once
#include "Entity.h"
#include "Enemy.h"
#include "../skills/Skill.h"
#include "../Components/TextureComponent.h"
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
    TextureComponent* textureComponent; // New: A pointer to our texture component

public:
    Player(Vector2 pos, float s = 200.0f);
    ~Player(); // New: Proper destructor to clean up memory

    // This function is not an override of the base Entity's Update
    void Update(float dt, std::vector<Enemy*>& enemies); 
    
    // Add a public getter for player position so external classes can access it
    Vector2 GetPosition() const { return position; }

    void Draw(); // New: Override the Draw function to use the texture component

    // Getters for SkillBar
    const std::vector<Skill*>& GetSkills() const { return skills; } // Get the skill list
    const Skill* GetCurrentSkill() const { return skills[currentSkillIndex]; } // Get the currently queued skill
    
};