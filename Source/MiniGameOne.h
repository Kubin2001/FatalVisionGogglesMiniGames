#pragma once
#include <SDL.h>
#include <vector>
#include "UI.h"

class PopingCricle{
	private:
		SDL_Rect rectangle;



	public:
		int lifeSpan = 200; //5 sekund
		SDL_Rect* GetRectangle();
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
		int delay = 15;
	public:
		MiniGameOne(SDL_Renderer *renderer);

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