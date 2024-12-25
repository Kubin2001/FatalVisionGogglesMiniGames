#pragma once
#include <SDL.h>
#include <vector>
#include "UI.h"
#include "Basics.h"

class PopingCricleTwo :public GameObject {
private:

public:
	int lifeSpan = 1000; //20 sekund
	PopingCricleTwo(int x, int y, int w, int h);
};


class MiniGameFour {
private:
	SDL_Renderer* renderer = nullptr;
	std::vector<PopingCricleTwo> PopingCircles;
	int score = 0;
	unsigned short time = 30;
	unsigned int clicks = 0;
	int delay = 15;
public:
	MiniGameFour(SDL_Renderer* renderer);

	void Innit(UI* ui);

	void CreateCircle(int x, int y, int w, int h);

	void ManageLifespan();

	void ManageCreation();

	void ManageTime();

	void OnClick(SDL_Event& event);

	void Render();

	void Finisch(UI* ui);

	int GetScore();

	unsigned short GetTime();


};