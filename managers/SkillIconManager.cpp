#include "SkillIconManager.h"
#include "raylib.h"
#include <iostream>

SkillIconManager* SkillIconManager::instance = nullptr;

SkillIconManager& SkillIconManager::GetInstance() {
    if (!instance) {
        instance = new SkillIconManager();
    }
    return *instance;
}

void SkillIconManager::LoadIconsFromDirectory(const char* directoryPath) {
    FilePathList files = LoadDirectoryFiles(directoryPath);
    for (int i = 0; i < files.count; ++i) {
        std::string filePath = files.paths[i];
        std::string fileName = GetFileName(filePath.c_str());

        // We only care about Icon.png files
        if (fileName.find("Icon.png") != std::string::npos) {
            std::string skillName = GetFileNameWithoutExt(fileName.c_str());
            skillName.erase(skillName.find("Icon"), 4); // Remove "Icon" from the name
            
            Texture2D icon = LoadTexture(filePath.c_str());
            if (icon.id != 0) {
                icons[skillName] = icon;
            } else {
                std::cout << "Warning: Could not load skill icon: " << filePath << std::endl;
            }
        }
    }
    // Load a placeholder texture for safety
    icons["placeholder"] = LoadTexture("assets/icons/placeholder.png");
    UnloadDirectoryFiles(files);
}

Texture2D SkillIconManager::GetIcon(const std::string& skillName) {
    if (icons.count(skillName)) {
        return icons[skillName];
    }
    std::cout << "Error: Icon for skill '" << skillName << "' not found. Using placeholder." << std::endl;
    return icons["placeholder"];
}

void SkillIconManager::UnloadIcons() {
    for (auto const& [name, texture] : icons) {
        UnloadTexture(texture);
    }
    icons.clear();
}