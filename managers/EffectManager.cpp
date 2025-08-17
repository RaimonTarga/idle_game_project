#include "EffectManager.h"
#include <algorithm>

void EffectManager::AddEffect(std::unique_ptr<Effect> effect) {
    activeEffects.push_back(std::move(effect));
}

void EffectManager::Update(float dt) {
    for (auto& effect : activeEffects) {
        effect->Update(dt);
    }

    activeEffects.erase(
        std::remove_if(activeEffects.begin(), activeEffects.end(),
            [](const auto& e) { return !e->IsAlive(); }),
        activeEffects.end()
    );
}

void EffectManager::Draw() {
    for (auto& effect : activeEffects) {
        effect->Draw();
    }
}