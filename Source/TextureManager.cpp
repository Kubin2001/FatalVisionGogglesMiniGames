#include <iostream>
#include <SDL.h>

#include <filesystem>
#include <vector>
#include <string>
#include "TextureManager.h"


std::unordered_map<std::string, SDL_Texture*> TextureManager::Textures;
std::vector<std::string> TextureManager::SupportedFormats;
SDL_Renderer* TextureManager::renderer = nullptr;
bool TextureManager::isInnit = false;


bool TextureManager::Start(SDL_Renderer *ren) {
   renderer = ren;
   if (renderer != nullptr) {
       isInnit = true;
       SupportedFormats.emplace_back(".png");
       SupportedFormats.emplace_back(".jpg");
       SupportedFormats.emplace_back(".jpeg");
       SupportedFormats.emplace_back(".bmp");
       SupportedFormats.emplace_back(".gif");
       SupportedFormats.emplace_back(".tif");
       SupportedFormats.emplace_back(".tiff");
       SupportedFormats.emplace_back(".tga");
       SupportedFormats.emplace_back(".ico");
       SupportedFormats.emplace_back(".cur");
       SupportedFormats.emplace_back(".pcx");
       SupportedFormats.emplace_back(".xpm");
       return isInnit;
   }

   return false;
}


bool TextureManager::isWorking() {
    return isInnit;
}

bool TextureManager::IsFormatSupported(const std::string& format) {
    for (const auto& it : SupportedFormats) {
        if (format == it) { return true; }
    }
    return false;
}

void TextureManager::LoadSingleTexture(const char* filePath, const std::string& name) {
    if (Textures.find(name) != Textures.end()) {
        std::cout << "Texture: " << name << " is already loaded\n";
        return;
    }
	SDL_Surface* tmpSurface = IMG_Load(filePath);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
    Textures.insert(std::make_pair(name, tex));
}



void TextureManager::LoadMultipleTextures(const std::string& directory){
    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(directory)) {
        if (IsFormatSupported(entry.path().extension().string())) {
            std::string pathString = entry.path().string();
            const char* path = pathString.c_str();
            std::string name = entry.path().stem().string();
            LoadSingleTexture(path, name);
        }
    }
}

void TextureManager::DeepLoad(const std::string& directory) {
    LoadMultipleTextures(directory);
    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.is_directory()) {
            const std::string path = entry.path().string();
            DeepLoad(path);
        }
    }
}


SDL_Texture* TextureManager::GetTextureByName(const std::string& name) {
    auto it = Textures.find(name);
    if (it != Textures.end()) {
        return it->second;
    }
    std::cerr << "Texture not found: " << name << "\n";
    return nullptr;
}

bool TextureManager::DeleteTexture(const std::string& name) {
    auto it = Textures.find(name);
    if (it != Textures.end()) {
        SDL_DestroyTexture(it->second);
        Textures.erase(it);
        return true;
    }
    else
    {
        return false;
    }
}

Point TextureManager::GetTextureSize(const std::string& name) {
    Point p(-1, -1);
    auto it = Textures.find(name);
    if (it != Textures.end()) {
        SDL_QueryTexture(it->second, nullptr, nullptr, &p.x, &p.y);
        return p;
    }
    std::cerr << "Texture not found: " << name << "\n";
    return p;
}

void TextureManager::Clear() {
    for (auto& pair : Textures) {
        SDL_DestroyTexture(pair.second);
    }
    Textures.clear();
}
