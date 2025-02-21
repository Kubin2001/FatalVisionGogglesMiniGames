#pragma once

#include <SDL.h>
#include <string>
#include <unordered_map>
#include "UI.h"
#include <memory>
#include "Addons.h"



class Scene {
	protected: 
		std::string name;
		UI* ui = nullptr;
		SDL_Renderer *renderer = nullptr;

	public:
		virtual void Init(SDL_Renderer* renderer = nullptr,UI* ui = nullptr) = 0;

		virtual void LogicUpdate() = 0;   

		virtual void FrameUpdate() = 0;  

		virtual void Input(SDL_Event &event) = 0;

		virtual void Render() = 0;

		virtual void Clear() = 0;
};

class SceneManager {
	private:
		static Scene* currentScene;

		static std::unordered_map<std::string, Scene*> Scenes;

		static std::unordered_map<std::string, std::unique_ptr<AnyData>> SharedData;

	public:
		static void AddScene(Scene *scene, const std::string &sceneName);

		static void SetScene(const std::string& sceneName);

		static void SwitchScene(const std::string& sceneName, SDL_Renderer* renderer = nullptr, UI* ui = nullptr);

		static void Clear();

		static Scene* GetCurrentScene();

		template <typename T>
		static void AddData(const std::string& key, T data);

		template <typename T>
		static T& GetData(const std::string& key);

		static void ClearData(const std::string& key);

		static void ClearAllData();
};

template <typename T>
static void SceneManager::AddData(const std::string& key, T data) {
	SharedData[key] = std::make_unique <AnyContatiner<T>>();
	SharedData[key]->Set(data);

}

template <typename T>
static T& SceneManager::GetData(const std::string& key) {
	if (SharedData.find(key) != SharedData.end()) {
		return SharedData[key]->Get<T>();
	}
	else{
		std::cout << "Error data: " << key << " not found." << "\n";
		return SharedData[key]->Get<T>();
	}
}