
#include "MiniGameFour.h"
#include "GlobalVariables.h"
#include "TextureManager.h"
#include "Colision.h"
#include <string>
#include "Logger.h"

/*
Lista logów
1: Ko³o stworzone
2: Ko³o umar³o ze staroœci przez brak klikniêcia
3: Ko³o klikniête przez gracza
4: Gracz nie trafi³ w ko³o klikna³ poza nie
*/

PopingCricleTwo::PopingCricleTwo(int x, int y, int w, int h) {
	this->rectangle.x = x;
	this->rectangle.y = y;
	this->rectangle.w = w;
	this->rectangle.h = h;
	unsigned short random = rand() % 3;
	switch (random)
	{
		case 0:
			texture = TexMan::GetTex("CricleDim1");
			break;
		case 1:
			texture = TexMan::GetTex("CricleDim2");
			break;
		case 2:
			texture = TexMan::GetTex("CricleDim3");
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
	createdCircles = 0;

	ui->CreateButton("ScoreButton", 0, 0, Global::windowWidth * 0.5, 150,
		TexMan::GetTex("buttonModern"), ui->GetFont("arial40px"),
		"Score: 0", 1, 8, 12, 5);
	ui->SetElementBorderColor("ScoreButton", 135, 206, 250);
	ui->SetElementFontColor("ScoreButton", 255, 168, 0);

	ui->CreateButton("TimeButton", Global::windowWidth * 0.5, 0, Global::windowWidth * 0.5, 150,
		TexMan::GetTex("buttonModern"), ui->GetFont("arial40px"),
		"Time: " + std::to_string(GetTime()), 1, 8, 12, 5);
	ui->SetElementBorderColor("TimeButton", 135, 206, 250);
	ui->SetElementFontColor("TimeButton", 255, 168, 0);

	Logger::SetUpNewSession(SceneMan::GetData<std::string>("PlayerName"), SceneMan::GetData<int>("Current Game"));
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
	createdCircles++;
	PopingCircles.back().id = createdCircles;
	Logger::Log(std::to_string(Global::frameCounter) + ",1," + std::to_string(PopingCircles.back().id));
}

void MiniGameFour::ManageLifespan() {
	for (size_t i = 0; i < PopingCircles.size(); i++) {
		PopingCircles[i].lifeSpan--;
		if (PopingCircles[i].lifeSpan < 1) {
			Logger::Log(std::to_string(Global::frameCounter) + ",2," + std::to_string(PopingCircles[i].id));
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
	ui->GetButton("TimeButton")->SetText("Time: " + std::to_string(GetTime()));
	if (GetTime() < 1) { //bazowo na 1
		SceneMan::GetData<int>("Game State") = 1;
		SceneMan::GetData<int>("Current Game") = 4;
		SceneMan::SwitchResetScene("EndScreen", renderer, ui);
	}
}

void MiniGameFour::Input(SDL_Event& event) {
	if (event.type == SDL_MOUSEBUTTONUP) {
		clicks++;
		int x, y;
		SDL_GetMouseState(&x, &y);
		SDL_Rect mouse{ x,y,1,1 };
		for (size_t i = 0; i < PopingCircles.size(); i++)
		{
			if (CircleMouseCollision(*PopingCircles[i].GetRectangle(), mouse)) {

				score++;
				Logger::Log(std::to_string(Global::frameCounter) + ",3," + std::to_string(PopingCircles[i].id));
				PopingCircles.erase(PopingCircles.begin() + i);
				ui->GetButtons()[0]->SetText("Score: " + std::to_string(GetScore()));
				SoundMan::PlaySound("coin");
				break;
			}
			else{
				Logger::Log(std::to_string(Global::frameCounter) + ",4," + std::to_string(PopingCircles[i].id));
			}
		}
	}
	if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
		SceneMan::GetData<int>("Game State") = 2;
		SceneMan::GetData<int>("Current Game") = 4;
		SceneMan::SwitchResetScene("EndScreen", renderer, ui);
	}

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
		TexMan::GetTex("buttonModern"), ui->GetFont("arial20px"),
		"Final Score: " + std::to_string(finalScore), 1, 8, 12, 5);
	ui->SetElementBorderColor("FinalScore", 135, 206, 250);
	ui->SetElementFontColor("FinalScore", 255, 168, 0);

	ui->CreateButton("FinalAccuracy", Global::windowWidth * 0.5, 0, Global::windowWidth * 0.5, 200,
		TexMan::GetTex("buttonModern"), ui->GetFont("arial20px"),
		"Accuracy: " + std::to_string(accuracyInt) + "%", 1, 8, 12, 5);
	ui->SetElementBorderColor("FinalAccuracy", 135, 206, 250);
	ui->SetElementFontColor("FinalAccuracy", 255, 168, 0);

	Logger::Log(std::to_string(Global::frameCounter) + ",Wynik:" + std::to_string(finalScore));
	SceneMan::AddData<int>("Final Score", finalScore);
	SceneMan::AddData<std::string>("Score File Path", "Data/gameFourScores.txt");
}


int MiniGameFour::GetScore() {
	return score;
}

unsigned short MiniGameFour::GetTime() {
	return time;
}