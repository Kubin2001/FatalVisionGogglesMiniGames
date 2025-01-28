#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>
#include <unordered_map>
#include "SDL_image.h"
#include "Addons.h"



class TextureManager {
	private:
		static std::unordered_map<std::string, SDL_Texture *> Textures;
		static SDL_Renderer* renderer;
		static bool isInnit;

	public:
		
		static bool Start(SDL_Renderer* ren);

		static bool isWorking();
		
		static void LoadSingleTexture(const char* filePath, const std::string& name);

		static void LoadMultipleTextures(const std::string& directory);

		static SDL_Texture* GetTextureByName(const std::string &name);

		static bool DeleteTexture(const std::string &name);

		static Point GetTextureSize(const std::string& name);

		static void Clear();
		
};
