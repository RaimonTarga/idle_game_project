#pragma once
#include "entities/Player.h"
#include "entities/SlimeEnemy.h"
#include <vector>

class Game {
public:
    Player player;
    Camera2D camera;
    std::vector<Enemy*> enemies;
    float spawnTimer;
    float nextSpawnTime;

    const float minPlayerDist = 50.0f;
    const float minEnemyDist = 50.0f;

    Game(Vector2 playerPos);
    ~Game();

    void Init();        // <-- Added this for setup logic
    void Update(float dt);
    void Draw();

private:
    float RandomFloat(float min, float max);
    void SpawnEnemy();
};
