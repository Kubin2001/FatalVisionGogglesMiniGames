
#include "MiniGameFive.h"
#include "GlobalVariables.h"
#include "TextureManager.h"
#include "Colision.h"
#include <string>
#include <algorithm>
#include <cctype>
#include "Addons.h"

bool IsNumeric(const std::string& str) {
	return std::all_of(str.begin(), str.end(), ::isdigit);
}


PopingFigure::PopingFigure(int x, int y, int w, int h, int type) {
	this->rectangle.x = x;
	this->rectangle.y = y;
	this->rectangle.w = w;
	this->rectangle.h = h;
	this->figureType = type;
	color[0] = rand() % 205 + 50;
	color[1] = rand() % 205 + 50;
	color[2] = rand() % 205 + 50;
	switch (type)
	{
		case 0:
			this->texture = TextureManager::GetTextureByName("Star");
			break;
		case 1:
			this->texture = TextureManager::GetTextureByName("Thunder");
			break;
		case 2:
			this->texture = TextureManager::GetTextureByName("Triangle");
			break;
		default:
			std::cout << "Type overflow case have gone to default shape (star)\n";
			this->texture = TextureManager::GetTextureByName("Star");
			break;
	}
}

void PopingFigure::Render(SDL_Renderer* renderer) {
	SDL_SetTextureColorMod(GetTexture(), color[0], color[1], color[2]);
	SDL_RenderCopy(renderer, GetTexture(), nullptr, GetRectangle());
	SDL_SetTextureColorMod(GetTexture(), 255, 255, 255);
}
/////////////////////////////////////////////


void MiniGameFive::Init(SDL_Renderer* renderer, UI* ui) {
	this->renderer = renderer;
	this->ui = ui;

	PopingFigures.clear();
	this->texture = TextureManager::GetTextureByName("Cricle");
	score = 0;
	time = 10;
	currentGameState = 0;
	timer = 0;

	tries = 5;

	starCount = 0;
	triangleCount = 0;
	thunderCount = 0;


	SetUpShowingStage();
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
	currentGameState = 0;
}

void MiniGameFive::ReStage() {
	SetUpShowingStage();
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
	currentGameState = 0;
}


void MiniGameFive::LogicUpdate() {

}

void MiniGameFive::FrameUpdate() {
	ManageStages();

	if (GetTries() == 0) {
		SceneManager::GetData<int>("Game State") = 2;
		SceneManager::GetData<int>("Current Game") = 5;
		SceneManager::SwitchScene("EndScreen", renderer, ui);
	}
}

void MiniGameFive::SetUpShowingStage() {
	int currentPos = 10;
	while (currentPos < (Global::windowWidth)-50) {
		int yPos = rand() % (Global::windowHeight - 200) + 150;
		PopingFigures.emplace_back(currentPos,yPos,50,50,rand() % 3);
		currentPos += 100;
	}
	std::cout << PopingFigures.size() << "\n";
	starCount = 0;
	triangleCount = 0;
	thunderCount = 0;
	for (auto& it : PopingFigures) {
		switch (it.figureType) {
			case 0:
				starCount++;
				break;
			case 1:
				thunderCount++;
				break;
			case 2:
				triangleCount++;
				break;
		}
	}
	std::cout << "Stars: " << starCount << " Thunders: " << thunderCount << " Triangles: " << triangleCount << "\n";
	timer = Global::frameCounter;
}


