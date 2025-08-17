#include "Game.h"
#include <cstdlib>
#include <ctime>
#include "raylib.h"
#include "string"
#include <cmath>
#include <algorithm>


// --- Constructor ---
Game::Game(Vector2 playerPos) : player(playerPos) {
    spawnTimer = 0;
    srand(static_cast<unsigned int>(time(0)));
    nextSpawnTime = RandomFloat(2, 5); // faster spawn for testing
    
}

// --- Destructor ---
Game::~Game() {
    for (auto e : enemies) delete e;
}

// --- Helper: Random float in range ---
float Game::RandomFloat(float min, float max) {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

// --- Manual distance between Vector2 ---
float Distance(const Vector2& a, const Vector2& b) {
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    return std::sqrtf(dx*dx + dy*dy);
}

// --- Spawn a single enemy ---
void Game::SpawnEnemy() {
    Vector2 pos;
    bool valid = false;
    int attempts = 0;

    while (!valid && attempts < 100) {
        pos = { RandomFloat(player.position.x - 200, player.position.x + 200),
                RandomFloat(player.position.y - 200, player.position.y + 200) };
        valid = true;

        // Min distance to player
        if (Distance(pos, player.position) < minPlayerDist) valid = false;

        // Min distance to other enemies
        for (auto& e : enemies) {
            if (Distance(pos, e->position) < minEnemyDist) {
                valid = false;
                break;
            }
        }

        attempts++;
    }

    if (valid) enemies.push_back(new SlimeEnemy(pos));
}

// --- Init game ---
void Game::Init() {
    player.position = {0, 0}; // starting at world center

    // Dynamic camera offset based on current screen
    camera.target = player.position;
    camera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // Spawn some enemies immediately near player
    for (int i = 0; i < 20; i++) {
        float offsetX = RandomFloat(-500, 500);
        float offsetY = RandomFloat(-500, 500);
        enemies.push_back(new SlimeEnemy({ player.position.x + offsetX, player.position.y + offsetY }));
    }
}

// --- Update ---
void Game::Update(float dt) {
    player.Update(dt, enemies);
    camera.target = player.position; // follow player

    for (auto& e : enemies) {
        e->Update(dt);
    }

    // Remove dead enemies safely
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [](Enemy* e) {
                if (e->IsDead()) {
                    delete e; // free memory
                    return true; // remove from vector
                }
                return false;
            }),
        enemies.end()
    );

    spawnTimer += dt;
    if (spawnTimer >= nextSpawnTime) {
        SpawnEnemy();
        spawnTimer = 0;
        nextSpawnTime = RandomFloat(2, 3); // random spawn interval
    }
}

// --- Draw ---
void Game::Draw() {
    BeginDrawing();
    ClearBackground(DARKGRAY);

    BeginMode2D(camera);

    // Draw background grid 
    int spacing = 50;
    int size = 2000;
    for (int x = -size; x <= size; x += spacing)
        DrawLine(x, -size, x, size, GRAY);
    for (int y = -size; y <= size; y += spacing)
        DrawLine(-size, y, size, y, GRAY);

    // Draw enemies
    for (auto& e : enemies) e->Draw();

    // Draw player
    player.Draw();

    EndMode2D();

    // Debug info on screen
    // Draw white rectangle background
    int padding = 5;
    int boxWidth = 220;
    int boxHeight = 50;
    int boxX = 10;
    int boxY = 10;
    DrawRectangle(boxX, boxY, boxWidth, boxHeight, WHITE);

    // Draw black border
    DrawRectangleLines(boxX, boxY, boxWidth, boxHeight, BLACK);

    // Draw FPS inside the rectangle
    DrawText(TextFormat("FPS: %d", GetFPS()), boxX + padding, boxY + padding, 20, BLACK);

    DrawText(TextFormat("Player: (%.0f, %.0f)", player.position.x, player.position.y),
         boxX + padding, boxY + 25, 20, BLACK);

    EndDrawing();
}
