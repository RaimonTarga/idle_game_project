#include "Slash.h"
#include "Entity.h"
#include "raymath.h"
#include "../skillEffects/SlashEffect.h"
#include <cmath>
#include <memory>
#include <iostream>

void Slash::Use(const Vector2& userPosition, Entity& target) {
    if (!CanUse()) return;

    ResetCooldown();

    target.TakeDamage(GetDamage());
    
    Vector2 attackDirection = Vector2Normalize(Vector2Subtract(target.GetPosition(), userPosition));
    
    // Create the effect and add it to the manager
    auto slashEffect = std::make_unique<SlashEffect>(target.GetPosition(), attackDirection);
    EffectManager::GetInstance().AddEffect(std::move(slashEffect));
}