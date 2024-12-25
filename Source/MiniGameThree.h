#pragma once
#include <SDL.h>
#include <vector>
#include "UI.h"
#include "Basics.h"



class Wall {
	public:
		GameObject upperWall;
		GameObject downWall;
		GameObject centerCollider;
};


class MiniGameThree {
	private:
		SDL_Renderer* renderer = nullptr;
		GameObject player;
		std::vector<Wall> Walls;
		short playerMovement = 0;
		short playerMoveTimer = 0;

		int score = 0;
		unsigned short time = 0;
		int maxX = 0;
		int wallSpeed = 2;

	public:
		MiniGameThree(SDL_Renderer* renderer);

		void Innit(UI* ui);

		void OnClick(SDL_Event& event);

		void MovePlayer();

		void MoveWalls();

		void Movement();

		bool Collision(UI* ui);

		void UpdateTime(UI *ui);

		void Render();

		void Finisch(UI* ui);

		int GetScore();

		unsigned short GetTime();


}; 
