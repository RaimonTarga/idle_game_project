#pragma once
#include "entities/Player.h"
#include "entities/SlimeEnemy.h"
#include <vector>
#include "UI/SkillMenu.h"

// New: Define the possible game states
enum class GameState {
    PLAYING,
    PAUSED
};

class Game {
public:
    Player player;
    Camera2D camera;
    std::vector<Enemy*> enemies;
    float spawnTimer;
    float nextSpawnTime;

    const float minPlayerDist = 50.0f;
    const float minEnemyDist = 50.0f;

    GameState state;

    SkillMenu skillMenu;

    Game(Vector2 playerPos);
    ~Game();

    void Init();
    void Update(float dt);
    void Draw();

private:
    float RandomFloat(float min, float max);
    void SpawnEnemy();
};