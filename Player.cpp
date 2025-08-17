#include "Player.h"
#include "Enemy.h"
#include "Slash.h"
#include "raymath.h"
#include <limits>
#include <cmath>

Player::Player(Vector2 pos, float s)
    : Entity(pos, 25.0f, GREEN, 100.0f), speed(s), meleeRange(30.0f), 
    attackCooldown(1.0f), attackTimer(0.0f) {
    // Instantiate a Slash skill and add it to the skills vector
    skills.push_back(new Slash());
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

    // Use the first skill if the enemy is in range and the skill is off cooldown
    if (distToEnemy <= meleeRange && attackTimer <= 0.0f) {
        // Check if there are any skills and if the first one can be used
        if (!skills.empty() && skills[0]->CanUse()) {
            skills[0]->Use(GetPosition(), *closest); // Use the skill on the closest enemy
            attackTimer = attackCooldown; // Reset the player's attack timer
        }
    }
    
    // Move towards the closest enemy if they're not in melee range
    if (distToEnemy > meleeRange) {
        Vector2 dir = Vector2Normalize(Vector2Subtract(closest->GetPosition(), position));
        position.x += dir.x * speed * dt;
        position.y += dir.y * speed * dt;
    }
    
    // Update all equipped skills
    for (auto& skill : skills) {
        skill->Update(dt);
    }
    
    // Check if player is dead
    if (IsDead()) {
        // Implement player death logic here
    }
}

// Player's drawing function
void Player::Draw() {
    // Draw the player body
    DrawCircleV(position, radius, color);

    // Draw health bar
    int barWidth = (int)(radius * 2);
    int barHeight = 5;
    int barX = (int)(position.x - radius);
    int barY = (int)(position.y - radius - 10);
    DrawRectangle(barX, barY, barWidth, barHeight, BLACK);

    float hpRatio = hp / maxHp;
    int hpWidth = (int)(barWidth * hpRatio);
    DrawRectangle(barX, barY, hpWidth, barHeight, RED);

    // This is the crucial part that was missing or incorrect
    // Loop through all equipped skills and call their Draw method.
    for (auto& skill : skills) {
        skill->Draw();
    }
}