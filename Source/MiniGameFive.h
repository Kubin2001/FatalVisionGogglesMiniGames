#pragma once
#include <SDL.h>
#include <vector>
#include "UI.h"
#include "Basics.h"
#include "SceneManager.h"

class PopingFigure :public GameObject {
private:
	unsigned char color[3];
public:
	int figureType = 0;
	PopingFigure(int x, int y, int w, int h, int type);

	void Render(SDL_Renderer *renderer);
};


class MiniGameFive :public Scene{
private:
	std::vector<PopingFigure> PopingFigures;
	SDL_Texture* texture = nullptr;
	int score = 0;
	unsigned short time = 10;
	int currentGameState = 0;
	int timer = 0;

	int tries = 5;

	int starCount = 0;
	int triangleCount = 0;
	int thunderCount = 0;
public:

	void Init(SDL_Renderer* renderer = nullptr, UI* ui = nullptr);

	void LogicUpdate()override;

	void FrameUpdate()override;

	void Input(SDL_Event& event)override;

	void Render()override;

	void Clear()override;

	void ReStage();

	int GetScore();

	unsigned short GetTime();

	int GetTries();


private:

	void SetUpShowingStage();

	void SetUpQuestionStage();

	void ManageStages();

};