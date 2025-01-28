#pragma once
#include <SDL.h>
#include <vector>
#include "UI.h"
#include "Basics.h"

class PopingCricle :public GameObjectBasic{
	private:

	public:
		int lifeSpan = 200; //5 sekund
		PopingCricle(int x, int y, int w, int h);
};


class MiniGameOne{
	private:
		SDL_Renderer* renderer = nullptr;
		std::vector<PopingCricle> PopingCircles;
		SDL_Texture* texture = nullptr;
		int score = 0;
		unsigned short time = 30;
		unsigned int clicks = 0;
		unsigned short createdCircles = 0;
	public:
		MiniGameOne(SDL_Renderer *renderer);

		void Innit(UI* ui);

		void CreateCircle(int x, int y, int w, int h);	

		void ManageLifespan();

		void ManageCreation();

		void ManageTime();

		void OnClick(SDL_Event& event);

		void Render();

		void Finisch(UI *ui);

		int GetScore();

		unsigned short GetTime();


};