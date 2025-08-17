#pragma once
#include "raylib.h"
#include <string>
#include <map>
#include <vector>

class SkillIconManager {
private:
    std::map<std::string, Texture2D> icons;
    static SkillIconManager* instance;

    // Private constructor to enforce singleton pattern
    SkillIconManager() = default;
    SkillIconManager(const SkillIconManager&) = delete;
    SkillIconManager& operator=(const SkillIconManager&) = delete;

public:
    static SkillIconManager& GetInstance();
    void LoadIconsFromDirectory(const char* directoryPath);
    Texture2D GetIcon(const std::string& skillName);
    void UnloadIcons();
};