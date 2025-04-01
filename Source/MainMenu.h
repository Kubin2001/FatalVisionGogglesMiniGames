#pragma once

#include "UI.h"
#include "SceneManager.h"

class MainMenu :public Scene{
	public:
		void Init(SDL_Renderer* renderer = nullptr, UI* ui = nullptr)override;

		void LogicUpdate()override;

		void FrameUpdate()override;

		void Input(SDL_Event& event)override;

		void Render()override;

		void Clear()override;

	private:
		void ManagePlayerName(SDL_Event& event);

		void ManageDrunkBox();
};