void MiniGameFive::SetUpQuestionStage() {
	std::vector <SDL_Rect> vec;
	ScaleRectanglesToScreen(vec, 3, 300, 100, 100, 100);
	ui->CreateButton("StarsIcon", vec[0].x, vec[0].y, vec[0].w, vec[0].h,
		TextureManager::GetTextureByName("StarIcon"), nullptr, "", 1.0f, 0, 0, 5);
	ui->SetUIElementBorderColor("StarsIcon", 135, 206, 250);
	ui->CreateButton("TrianglesIcon", vec[1].x, vec[1].y, vec[1].w, vec[1].h,
		TextureManager::GetTextureByName("TriangleIcon"), nullptr, "", 1.0f, 0, 0, 5);
	ui->SetUIElementBorderColor("TrianglesIcon", 135, 206, 250);
	ui->CreateButton("ThundersIcon", vec[2].x, vec[2].y, vec[2].w, vec[2].h,
		TextureManager::GetTextureByName("ThunderIcon"), nullptr, "", 1.0f, 0, 0, 5);
	ui->SetUIElementBorderColor("ThundersIcon", 135, 206, 250);

	ScaleRectanglesToScreen(vec, 3, 450, 100, 100, 100);

	ui->CreateMassageBox("StarsIconMS", vec[0].x, vec[0].y, vec[0].w, vec[0].h, nullptr, ui->GetFont("arial40px"), "", 1.0f, 30, 30, 5);
	ui->CreateMassageBox("TrianglesIconMS", vec[1].x, vec[1].y, vec[1].w, vec[1].h, nullptr, ui->GetFont("arial40px"), "", 1.0f, 30, 30, 5);
	ui->CreateMassageBox("ThundersIconMS", vec[2].x, vec[2].y, vec[2].w, vec[2].h, nullptr, ui->GetFont("arial40px"), "", 1.0f, 30, 30, 5);



	ScaleRectanglesToScreen(vec, 1, 600, 400, 100, 100);
	ui->CreateInteractionBox("SubmitButton", vec[0].x, vec[0].y, vec[0].w, vec[0].h, nullptr, ui->GetFont("arial40px"), "   Submit", 1.0f, 10, 10, 5);
	ui->SetUIElementBorderColor("SubmitButton", 60, 179, 113);
}


void MiniGameFive::ManageStages() {
	ui->GetButtonByName("ScoreButton")->SetText("Score: " + std::to_string(score));
	if (currentGameState == 0) {
		if (Global::frameCounter % 60 == 0) {
			time--;
		}
		ui->GetButtonByName("TimeButton")->SetText("Time: " + std::to_string(GetTime()));
		if (Global::frameCounter - timer > 600) {// 600 = 10 sekund
			SetUpQuestionStage();
			PopingFigures.clear();
			currentGameState = 1;
		}
	}
	else
	{
		std::string text1 = ui->GetMassageBoxByName("StarsIconMS")->GetText();;
		std::string text2 = ui->GetMassageBoxByName("TrianglesIconMS")->GetText();
		std::string text3 = ui->GetMassageBoxByName("ThundersIconMS")->GetText();
		if (ui->GetMassageBoxByName("StarsIconMS")->GetText().length() > 2) {
			text1 = text1.substr(0, 2); 
			ui->GetMassageBoxByName("StarsIconMS")->SetText(text1);
		}
		if (ui->GetMassageBoxByName("TrianglesIconMS")->GetText().length() > 2) {
			text2 = text2.substr(0, 2); 
			ui->GetMassageBoxByName("TrianglesIconMS")->SetText(text2);
		}
		if (ui->GetMassageBoxByName("ThundersIconMS")->GetText().length() > 2) {
			text3 = text3.substr(0, 2); 
			ui->GetMassageBoxByName("ThundersIconMS")->SetText(text3);
		}

		if (ui->GetInteractionBoxByName("SubmitButton")->GetStatus() && !text1.empty() && !text2.empty()&& !text3.empty()) {
			ui->GetInteractionBoxByName("SubmitButton")->SetStatus(0);
			if (IsNumeric(text1) && IsNumeric(text2) && IsNumeric(text3)) {
				if (std::stoi(text1) == starCount) {
					score++;
				}
				if (std::stoi(text2) == triangleCount) {
					score++;
				}
				if (std::stoi(text3) == thunderCount) {
					score++;
				}
				ui->ClearAllButtons();
				tries--;
				ReStage();
				time = 10;
			}
		}
		else
		{
			ui->GetInteractionBoxByName("SubmitButton")->SetStatus(0);
		}


	}

}

void MiniGameFive::Input(SDL_Event& event) {

}

void MiniGameFive::Render() {
	for (auto& it : PopingFigures)
	{
		it.Render(renderer);
	}
}

void MiniGameFive::Clear() {
	ui->ClearAllButtons();
	ui->CreateButton("FinalScore", 0, 0, Global::windowWidth * 0.5, 200,
		TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial20px"),
		"Final Score: " + std::to_string(score), 1, 8, 12, 5);
	ui->SetUIElementBorderColor("FinalScore", 135, 206, 250);
	ui->SetUIElementFontColor("FinalScore", 255, 168, 0);

	SceneManager::AddData<int>("Final Score", score);
	SceneManager::AddData<std::string>("Score File Path", "Data/gameFiveScores.txt");
}


int MiniGameFive::GetScore() {
	return score;
}

unsigned short MiniGameFive::GetTime() {
	return time;
}

int MiniGameFive::GetTries() {
	return tries;
}