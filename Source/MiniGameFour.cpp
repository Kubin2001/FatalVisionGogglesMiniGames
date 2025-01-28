
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

void MiniGameFour::Innit(UI* ui) {
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

MiniGameFour::MiniGameFour(SDL_Renderer* renderer) {
	this->renderer = renderer;
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
}

void MiniGameFour::OnClick(SDL_Event& event) {
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

void MiniGameFour::Finisch(UI* ui) {
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
	ui->CreateButton("FinalScore", 0, 0, Global::windowWidth * 0.5, 200,
		TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial20px"),
		"Final Score: " + std::to_string(score), 1, 8, 12, 5);
	ui->SetUIElementBorderColor("FinalScore", 135, 206, 250);
	ui->SetUIElementFontColor("FinalScore", 255, 168, 0);

	ui->CreateButton("FinalAccuracy", Global::windowWidth * 0.5, 0, Global::windowWidth * 0.5, 200,
		TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial20px"),
		"Accuracy: " + std::to_string(accuracyInt) + "%", 1, 8, 12, 5);
	ui->SetUIElementBorderColor("FinalAccuracy", 135, 206, 250);
	ui->SetUIElementFontColor("FinalAccuracy", 255, 168, 0);


	ui->CreateButton("MainMenuIcon", 200, 400, 200, 200, TextureManager::GetTextureByName("MenuIcon"), ui->GetFont("arial20px"),
		"", 0, 0, 0, 5);
	ui->SetUIElementBorderColor("MainMenuIcon", 135, 206, 250);

	ui->CreateInteractionBox("MainMenuButton", 200, 600, 200, 100,
		TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial20px"),
		"      Main Menu", 1, 8, 40, 5);
	ui->SetUIElementBorderColor("MainMenuButton", 135, 206, 250);
	ui->SetUIElementFontColor("MainMenuButton", 255, 168, 0);

	ui->CreateButton("RetryIcon", Global::windowWidth - 400, 400, 200, 200, TextureManager::GetTextureByName("RetryIcon"), ui->GetFont("arial20px"),
		"", 0, 0, 0, 5);
	ui->SetUIElementBorderColor("RetryIcon", 135, 206, 250);

	ui->CreateInteractionBox("RetryButton", Global::windowWidth - 400, 600, 200, 100,
		TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial20px"),
		"         Retry", 1, 8, 40, 5);
	ui->SetUIElementBorderColor("RetryButton", 135, 206, 250);
	ui->SetUIElementFontColor("RetryButton", 255, 168, 0);



	ui->CreateButton("ScoreBoardIcon", 600, 400, 200, 200, TextureManager::GetTextureByName("ScoreIcon"), ui->GetFont("arial20px"),
		"", 0, 0, 0, 5);
	ui->SetUIElementBorderColor("ScoreBoardIcon", 135, 206, 250);

	ui->CreateInteractionBox("ScoreBoardButton", 600, 600, 200, 100,
		TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial20px"),
		"      Submit", 1, 8, 40, 5);
	ui->SetUIElementBorderColor("ScoreBoardButton", 135, 206, 250);
	ui->SetUIElementFontColor("ScoreBoardButton", 255, 168, 0);
}


int MiniGameFour::GetScore() {
	return score;
}

unsigned short MiniGameFour::GetTime() {
	return time;
}