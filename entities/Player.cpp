#include "Player.h"
#include "Enemy.h"
#include "../skills/Slash.h"
#include "../skills/StrongSlash.h"
#include "raymath.h"
#include <limits>
#include <cmath>
#include <algorithm>

Player::Player(Vector2 pos, float s)
    : Entity(pos, 25.0f, GREEN, 100.0f), speed(s), meleeRange(40.0f),
    attackCooldown(1.0f), // Set this to 1.0f for a one-second delay
    attackTimer(0.0f),
    currentSkillIndex(0) {

    // Instantiate all skills and add them to the list in order
    skills.push_back(new Slash());
    skills.push_back(new Slash());
    skills.push_back(new Slash());
    skills.push_back(new StrongSlash());
}

Player::~Player() {
    // Correctly deallocate memory for each skill
    for (auto& skill : skills) {
        delete skill;
    }
}

// Player's main update loop
void Player::Update(float dt, std::vector<Enemy*>& enemies) {
    // Update the player's internal attack timer
    if (attackTimer > 0.0f) {
        attackTimer -= dt;
    }

    // Find the closest enemy to the player
    Enemy* closest = nullptr;
    float minDist = std::numeric_limits<float>::max();

    for (auto& e : enemies) {
        float dist = Vector2Distance(position, e->GetPosition());
        if (dist < minDist) {
            minDist = dist;
            closest = e;
        }
    }

    if (!closest) {
        // No enemies nearby, so the player stays put
        return;
    }
    
    // Check if the closest enemy is within melee range
    float distToEnemy = Vector2Distance(position, closest->GetPosition());

    // New Logic: Check if it's time to execute the next skill in the list
    if (distToEnemy <= meleeRange && attackTimer <= 0.0f) {
        // Get the current skill from the list
        Skill* currentSkill = skills[currentSkillIndex];

        // Check if the current skill is off its own cooldown
        if (currentSkill->CanUse()) {
            currentSkill->Use(GetPosition(), *closest);
            
            // Advance to the next skill in the list and loop if we reach the end
            currentSkillIndex = (currentSkillIndex + 1) % skills.size(); 
            
            // Reset the player's attack timer for the next skill in the sequence
            attackTimer = attackCooldown;
        }
    }
    
    // Move towards the closest enemy if they're not in melee range
    if (distToEnemy > meleeRange) {
        Vector2 dir = Vector2Normalize(Vector2Subtract(closest->GetPosition(), position));
        position.x += dir.x * speed * dt;
        position.y += dir.y * speed * dt;
    }
    
    // Update all equipped skills to manage their individual cooldowns
    for (auto& skill : skills) {
        skill->Update(dt);
    }
    
    // Check if player is dead
    if (IsDead()) {
        // Implement player death logic here
    }
}