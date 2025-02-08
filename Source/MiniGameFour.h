#pragma once
#include <SDL.h>
#include <vector>
#include "UI.h"
#include "Basics.h"
#include "SceneManager.h"

class PopingCricleTwo :public GameObject {
private:

public:
	int lifeSpan = 1000; //20 sekund
	PopingCricleTwo(int x, int y, int w, int h);
};


class MiniGameFour: public Scene {
private:
	std::vector<PopingCricleTwo> PopingCircles;
	int score = 0;
	unsigned short time = 30;
	unsigned int clicks = 0;
	int delay = 15;
public:
	void Init(SDL_Renderer* renderer = nullptr, UI* ui = nullptr)override;

	void LogicUpdate()override;

	void FrameUpdate()override;

	void Input(SDL_Event& event)override;

	void Render()override;

	void Clear()override;


	void ManageLifespan();

	void ManageCreation();

	void ManageTime();

	int GetScore();

	unsigned short GetTime();

private:

	void CreateCircle(int x, int y, int w, int h);


};