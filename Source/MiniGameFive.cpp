
#include "MiniGameFive.h"
#include "GlobalVariables.h"
#include "TextureManager.h"
#include "Colision.h"
#include <string>
#include <algorithm>
#include <cctype>
#include "Addons.h"
#include "Logger.h"


/*
Lista logów
1: Ile czego siê zespawnowa³o gwiazdy , trójk¹ty, pioruny
2 : Co siê dobrze zgad³o gwiazdy , trójk¹ty, pioruny
*/

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
			this->texture = TexMan::GetTex("Star");
			break;
		case 1:
			this->texture = TexMan::GetTex("Thunder");
			break;
		case 2:
			this->texture = TexMan::GetTex("Triangle");
			break;
		default:
			std::cout << "Type overflow case have gone to default shape (star)\n";
			this->texture = TexMan::GetTex("Star");
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
	this->texture = TexMan::GetTex("Cricle");
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
		TexMan::GetTex("buttonModern"), ui->GetFont("arial40px"),
		"Score: 0", 1, 8, 12, 5);
	ui->SetElementBorderColor("ScoreButton", 135, 206, 250);
	ui->SetElementFontColor("ScoreButton", 255, 168, 0);

	ui->CreateButton("TimeButton", Global::windowWidth * 0.5, 0, Global::windowWidth * 0.5, 150,
		TexMan::GetTex("buttonModern"), ui->GetFont("arial40px"),
		"Time: " + std::to_string(GetTime()), 1, 8, 12, 5);
	ui->SetElementBorderColor("TimeButton", 135, 206, 250);
	ui->SetElementFontColor("TimeButton", 255, 168, 0);
	currentGameState = 0;

	Logger::SetUpNewSession(SceneMan::GetData<std::string>("PlayerName"), SceneMan::GetData<int>("Current Game"));
}

void MiniGameFive::ReStage() {
	SetUpShowingStage();
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
	currentGameState = 0;
}


void MiniGameFive::LogicUpdate() {

}

