#pragma once
#include <SDL.h>
#include <vector>
#include "UI.h"
#include "Basics.h"

class PopingFigure :public GameObject {
private:
	int figureType = 0;
	unsigned char color[3];
public:
	PopingFigure(int x, int y, int w, int h, int type);

	void Render(SDL_Renderer *renderer);
};


class MiniGameFive {
private:
	SDL_Renderer* renderer = nullptr;
	std::vector<PopingFigure> PopingFigures;
	SDL_Texture* texture = nullptr;
	int score = 0;
	unsigned short time = 30;
	int currentGameState = 0;
	int timer = 0;
public:
	MiniGameFive(SDL_Renderer* renderer);

	void Innit(UI* ui);

	void SetUpShowingStage();

	void SetUpQuestionStage(UI* ui);

	void ManageStages(UI* ui);

	void OnClick(SDL_Event& event);

	void Render();

	void Finisch(UI* ui);

	int GetScore();

	unsigned short GetTime();


};