#pragma once
#include <SDL.h>
#include <vector>
#include "UI.h"
#include "Basics.h"
#include "SceneManager.h"



class Wall {
	public:
		GameObject upperWall;
		GameObject downWall;
		GameObject centerCollider;
};


class MiniGameThree : public Scene{
	private:
		GameObject player;
		std::vector<Wall> Walls;
		short playerMovement = 0;
		short playerMoveTimer = 0;

		int score = 0;
		unsigned short time = 0;
		int maxX = 0;
		int wallSpeed = 2;

	public:
		void Init(SDL_Renderer* renderer = nullptr, UI* ui = nullptr)override;

		void Input(SDL_Event& event)override;

		void LogicUpdate()override;

		void FrameUpdate()override;

		void Render()override;

		void Clear()override;

		bool Collision();

		void UpdateTime();

		int GetScore();

		unsigned short GetTime();

	private:
		void MovePlayer();

		void MoveWalls();
}; 
