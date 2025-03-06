
#include "MiniGameOne.h"
#include "GlobalVariables.h"
#include "TextureManager.h"
#include "Colision.h"
#include <string>


PopingCricle::PopingCricle(int x, int y, int w, int h) {
	this->rectangle.x = x;
	this->rectangle.y = y;
	this->rectangle.w = w;
	this->rectangle.h = h;
}
/////////////////////////////////////////////

void MiniGameOne::Init(SDL_Renderer* renderer, UI* ui) {
	this->renderer = renderer;
	this->ui = ui;
	this->texture = TextureManager::GetTextureByName("Cricle");

	PopingCircles.clear();
	score = 0;
	time = 30;
	clicks = 0;
	createdCircles = 0;

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


void MiniGameOne::LogicUpdate() {

}

void MiniGameOne::FrameUpdate() {
	ui->GetButtons()[0]->SetText("Score: " + std::to_string(GetScore()));
	if (Global::frameCounter % 60 == 0) {
		ManageTime();
		ui->GetButtons()[1]->SetText("Time: " + std::to_string(GetTime()));
		if (GetTime() < 28) { //bazowo na 1
			SceneManager::GetData<int>("Game State") = 2;
			SceneManager::GetData<int>("Current Game") = 1;
			SceneManager::SwitchScene("EndScreen",renderer,ui);

		}
	}
	ManageCreation();
	ManageLifespan();
}

void MiniGameOne::CreateCircle(int x, int y, int w, int h) {
	PopingCircles.emplace_back(x,y,w,h);
	createdCircles++;
}

void MiniGameOne::ManageLifespan() {
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

void MiniGameOne::ManageCreation() {
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

void MiniGameOne::ManageTime() {
	time--;
}

void MiniGameOne::Input(SDL_Event &event) {
	if (event.type == SDL_MOUSEBUTTONUP){
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
	}
}

void MiniGameOne::Render() {
	for (auto &it: PopingCircles)
	{
		SDL_RenderCopy(renderer, texture, NULL, it.GetRectangle());
	}
}

void MiniGameOne::Clear() {
	ui->ClearAllButtons();
	double accuracy = 0;
	int accuracyInt = 0;
	if (clicks > 0) {
		accuracy = (static_cast<double>(score) / static_cast<double>(clicks)) * 100;
		accuracyInt = static_cast<int>(accuracy);
	}
	else{accuracyInt = 0;}

	int finalScore = (score -(createdCircles - score)) * accuracy; // Chyba nie mo¿e byæ dzielenia przez zero ale jest +1 jakby co

	ui->CreateButton("Circles Clicked", 0, 0, Global::windowWidth /3, 200,
		TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial20px"),
		"Circles Clicked: " + std::to_string(score) + "/" + std::to_string(createdCircles), 1, 8, 12, 5);
	ui->SetUIElementBorderColor("Circles Clicked", 135, 206, 250);
	ui->SetUIElementFontColor("Circles Clicked", 255, 168, 0);

	ui->CreateButton("FinalAccuracy", Global::windowWidth * 0.3, 0, Global::windowWidth /3, 200,
		TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial20px"),
		"Accuracy: " + std::to_string(accuracyInt) + "%", 1, 8, 12, 5);
	ui->SetUIElementBorderColor("FinalAccuracy", 135, 206, 250);
	ui->SetUIElementFontColor("FinalAccuracy", 255, 168, 0);

	ui->CreateButton("FinalScore", Global::windowWidth * 0.6, 0, Global::windowWidth - (Global::windowWidth * 0.6), 200,
		TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial20px"),
		"FinalScore: " + std::to_string(finalScore), 1, 8, 12, 5);
	ui->SetUIElementBorderColor("FinalScore", 135, 206, 250);
	ui->SetUIElementFontColor("FinalScore", 255, 168, 0);


	SceneManager::AddData<int>("Final Score", finalScore);
	SceneManager::AddData<std::string>("Score File Path", "Data/gameOneScores.txt");

}


int MiniGameOne::GetScore() {
	return score;
}

unsigned short MiniGameOne::GetTime() {
	return time;
}