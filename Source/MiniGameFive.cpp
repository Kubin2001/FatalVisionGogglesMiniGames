
#include "MiniGameFive.h"
#include "GlobalVariables.h"
#include "TextureManager.h"
#include "Colision.h"
#include <string>
#include <algorithm>
#include <cctype>

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

void MiniGameFive::Innit(UI* ui) {
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

MiniGameFive::MiniGameFive(SDL_Renderer* renderer) {
	this->renderer = renderer;
	this->texture = TextureManager::GetTextureByName("Cricle");
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


void MiniGameFive::SetUpQuestionStage(UI* ui) {
	ui->CreateButton("StarsIcon", 100, 300, 100, 100, TextureManager::GetTextureByName("StarIcon"), nullptr, "", 1.0f, 0, 0, 5);
	ui->SetUIElementBorderColor("StarsIcon", 135, 206, 250);
	ui->CreateButton("TrianglesIcon", 650, 300, 100, 100, TextureManager::GetTextureByName("TriangleIcon"), nullptr, "", 1.0f, 0, 0, 5);
	ui->SetUIElementBorderColor("TrianglesIcon", 135, 206, 250);
	ui->CreateButton("ThundersIcon", 1200, 300, 100, 100, TextureManager::GetTextureByName("ThunderIcon"), nullptr, "", 1.0f, 0, 0, 5);
	ui->SetUIElementBorderColor("ThundersIcon", 135, 206, 250);

	ui->CreateMassageBox("StarsIconMS", 100, 450, 100, 100, nullptr, ui->GetFont("arial40px"), "", 1.0f, 30, 30, 5);
	ui->CreateMassageBox("TrianglesIconMS", 650, 450, 100, 100, nullptr, ui->GetFont("arial40px"), "", 1.0f, 30, 30, 5);
	ui->CreateMassageBox("ThundersIconMS", 1200, 450, 100, 100, nullptr, ui->GetFont("arial40px"), "", 1.0f, 30, 30, 5);

	ui->CreateInteractionBox("SubmitButton", 500, 600, 400, 100, nullptr, ui->GetFont("arial40px"), "   Submit", 1.0f, 10, 10, 5);
	ui->SetUIElementBorderColor("SubmitButton", 60, 179, 113);
}


void MiniGameFive::ManageStages(UI* ui) {
	ui->GetButtonByName("ScoreButton")->SetText("Score: " + std::to_string(score));
	if (currentGameState == 0) {
		if (Global::frameCounter % 60 == 0) {
			time--;
		}
		ui->GetButtonByName("TimeButton")->SetText("Time: " + std::to_string(GetTime()));
		if (Global::frameCounter - timer > 600) {// 600 = 10 sekund
			SetUpQuestionStage(ui);
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
				Innit(ui);
				time = 10;
			}
		}
		else
		{
			ui->GetInteractionBoxByName("SubmitButton")->SetStatus(0);
		}


	}

}

void MiniGameFive::OnClick(SDL_Event& event) {
	if (event.type == SDL_MOUSEBUTTONUP) {


	}

}

void MiniGameFive::Render() {
	for (auto& it : PopingFigures)
	{
		it.Render(renderer);
	}
}

void MiniGameFive::Finisch(UI* ui) {
	ui->ClearAllButtons();
	ui->CreateButton("FinalScore", 0, 0, Global::windowWidth * 0.5, 200,
		TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial20px"),
		"Final Score: " + std::to_string(score), 1, 8, 12, 5);
	ui->SetUIElementBorderColor("FinalScore", 135, 206, 250);
	ui->SetUIElementFontColor("FinalScore", 255, 168, 0);


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