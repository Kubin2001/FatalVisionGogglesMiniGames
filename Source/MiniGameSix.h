#pragma once
#include "Basics.h"
#include "vector"
#include "SceneManager.h"



class MovingCircle :public GameObject{
	public:
		float speedX = 2.0f;
		float speedY = 2.0f;
		int lifeTime = 0;
};


class Border :public GameObject {

};

class MiniGameSix :public Scene {
	private:
		Border borderLeft;

		Border borderUp;

		Border borderRight;

		Border borderDown;

		int time = 0;

		std::vector<MovingCircle> movingCircles;

		int spawnChance = 0;

		float speed = 1.0f;

		int score = 0;

		SDL_Rect cursorRect{ 0,0,18,27 };

	public:
		void Init(SDL_Renderer* renderer = nullptr, UI* ui = nullptr)override;

		void LogicUpdate() override;

		void FrameUpdate() override;

		void Input(SDL_Event& event)override;

		void Render()override;

		void Clear()override;

	private:
		void UpdateCursor();

		void CreateCircle();

		void CircleLifeTime();

		void MoveCirles();
};