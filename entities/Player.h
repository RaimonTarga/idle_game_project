#pragma once
#include "Entity.h"
#include "Enemy.h"
#include "../skills/Skill.h"
#include "../Components/TextureComponent.h"
#include "raylib.h"
#include <vector>

class Player : public Entity {
private:
    float speed;
    float meleeRange;
    float attackCooldown;
    float attackTimer;
    // New: Two separate lists for skills
    std::vector<Skill*> availableSkills;
    std::vector<Skill*> skillQueue;
    size_t currentSkillIndex;
    TextureComponent* textureComponent;

public:
    Player(Vector2 pos, float s = 200.0f);
    ~Player();

    void Update(float dt, std::vector<Enemy*>& enemies);
    
    Vector2 GetPosition() const { return position; }
    void Draw();

    void AddSkillToQueue(Skill* skill);
    void ReorderSkillInQueue(int originalIndex, int newIndex);
    void RemoveSkillFromQueue(int indexToRemove);

    const std::vector<Skill*>& GetAvailableSkills() const { return availableSkills; }
    const std::vector<Skill*>& GetSkillQueue() const { return skillQueue; }
    const Skill* GetCurrentSkill() const;
};