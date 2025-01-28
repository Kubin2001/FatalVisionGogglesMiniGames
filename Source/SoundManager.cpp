#include <iostream>
#include <SDL.h>
#include "SoundManager.h"
#include <filesystem>

std::unordered_map<std::string, Mix_Chunk*> SoundManager::Sounds;


void SoundManager::Innit() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Failed to sound manager (sdl_mixer error): " << Mix_GetError() << "\n";

    }
}

void SoundManager::LoadSound(const char* filePath, const std::string& name) {
    if (Sounds.find(name) != Sounds.end()) {
        std::cout << "Sound already loaded: " << name << "\n";
        return;
    }
    else
    {
        Sounds.insert(std::make_pair(name, Mix_LoadWAV(filePath)));
    }
    auto it = Sounds.find(name);
    if (it->second == nullptr) {
        std::cout << "Failed to load sound from: " << filePath <<" loaded as nullptr"<< "\n";
    }
}

void SoundManager::LoadSounds(const std::string& directory) {
    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.path().extension() == ".wav") {
            std::string pathString = entry.path().string();
            const char* path = pathString.c_str();
            std::string name = entry.path().stem().string();
            LoadSound(path, name);
        }
    }
}

void SoundManager::PlaySound(const std::string& name) {
    auto it = Sounds.find(name);
    if (it != Sounds.end()) {
        Mix_PlayChannel(-1, it->second, 0);
        return;
    }
    std::cout << "Sound not found: " << name << "\n";
    return ;
}

Mix_Chunk *SoundManager::GetSound(const std::string& name) {
    auto it = Sounds.find(name);
    if (it != Sounds.end()) {
        return it->second;
    }
    std::cout << "Sound not found: "<<name<<"\n";
    return nullptr;
}

bool SoundManager::DeleteSound(const std::string& name) {
    auto it = Sounds.find(name);
    if (it != Sounds.end()) {
        Mix_FreeChunk(it->second);
        Sounds.erase(it);
        return true;
    }
    std::cout << "Sound not found: " << name << "\n";
    return false;
}

void SoundManager::Clear() {
    for (auto& pair : Sounds) {
        Mix_FreeChunk(pair.second);
    }
    Sounds.clear();
}


