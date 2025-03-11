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
		static std::vector<std::string> SupportedFormats;
		static SDL_Renderer* renderer;
		static bool isInnit;

	public:
		
		static bool Start(SDL_Renderer* ren);

		static bool isWorking();

		// You need to pass extenstion with . example .png it supports all formats supported by sdl_image IMG_LOAD
		static bool IsFormatSupported(const std::string& format);
		
		static void LoadSingleTexture(const char* filePath, const std::string& name);

		//Loads single folder and uses file names (without extensions) as keys
		// Example tree.png key = tree
		static void LoadMultipleTextures(const std::string& directory);

		// Recursive loading of every folder and subfolder in directory uses file names (without extensions) as keys
		// Example tree.png key = tree
		static void DeepLoad(const std::string& directory);

		static SDL_Texture* GetTextureByName(const std::string &name);

		static bool DeleteTexture(const std::string &name);

		static Point GetTextureSize(const std::string& name);

		static void Clear();
};
