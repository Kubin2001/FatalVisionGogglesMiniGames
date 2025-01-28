#pragma once
#include "UI.h"

class EndScreen {
	private:
		UI* ui = nullptr;
		InteractionBox* scoreButtonRef = nullptr;
		MassageBox* submissionButtonRef = nullptr;

	public:
		EndScreen(UI* ui);

		bool ManageInput(int& gamestate, int& currentGame);

		void ManageScoreBoard();

		void ScoreBoardInput(SDL_Event &event);
};