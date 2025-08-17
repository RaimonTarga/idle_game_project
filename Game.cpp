#include "Game.h"
#include <cstdlib>
#include <ctime>
#include "raylib.h"
#include "string"
#include <cmath>
#include <algorithm>
#include "entities/SlimeEnemy.h"
#include "entities/Player.h"
#include "managers/UIManager.h"
#include "managers/DamageNumberManager.h"
#include "managers/EffectManager.h"
#include "managers/SkillIconManager.h"

// --- Constructor ---
Game::Game(Vector2 playerPos) : player(playerPos), skillMenu(player) {
    spawnTimer = 0;
    srand(static_cast<unsigned int>(time(0)));
    nextSpawnTime = RandomFloat(2, 5);
    state = GameState::PLAYING;
}

// --- Destructor ---
Game::~Game() {
    for (auto e : enemies) delete e;
    SkillIconManager::GetInstance().UnloadIcons();
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
        pos = { RandomFloat(player.GetPosition().x - 200, player.GetPosition().x + 200),
                RandomFloat(player.GetPosition().y - 200, player.GetPosition().y + 200) };
        valid = true;

        // Min distance to player
        if (Distance(pos, player.GetPosition()) < minPlayerDist) valid = false;

        // Min distance to other enemies
        for (auto& e : enemies) {
            if (Distance(pos, e->GetPosition()) < minEnemyDist) {
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
    // Note: We need a setter for position since it's now protected.
    // player.SetPosition({0, 0}); // starting at world center

    // Dynamic camera offset based on current screen
    camera.target = player.GetPosition();
    camera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // Spawn some enemies immediately near player
    for (int i = 0; i < 20; i++) {
        float offsetX = RandomFloat(-500, 500);
        float offsetY = RandomFloat(-500, 500);
        enemies.push_back(new SlimeEnemy({ player.GetPosition().x + offsetX, player.GetPosition().y + offsetY }));
    }

    // Set up the UI manager to track the player
    UIManager::GetInstance().SetPlayer(player);
    SkillIconManager::GetInstance().LoadIconsFromDirectory("assets/icons/");
}

// --- Update ---
void Game::Update(float dt) {
    // New: Check for the 'S' key press to toggle the state
    if (IsKeyPressed(KEY_S)) {
        if (state == GameState::PLAYING) {
            state = GameState::PAUSED;
        } else {
            state = GameState::PLAYING;
        }
    }

    // New: Only run the game logic when the state is PLAYING
    if (state == GameState::PLAYING) {
        player.Update(dt, enemies);
        camera.target = player.GetPosition(); // follow player

        for (auto& e : enemies) {
            e->Update(dt);
        }

        // Remove dead enemies safely
        for (auto it = enemies.begin(); it != enemies.end(); /* No increment here */) {
            if ((*it)->IsDead()) {
                delete *it;
                it = enemies.erase(it); // Erase returns an iterator to the next element
            } else {
                ++it;
            }
        }

        spawnTimer += dt;
        if (spawnTimer >= nextSpawnTime) {
            SpawnEnemy();
            spawnTimer = 0;
            nextSpawnTime = RandomFloat(2, 3); // random spawn interval
        }
    }

    if (state == GameState::PAUSED) {
        skillMenu.Update(); // New: Call the menu's update method
    }

    // New: UI and other managers still update even when paused
    DamageNumberManager::GetInstance().Update(dt);
    EffectManager::GetInstance().Update(dt);
}

// --- Draw ---
void Game::Draw() {
    BeginDrawing();
    ClearBackground(DARKGRAY);

    // Check the game state to decide what to draw
    if (state == GameState::PLAYING) {
        // Draw the game world and all in-game elements
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

        EffectManager::GetInstance().Draw();
        DamageNumberManager::GetInstance().Draw();

        EndMode2D();

        // Draw all of the UI elements
        UIManager::GetInstance().Draw();

    } else { // GameState::PAUSED
        skillMenu.Draw();
    }

    // These debug elements are drawn regardless of game state
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

    DrawText(TextFormat("Player: (%.0f, %.0f)", player.GetPosition().x, player.GetPosition().y),
            boxX + padding, boxY + 25, 20, BLACK);

    EndDrawing();
}