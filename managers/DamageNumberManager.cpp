#include "DamageNumberManager.h"
#include "raymath.h"
#include <string>
#include <algorithm>

void DamageNumberManager::AddDamageNumber(Vector2 position, float amount, Color color) {
    DamageNumber newDamageNumber;
    newDamageNumber.text = std::to_string(static_cast<int>(amount));
    newDamageNumber.position = position;
    newDamageNumber.velocity = { 0.0f, -30.0f };
    newDamageNumber.alpha = 1.0f;
    newDamageNumber.lifetime = 1.0f;

    activeNumbers.push_back(newDamageNumber);
}

void DamageNumberManager::Update(float dt) {
    for (size_t i = 0; i < activeNumbers.size(); ++i) {
        DamageNumber& dn = activeNumbers[i];
        dn.position.x += dn.velocity.x * dt;
        dn.position.y += dn.velocity.y * dt;
        dn.lifetime -= dt;
        dn.alpha = dn.lifetime;
    }

    activeNumbers.erase(
        std::remove_if(activeNumbers.begin(), activeNumbers.end(),
            [](const DamageNumber& dn) { return dn.lifetime <= 0.0f; }),
        activeNumbers.end()
    );
}

void DamageNumberManager::Draw() {
    for (const auto& dn : activeNumbers) {
        DrawText(dn.text.c_str(), (int)dn.position.x, (int)dn.position.y, 20, Fade(WHITE, dn.alpha));
    }
}