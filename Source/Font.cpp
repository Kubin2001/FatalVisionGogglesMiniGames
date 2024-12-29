#include <iostream>
#include <SDL.h>
#include "Font.h"
#include "json.hpp"
#include <fstream>

Font::Font(const std::string& name, SDL_Texture* texture, const std::string& jsonPath) {
    this->name = name;
    this->texture = texture;
    LoadTextInfo(jsonPath);
}


std::string Font::GetName() {
    return name;
}

SDL_Texture* Font::GetTexture() {
    return texture;
}


void Font::SetTexture(SDL_Texture* temptex) {
    texture = temptex;
}

SDL_Rect* Font::GetRectangle() {
    return &rectangle;
}

bool Font::LoadTextInfo(const std::string& jsonPath) {
    sourceRectangles.resize(200);
    std::ifstream file(jsonPath);
    if (file.is_open()) {
        nlohmann::json jsonData;
        file >> jsonData;

        for (auto& [key, value] : jsonData.items()) {
            if (std::stoi(key) < sourceRectangles.size()) {
                sourceRectangles[std::stoi(key)].x = value["x"].get<int>();
                sourceRectangles[std::stoi(key)].y = value["y"].get<int>();
                sourceRectangles[std::stoi(key)].w = value["width"].get<int>();
                sourceRectangles[std::stoi(key)].h = value["height"].get<int>();
                if (standardInterLine < sourceRectangles[std::stoi(key)].h) {
                    standardInterLine = sourceRectangles[std::stoi(key)].h;
                }
            }
        }

        /*for (size_t i = 0; i < sourceRectangles.size(); i++)
        {
            std::cout << i << " : X: " << sourceRectangles[i].x << " Y: " << sourceRectangles[i].y
                << " W: " << sourceRectangles[i].w << " H: " << sourceRectangles[i].h << "\n";

        }*/
        std::cout << "InterLine: " << standardInterLine << "\n";

    }
    else
    {
        std::cout << "Error font json not loaded correctly!\n";
        return false;
    }
    return true;
}

void Font::RenderText(SDL_Renderer* renderer, std::string text, int x, int y, float scale, int interline, int textStartX, int textStartY) {
    rectangle.x = x + textStartX;
    rectangle.y = y + textStartY;
    rectangle.w = 0;
    rectangle.h = 0;
    int temp = rectangle.x;
    for (int i = 0; i < text.length(); i++)
    {
        if (text[i] < sourceRectangles.size()) {
            if (text[i] != '\n') {
                rectangle.w = sourceRectangles[text[i]].w * scale;
                rectangle.h = sourceRectangles[text[i]].h * scale;
                SDL_RenderCopy(renderer, texture, &sourceRectangles[text[i]], &rectangle);
                rectangle.x += (sourceRectangles[text[i]].w * scale) + 1;
            }
            else
            {
                rectangle.y += interline;
                rectangle.x = temp;
            }
        }
    }
}

int Font::GetStandardInterline() {
    return standardInterLine;
}

void Font::SetStandardInterline(int temp) {
    standardInterLine = temp;
}


/// //////////////////

FontManager::FontManager() {
}


bool FontManager::CreateFont(const std::string& name, SDL_Texture* texture, const std::string& jsonPath) {
    if (fonts.size() > 0) {
        for (auto& it : fonts) {
            if (it->GetName() == name) {
                return false;
            }
        }
    }
    fonts.emplace_back(new Font(name, texture, jsonPath));
    return true;
}

Font* FontManager::GetFont(const std::string& name) {
    if (fonts.size() > 0) {
        for (auto& it : fonts) {
            if (it->GetName() == name) {
                return it;
            }
        }
    }
    return nullptr;
}

FontManager::~FontManager() {
    for (auto& it : fonts) {
        delete it;
    }
    fonts.clear();
}