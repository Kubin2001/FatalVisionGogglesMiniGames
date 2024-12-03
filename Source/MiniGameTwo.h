#pragma once
#include <SDL.h>
#include <vector>
#include "UI.h"


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


class MiniGameTwo {
	private:
	SDL_Renderer* renderer = nullptr;
	Square staticSquare;
	Square movingSquare;
	int score = 0;
	unsigned short tries = 6;
	unsigned int clicks = 0;
	int delay = 15;
	public:
	MiniGameTwo(SDL_Renderer* renderer);

	void SetUpSquares();


	void OnClick(SDL_Event& event);

	void Render();

	void Finisch(UI* ui);

	int GetScore();
};