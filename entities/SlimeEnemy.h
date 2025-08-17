#pragma once
#include "Enemy.h"
#include "../Components/TextureComponent.h"

class SlimeEnemy : public Enemy {
public:
    Vector2 direction;
    float moveTimer;
    float waitTimer;
    TextureComponent* textureComponent; // New: A pointer to our texture component

    SlimeEnemy(Vector2 spawnPos);

    void Update(float deltaTime) override;
    void Draw(); 

private:
    float RandomFloat(float min, float max);

};
