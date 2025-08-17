#pragma once
#include "raylib.h"
#include "../Entities/Player.h"
#include "../skills/Skill.h"

class SkillMenu {
private:
    Player& nonConstPlayer;
    
    bool isDragging;
    Skill* draggedSkill;
    Vector2 draggedOffset;
    int draggedSkillOriginalIndex; // New: To track the skill's original spot

public:
    SkillMenu(Player& player);

    void Update();
    void Draw();
};