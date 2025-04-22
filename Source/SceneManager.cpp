#include "SceneManager.h"
#include "iostream"

std::unordered_map<std::string, Scene*> SceneManager::Scenes;
std::unordered_map<std::string, std::unique_ptr<AnyData>> SceneManager::SharedData;
Scene* SceneManager::currentScene = nullptr;

std::unordered_map<std::string, std::function<Scene* ()>> SceneFactory::factories;




void SceneManager::AddScene(Scene* scene, const std::string& sceneName) {
	if (Scenes.find(sceneName) == Scenes.end()) {
		scene->name = sceneName;
		Scenes.insert(std::make_pair(sceneName, scene));
	}
	else
	{
		std::cerr << "ERROR: Scene '" << sceneName << "' already exists!\n";
	}

}

void SceneManager::AddRegisterScene(Scene* scene, const std::string& sceneName, std::function<Scene* ()> factoryFn) {
	if (Scenes.find(sceneName) == Scenes.end()) {
		scene->name = sceneName;
		Scenes.insert(std::make_pair(sceneName, scene));
		SceneFactory::RegisterScene(sceneName,factoryFn);
	}
	else
	{
		std::cerr << "ERROR: Scene '" << sceneName << "' already exists!\n";
	}

}

void SceneManager::SetScene(const std::string& sceneName) {
	if (Scenes.find(sceneName) != Scenes.end()) {
		currentScene = Scenes[sceneName];

	}
	else
	{
		std::cerr << "ERROR: Scene '" << sceneName << "' not found!\n";
	}
}

void SceneManager::SwitchScene(const std::string& sceneName, SDL_Renderer* renderer, UI* ui) {
	if (Scenes.find(sceneName) != Scenes.end()) {
		if (currentScene != nullptr) {
			currentScene->Clear();
		}
		currentScene = Scenes[sceneName];
		currentScene->Init(renderer,ui);

	}
	else
	{
		std::cerr << "ERROR: Scene '" << sceneName << "' not found!\n";
	}
}

void SceneManager::SwitchResetScene(const std::string& sceneName, SDL_Renderer* renderer, UI* ui) {
	if (Scenes.find(sceneName) != Scenes.end()) {
		if (currentScene != nullptr) { // usuwanie obecnej sceny
			currentScene->Clear();
			Scenes[currentScene->name] = nullptr;
			delete currentScene;
		}


		currentScene = Scenes[sceneName];

		if (currentScene == nullptr) {
			Scenes[sceneName] = SceneFactory::CreateScene(sceneName);
			currentScene = Scenes[sceneName];
			Scenes[sceneName]->name = sceneName;

			currentScene->name = sceneName;
		}
		currentScene->Init(renderer, ui);

	}
	else
	{
		std::cerr << "ERROR: Scene '" << sceneName << "' not found!\n";
	}
}

void SceneManager::Clear() {
	for (auto& pair : Scenes) {
		delete pair.second;
	}
	Scenes.clear();
}


Scene* SceneManager::GetCurrentScene() {
	return currentScene;
}

bool SceneManager::IsData(const std::string& key) {
	if (SharedData.find(key) != SharedData.end()) {
		return true;
	}
	return false;
}

void SceneManager::ClearData(const std::string& key) {
	if (SharedData.find(key) != SharedData.end()) {
		SharedData.erase(key);
	}
}

void SceneManager::ClearAllData() {
	SharedData.clear();
}


void SceneFactory::RegisterScene(const std::string& shapeName, std::function<Scene* ()> factoryFn) {
	factories[shapeName] = factoryFn;
}


Scene* SceneFactory::CreateScene(const std::string& shapeName) {
	if (factories.count(shapeName)) {
		return factories[shapeName]();
	}
	return nullptr;
}