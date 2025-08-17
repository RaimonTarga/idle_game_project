#include "Entity.h"
#include "raymath.h"
#include <string>

// Constructor implementation
Entity::Entity(Vector2 pos, float r, Color c, float health)
    : position(pos), radius(r), color(c), hp(health), maxHp(health) {}

void Entity::Update(float dt) {
    // This is now empty, as the manager handles all updates
}

void Entity::Draw() {
    DrawCircleV(position, radius, color);
}

// TakeDamage function implementation
void Entity::TakeDamage(float amount) {
    hp -= amount;
    if (hp < 0.0f) hp = 0.0f;
    
    // Now we get the singleton instance and call AddDamageNumber
    DamageNumberManager::GetInstance().AddDamageNumber(
        {position.x, position.y - radius}, amount, WHITE
    );
}

// Public getters implementations
Vector2 Entity::GetPosition() const { return position; }
float Entity::GetRadius() const { return radius; }
float Entity::GetCurrentHP() const { return hp; }
float Entity::GetMaxHP() const { return maxHp; }
bool Entity::IsDead() const { return hp <= 0; }