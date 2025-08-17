#pragma once
#include "raylib.h"
#include <vector>
#include <string>
#include "../Skills/Skill.h" // Include the base skill class
#include "../Entities/Player.h" // To get player info

class SkillBar {
private:
    std::vector<Texture2D> skillIcons;
    const Player& player; // Reference to the player object

    void LoadSkillIcons();

public:
    SkillBar(const Player& player);

    void Draw();
};