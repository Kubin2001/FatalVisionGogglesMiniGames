#pragma once
#include "UI.h"
#include "SceneManager.h"

class EndScreen : public Scene{
	private:
		InteractionBox* scoreButtonRef = nullptr;
		MassageBox* submissionButtonRef = nullptr;

	public:
		void Init(SDL_Renderer* renderer = nullptr, UI* ui = nullptr) override;
		void LogicUpdate() override;
		void FrameUpdate() override;
		void Input(SDL_Event& event) override;
		void Render() override;
		void Clear() override;



		void ManageScoreBoard();

		void ScoreBoardInput(SDL_Event &event);
};