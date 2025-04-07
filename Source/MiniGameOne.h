#pragma once
#include <SDL.h>
#include <vector>
#include "UI.h"
#include "Basics.h"
#include "SceneManager.h"

class PopingCricle :public GameObjectBasic{
	private:

	public:
		int lifeSpan = 200; //5 sekund
		PopingCricle(int x, int y, int w, int h);
		unsigned int id = 0;
};


class MiniGameOne :public Scene {
	private:
		std::vector<PopingCricle> PopingCircles;
		SDL_Texture* texture = nullptr;
		int score = 0;
		unsigned short time = 30;
		unsigned int clicks = 0;
		unsigned short createdCircles = 0;
	public:
		void Init(SDL_Renderer* renderer = nullptr, UI* ui = nullptr)override;

		void LogicUpdate() override;

		void FrameUpdate() override;

		void Input(SDL_Event& event)override;

		void Render()override;

		void Clear()override;

		int GetScore();

		unsigned short GetTime();

	private:

		void CreateCircle(int x, int y, int w, int h);

		void ManageLifespan();

		void ManageCreation();

		void ManageTime();


};