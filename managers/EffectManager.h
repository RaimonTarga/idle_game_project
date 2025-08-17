#pragma once
#include "Effect.h"
#include <vector>
#include <memory>

class EffectManager {
private:
    std::vector<std::unique_ptr<Effect>> activeEffects;

    EffectManager() {}
    EffectManager(const EffectManager&) = delete;
    EffectManager& operator=(const EffectManager&) = delete;

public:
    static EffectManager& GetInstance() {
        static EffectManager instance;
        return instance;
    }

    // A generic method to add any type of effect
    void AddEffect(std::unique_ptr<Effect> effect);
    
    void Update(float dt);
    void Draw();
};