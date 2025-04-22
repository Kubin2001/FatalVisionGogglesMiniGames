#pragma once
#include "UI.h"
#include "SceneManager.h"

struct ScoreBox{
	std::string name = "";
	int score = 0;

	bool operator<(const ScoreBox& other) const {
		return score > other.score; 
	}

	bool operator>(const ScoreBox& other) const {
		return score < other.score; 
	}
};

class EndScreen : public Scene{
	private:
		InteractionBox* scoreButtonRef = nullptr;
		MassageBox* submissionButtonRef = nullptr;
		std::vector<ScoreBox> ScoreContainer;

	public:
		void Init(SDL_Renderer* renderer = nullptr, UI* ui = nullptr) override;
		void LogicUpdate() override;
		void FrameUpdate() override;
		void Input(SDL_Event& event) override;
		void Render() override;
		void Clear() override;

		void ManageDrunkBox();

		void ManageScoreBoard();

		void ScoreBoardInput(SDL_Event &event);

		void SetUpScoreBoard(int entries);
};