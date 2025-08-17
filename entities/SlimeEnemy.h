#pragma once
#include "Enemy.h"

class SlimeEnemy : public Enemy {
public:
    Vector2 direction;
    float moveTimer;
    float waitTimer;

    SlimeEnemy(Vector2 spawnPos);

    void Update(float deltaTime) override;

private:
    float RandomFloat(float min, float max);

};