void MiniGameFive::FrameUpdate() {
	ManageStages();

	if (GetTries() == 0) {
		SceneMan::GetData<int>("Game State") = 2;
		SceneMan::GetData<int>("Current Game") = 5;
		SceneMan::SwitchResetScene("EndScreen", renderer, ui);
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
	Logger::Log(std::to_string(Global::frameCounter) + ",1," + std::to_string(starCount) + "," 
		+ std::to_string(triangleCount) + ","
		+ std::to_string(thunderCount));
	timer = Global::frameCounter;
}


void MiniGameFive::SetUpQuestionStage() {
	std::vector <SDL_Rect> vec;
	ScaleRectanglesToScreen(vec, 3, 300, 100, 100, 100);
	ui->CreateButton("StarsIcon", vec[0].x, vec[0].y, vec[0].w, vec[0].h,
		TexMan::GetTex("StarIcon"), nullptr, "", 1.0f, 0, 0, 5);
	ui->SetElementBorderColor("StarsIcon", 135, 206, 250);
	ui->CreateButton("TrianglesIcon", vec[1].x, vec[1].y, vec[1].w, vec[1].h,
		TexMan::GetTex("TriangleIcon"), nullptr, "", 1.0f, 0, 0, 5);
	ui->SetElementBorderColor("TrianglesIcon", 135, 206, 250);
	ui->CreateButton("ThundersIcon", vec[2].x, vec[2].y, vec[2].w, vec[2].h,
		TexMan::GetTex("ThunderIcon"), nullptr, "", 1.0f, 0, 0, 5);
	ui->SetElementBorderColor("ThundersIcon", 135, 206, 250);

	ScaleRectanglesToScreen(vec, 3, 450, 100, 100, 100);

	ui->CreateTextBox("StarsIconMS", vec[0].x, vec[0].y, vec[0].w, vec[0].h, nullptr, ui->GetFont("arial40px"), "", 1.0f, 30, 30, 5);
	ui->CreateTextBox("TrianglesIconMS", vec[1].x, vec[1].y, vec[1].w, vec[1].h, nullptr, ui->GetFont("arial40px"), "", 1.0f, 30, 30, 5);
	ui->CreateTextBox("ThundersIconMS", vec[2].x, vec[2].y, vec[2].w, vec[2].h, nullptr, ui->GetFont("arial40px"), "", 1.0f, 30, 30, 5);



	ScaleRectanglesToScreen(vec, 1, 600, 400, 100, 100);
	ui->CreateClickBox("SubmitButton", vec[0].x, vec[0].y, vec[0].w, vec[0].h, nullptr, ui->GetFont("arial40px"), "   Submit", 1.0f, 10, 10, 5);
	ui->SetElementBorderColor("SubmitButton", 60, 179, 113);
}


void MiniGameFive::ManageStages() {
	ui->GetButton("ScoreButton")->SetText("Score: " + std::to_string(score));
	if (currentGameState == 0) {
		if (Global::frameCounter % 60 == 0) {
			time--;
		}
		ui->GetButton("TimeButton")->SetText("Time: " + std::to_string(GetTime()));
		if (Global::frameCounter - timer > 600) {// 600 = 10 sekund
			SetUpQuestionStage();
			PopingFigures.clear();
			currentGameState = 1;
		}
	}
	else
	{
		std::string text1 = ui->GetTextBox("StarsIconMS")->GetText();;
		std::string text2 = ui->GetTextBox("TrianglesIconMS")->GetText();
		std::string text3 = ui->GetTextBox("ThundersIconMS")->GetText();
		if (ui->GetTextBox("StarsIconMS")->GetText().length() > 2) {
			text1 = text1.substr(0, 2); 
			ui->GetTextBox("StarsIconMS")->SetText(text1);
		}
		if (ui->GetTextBox("TrianglesIconMS")->GetText().length() > 2) {
			text2 = text2.substr(0, 2); 
			ui->GetTextBox("TrianglesIconMS")->SetText(text2);
		}
		if (ui->GetTextBox("ThundersIconMS")->GetText().length() > 2) {
			text3 = text3.substr(0, 2); 
			ui->GetTextBox("ThundersIconMS")->SetText(text3);
		}

		if (ui->GetClickBox("SubmitButton")->GetStatus() && !text1.empty() && !text2.empty()&& !text3.empty()) {
			ui->GetClickBox("SubmitButton")->SetStatus(0);
			if (IsNumeric(text1) && IsNumeric(text2) && IsNumeric(text3)) {
				bool st = false;
				bool tr = false;
				bool th = false; // ile siê dobrze zgad³o
				if (std::stoi(text1) == starCount) {
					score++;
					st = true;
				}
				if (std::stoi(text2) == triangleCount) {
					score++;
					tr = true;
				}
				if (std::stoi(text3) == thunderCount) {
					score++;
					th = true;
				}
				Logger::Log(std::to_string(Global::frameCounter) + ",2," + std::to_string(st) + ","
					+ std::to_string(tr) + ","
					+ std::to_string(th));
				ui->ClearAllButtons();
				tries--;
				ReStage();
				time = 10;
			}
		}
		else{
			ui->GetClickBox("SubmitButton")->SetStatus(0);
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
	ui->CreateButton("FinalScore", 0, 0, Global::windowWidth, 200,
		TexMan::GetTex("buttonModern"), ui->GetFont("arial40px"),
		"Final Score: " + std::to_string(score), 1, 8, 12, 5);
	ui->SetElementBorderColor("FinalScore", 135, 206, 250);
	ui->SetElementFontColor("FinalScore", 255, 168, 0);
	ui->GetButton("FinalScore")->SetRenderTextType(2);

	Logger::Log(std::to_string(Global::frameCounter) + ",Wynik:" + std::to_string(score));
	SceneMan::AddData<int>("Final Score", score);
	SceneMan::AddData<std::string>("Score File Path", "Data/gameFiveScores.txt");
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