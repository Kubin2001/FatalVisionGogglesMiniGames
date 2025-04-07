#pragma once
#include <SDL.h>
#include <vector>
#include "UI.h"
#include "SceneManager.h"


class Square {
	private:
		SDL_Rect rectangle;
		SDL_Texture* texture = nullptr;



	public:
		SDL_Rect* GetRectangle();
		SDL_Texture* GetTexture();
		void SetTexture(SDL_Texture *text);
		Square();

		Square(int x, int y, int w, int h,SDL_Texture *text);
};


class MiniGameTwo : public Scene{
	private:
		Square staticSquare;
		Square movingSquare;
		SDL_Rect colliderStatic;
		SDL_Rect colliderMoving;
		int score = 10000;
		unsigned short tries = 6;
		unsigned int clicks = 0;
		bool colided = false;

		unsigned short moveSpeed = 6;

	public:
		void Init(SDL_Renderer* renderer = nullptr, UI* ui = nullptr)override;

		void LogicUpdate()override;

		void FrameUpdate()override;

		void Input(SDL_Event& event)override;

		void Render()override;

		void Clear()override;

		int GetScore();

		unsigned short getTries();

	private:
		void SetUpSquares();

		void UpdateColliders();

		void MoveSquares();

		void UpdateScore();
};