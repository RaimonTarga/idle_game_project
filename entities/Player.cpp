#include "Player.h"
#include "Enemy.h"
#include "../skills/Slash.h"
#include "../skills/StrongSlash.h"
#include "../Components/TextureComponent.h"
#include "../managers/UIManager.h"
#include "raymath.h"
#include <limits>
#include <cmath>
#include <algorithm>
#include <iostream>

Player::Player(Vector2 pos, float s)
    : Entity(pos, 25.0f, GREEN, 100.0f), speed(s), meleeRange(40.0f),
    attackCooldown(1.0f), attackTimer(0.0f), currentSkillIndex(0) {

    // Populate availableSkills with unique skills.
    availableSkills.push_back(new Slash());
    availableSkills.push_back(new StrongSlash());
    
    // Initially, the skill queue is a simple sequence
    skillQueue.push_back(availableSkills[0]); // Slash
    skillQueue.push_back(availableSkills[0]); // Slash
    skillQueue.push_back(availableSkills[0]); // Slash
    skillQueue.push_back(availableSkills[1]); // StrongSlash
    
    textureComponent = new TextureComponent("assets/adventurer.png");
}


Player::~Player() {
    // Correctly deallocate memory for each skill
    for (auto& skill : availableSkills) {
        delete skill;
    }
    delete textureComponent;
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
        Skill* currentSkill = skillQueue[currentSkillIndex];

        // Check if the current skill is off its own cooldown
        if (currentSkill->CanUse()) {
            currentSkill->Use(GetPosition(), *closest);
            
            // Advance to the next skill in the list and loop if we reach the end
            currentSkillIndex = (currentSkillIndex + 1) % skillQueue.size(); 
            
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
    for (auto& skill : skillQueue) {
        skill->Update(dt);
    }
    
    // Check if player is dead
    if (IsDead()) {
        // Implement player death logic here
    }    
}

const Skill* Player::GetCurrentSkill() const {
    // Check if the queue is empty to prevent a crash
    if (skillQueue.empty()) {
        return nullptr;
    }
    return skillQueue[currentSkillIndex];
}

void Player::Draw() {
    // We now delegate all drawing to our texture component
    textureComponent->Draw(position, 0.0f, 1.0f);
    UIManager::GetInstance().DrawHealthBar(position, radius, hp, maxHp);
}

void Player::AddSkillToQueue(Skill* skill) {
    skillQueue.push_back(skill);
}

void Player::ReorderSkillInQueue(int originalIndex, int newIndex) {
    if (originalIndex >= skillQueue.size() || newIndex >= skillQueue.size() + 1) {
        return; // Indices are out of bounds
    }

    // Get a reference to the element we want to move
    Skill* skillToMove = skillQueue[originalIndex];

    // Remove the element from its original position
    skillQueue.erase(skillQueue.begin() + originalIndex);

    // Insert it into the new position
    skillQueue.insert(skillQueue.begin() + newIndex, skillToMove);
}

void Player::RemoveSkillFromQueue(int indexToRemove) {
    if (indexToRemove < 0 || indexToRemove >= skillQueue.size()) {
        std::cout << "Warning: Attempted to remove a skill from an invalid index." << std::endl;
        return;
    }

    // Safely remove the skill using an iterator
    skillQueue.erase(skillQueue.begin() + indexToRemove);

    // If the removed skill was the one currently in use, reset the current skill
    if (currentSkillIndex == indexToRemove) {
        currentSkillIndex = -1;
    } else if (currentSkillIndex > indexToRemove) {
        // If the removed skill was before the current skill, we need to decrement the index of the current skill
        currentSkillIndex--;
    }
}