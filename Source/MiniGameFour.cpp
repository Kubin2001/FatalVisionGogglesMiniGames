
#include "MiniGameFour.h"
#include "GlobalVariables.h"
#include "TextureManager.h"
#include "Colision.h"
#include <string>


PopingCricleTwo::PopingCricleTwo(int x, int y, int w, int h) {
	this->rectangle.x = x;
	this->rectangle.y = y;
	this->rectangle.w = w;
	this->rectangle.h = h;
	unsigned short random = rand() % 3;
	switch (random)
	{
		case 0:
			texture = TextureManager::GetTextureByName("CricleDim1");
			break;
		case 1:
			texture = TextureManager::GetTextureByName("CricleDim2");
			break;
		case 2:
			texture = TextureManager::GetTextureByName("CricleDim3");
			break;
	}
}
/////////////////////////////////////////////

void MiniGameFour::Init(SDL_Renderer* renderer, UI* ui) {
	this->renderer = renderer;
	this->ui = ui;

	PopingCircles.clear();
	score = 0;
	time = 30;
	clicks = 0;
	delay = 15;

	ui->CreateButton("ScoreButton", 0, 0, Global::windowWidth * 0.5, 150,
		TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial40px"),
		"Score: 0", 1, 8, 12, 5);
	ui->SetUIElementBorderColor("ScoreButton", 135, 206, 250);
	ui->SetUIElementFontColor("ScoreButton", 255, 168, 0);

	ui->CreateButton("TimeButton", Global::windowWidth * 0.5, 0, Global::windowWidth * 0.5, 150,
		TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial40px"),
		"Time: " + std::to_string(GetTime()), 1, 8, 12, 5);
	ui->SetUIElementBorderColor("TimeButton", 135, 206, 250);
	ui->SetUIElementFontColor("TimeButton", 255, 168, 0);
}

void MiniGameFour::LogicUpdate() {

}

void MiniGameFour::FrameUpdate() {
	ManageLifespan();
	ManageCreation();
	if (Global::frameCounter % 60 == 0) {
		ManageTime();
	}
}

void MiniGameFour::CreateCircle(int x, int y, int w, int h) {
	PopingCircles.emplace_back(x, y, w, h);
}

void MiniGameFour::ManageLifespan() {
	for (size_t i = 0; i < PopingCircles.size(); i++) {
		PopingCircles[i].lifeSpan--;
		if (PopingCircles[i].lifeSpan < 1) {
			PopingCircles.erase(PopingCircles.begin() + i);
			if (PopingCircles.size() > 0) {
				i--;
			}

		}
	}
}

void MiniGameFour::ManageCreation() {
	if (PopingCircles.size() < 20) {
		int random = rand() % 60;
		if (random == 0) {
			int x = rand() % (Global::windowWidth - 100) + 50;
			int y = rand() % (Global::windowHeight - 250) + 200;
			int w = (rand() % 60) + 10;
			int h = w;
			CreateCircle(x, y, w, h);
		}
	}
}

void MiniGameFour::ManageTime() {
	time--;
	ui->GetButtonByName("TimeButton")->SetText("Time: " + std::to_string(GetTime()));
	if (GetTime() < 25) { //bazowo na 1
		SceneManager::GetData<int>("Game State") = 1;
		SceneManager::GetData<int>("Current Game") = 4;
		SceneManager::SwitchScene("EndScreen", renderer, ui);
	}
}

void MiniGameFour::Input(SDL_Event& event) {
	if (event.button.button == SDL_BUTTON_LEFT) {
		if (delay < 1) {
			clicks++;
			int x, y;
			SDL_GetMouseState(&x, &y);
			SDL_Rect mouse{ x,y,1,1 };
			for (size_t i = 0; i < PopingCircles.size(); i++)
			{
				if (CircleMouseCollision(*PopingCircles[i].GetRectangle(), mouse)) {

					score++;
					PopingCircles.erase(PopingCircles.begin() + i);
					ui->GetButtons()[0]->SetText("Score: " + std::to_string(GetScore()));
					SoundManager::PlaySound("coin");
					break;
				}
			}
			delay = 6;
		}



	}
	delay--;

}

void MiniGameFour::Render() {
	for (auto& it : PopingCircles)
	{
		SDL_RenderCopy(renderer, it.GetTexture(), NULL, it.GetRectangle());
	}
}

void MiniGameFour::Clear() {
	ui->ClearAllButtons();
	double accuracy = 0;
	int accuracyInt = 0;
	if (clicks > 0) {
		accuracy = (static_cast<double>(score) / static_cast<double>(clicks)) * 100;
		accuracyInt = static_cast<int>(accuracy);
	}
	else
	{
		accuracyInt = 0;
	}

	int finalScore = ((score * 100) * (accuracy / 100));
	ui->CreateButton("FinalScore", 0, 0, Global::windowWidth * 0.5, 200,
		TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial20px"),
		"Final Score: " + std::to_string(finalScore), 1, 8, 12, 5);
	ui->SetUIElementBorderColor("FinalScore", 135, 206, 250);
	ui->SetUIElementFontColor("FinalScore", 255, 168, 0);

	ui->CreateButton("FinalAccuracy", Global::windowWidth * 0.5, 0, Global::windowWidth * 0.5, 200,
		TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial20px"),
		"Accuracy: " + std::to_string(accuracyInt) + "%", 1, 8, 12, 5);
	ui->SetUIElementBorderColor("FinalAccuracy", 135, 206, 250);
	ui->SetUIElementFontColor("FinalAccuracy", 255, 168, 0);

	SceneManager::AddData<int>("Final Score", finalScore);
	SceneManager::AddData<std::string>("Score File Path", "Data/gameFourScores.txt");
}


int MiniGameFour::GetScore() {
	return score;
}

unsigned short MiniGameFour::GetTime() {
	return time;
}