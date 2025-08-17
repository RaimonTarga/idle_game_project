#include "../skills/StrongSlash.h"
#include "Entity.h"
#include "raymath.h"
#include "../skillEffects/StrongSlashEffect.h" // Include the new concrete effect
#include "../managers/EffectManager.h"
#include <cmath>
#include <memory>

void StrongSlash::Use(const Vector2& userPosition, Entity& target) {
    if (!CanUse()) return;
    ResetCooldown();

    target.TakeDamage(GetDamage());
    
    Vector2 attackDirection = Vector2Normalize(Vector2Subtract(target.GetPosition(), userPosition));
    
    // Create the STRONG slash effect and add it to the manager
    auto strongSlashEffect = std::make_unique<StrongSlashEffect>(target.GetPosition(), attackDirection);
    EffectManager::GetInstance().AddEffect(std::move(strongSlashEffect));
}