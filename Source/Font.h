#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>


class Font {
private:
    std::string name;
    SDL_Texture* texture = nullptr;
    SDL_Rect rectangle{ 0,0,0,0 };
    std::vector<SDL_Rect> sourceRectangles;
    int standardInterLine = 0;
public:
    Font(const std::string& name, SDL_Texture* texture, const std::string& jsonPath);

    std::string GetName();

    SDL_Rect* GetRectangle();

    SDL_Texture* GetTexture();

    int GetStandardInterline();

    void SetStandardInterline(int temp);

    void SetTexture(SDL_Texture* temptex);

    bool LoadTextInfo(const std::string& jsonPath);

    void RenderText(SDL_Renderer* renderer, std::string text, int x, int y, float scale = 1.0, int interline = 20, int textStartX = 0, int textStartY = 0);
};

class FontManager {
private:

public:
    std::vector<Font*> fonts;

    FontManager();

    bool CreateFont(const std::string& name, SDL_Texture* texture, const std::string& jsonPath);

    Font* GetFont(const std::string& name);

    ~FontManager();
};