#include "SlimeEnemy.h"
#include <cstdlib>   // for rand()
#include <cmath>     // for cosf, sinf, M_PI
#ifndef M_PI
#define M_PI 3.14159265f
#endif

SlimeEnemy::SlimeEnemy(Vector2 spawnPos)
    : Enemy(spawnPos, 16, BLUE, 30) // radius=16, color=BLUE, hp=30
{
    direction = {0, 0};
    moveTimer = 0.0f;
    waitTimer = 0.0f;
    speed = 80.0f; // slower than player
}

void SlimeEnemy::Update(float deltaTime) {
    if (waitTimer > 0.0f) {
        waitTimer -= deltaTime;
        return;
    }

    moveTimer += deltaTime;

    if (moveTimer >= 3.0f) {
        moveTimer = 0.0f;
        waitTimer = 1.0f;
        direction = {0, 0};
    } else if (direction.x == 0 && direction.y == 0) {
        float angle = RandomFloat(0.0f, 2.0f * M_PI);
        direction = { std::cos(angle), std::sin(angle) };
    }

    position.x += direction.x * speed * deltaTime;
    position.y += direction.y * speed * deltaTime;
}

float SlimeEnemy::RandomFloat(float min, float max) {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}
