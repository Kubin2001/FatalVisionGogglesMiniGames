#include "MiniGameThree.h"
#include "GlobalVariables.h"
#include "TextureManager.h"
#include "Colision.h"
#include <string>
#include "Logger.h"

/////////////////////////////////////////////

/*
Lista log�w
1: Gracz poruszy� si� do g�ry  (czyli spacja)
2: Gracz zdoby� punkt
3: Kolizja ze �cian� (gra przegrana)
*/

void MiniGameThree::Init(SDL_Renderer* renderer, UI* ui) {
	this->renderer = renderer;
	this->ui = ui;

	playerMovement = 0;
	playerMoveTimer = 0;

	score = 0;
	time = 0;
	maxX = 0;
	wallSpeed = 2;
	Walls.clear();

	ui->CreateButton("ScoreButton", 0, 0, Global::windowWidth * 0.5, 150,
		TexMan::GetTex("buttonModern"), ui->GetFont("arial20px"),
		"Score: " + std::to_string(GetScore()), 1, 8, 12, 5);
	ui->SetElementBorderColor("ScoreButton", 135, 206, 250);
	ui->SetElementFontColor("ScoreButton", 255, 168, 0);

	ui->CreateButton("TimeButton", Global::windowWidth * 0.5, 0, Global::windowWidth * 0.5, 150,
		TexMan::GetTex("buttonModern"), ui->GetFont("arial20px"),
		"Time: " + std::to_string(GetTime()), 1, 8, 12, 5);
	ui->SetElementBorderColor("TimeButton", 135, 206, 250);
	ui->SetElementFontColor("TimeButton", 255, 168, 0);

	player.GetRectangle()->x = 400;
	player.GetRectangle()->y = 400;
	player.GetRectangle()->w = 50;
	player.GetRectangle()->h = 50;
	player.SetTexture(TexMan::GetTex("PlayerGameThree"));

	int startX = 1200;

	for (size_t i = 0; i < 6; i++)
	{
		Walls.emplace_back();
		int yHeight = rand() % 400 + 300;
		Walls.back().upperWall.Innit(startX, 0, 100, yHeight, TexMan::GetTex("GenericPurpleSquare"));

		int yHeight2 = yHeight +200;
		Walls.back().centerCollider.Innit(startX,yHeight2 - 200,100,200, TexMan::GetTex("GenericOrangeSquare"));
		Walls.back().downWall.Innit(startX, yHeight2, 100, 2000, TexMan::GetTex("GenericPurpleSquare"));

		startX += 800;
	}
	maxX = startX - 800;

	Logger::SetUpNewSession(SceneMan::GetData<std::string>("PlayerName"), SceneMan::GetData<int>("Current Game"));
}

void MiniGameThree::LogicUpdate() {

}

void MiniGameThree::FrameUpdate() {
	MovePlayer();
	MoveWalls();
	if (Global::frameCounter % 60 == 0) {
		UpdateTime();
	}


	if (Collision()) {
		SoundMan::PlaySound("lose");
		Logger::Log(std::to_string(Global::frameCounter) + ",3");
		SceneMan::GetData<int>("Game State") = 2;
		SceneMan::GetData<int>("Current Game") = 3;
		SceneMan::SwitchResetScene("EndScreen", renderer, ui);
	}
}


void MiniGameThree::Input(SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_SPACE) {
			if (playerMoveTimer < 1) {
				Logger::Log(std::to_string(Global::frameCounter) + ",1");
				playerMoveTimer += 10;
				playerMovement = 1;
				SoundMan::PlaySound("fling");
			}
		}
	}
	if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
		SceneMan::GetData<int>("Game State") = 2;
		SceneMan::GetData<int>("Current Game") = 3;
		SceneMan::SwitchResetScene("EndScreen", renderer, ui);
	}

}

void MiniGameThree::MovePlayer() {
	if (playerMovement == 1) {
		playerMoveTimer--;
		player.GetRectangle()->y -= 10;
		if (playerMoveTimer < 1) {
			playerMovement = 0;
		}
	}
	else
	{
		player.GetRectangle()->y += 5;
	}
}

void MiniGameThree::MoveWalls() {
	for (auto& it : Walls) {
		if (it.upperWall.GetRectangle()->x < -300) {
			int yHeight = rand() % 400 + 300;
			it.upperWall.Innit(maxX, 0, 100, yHeight, TexMan::GetTex("GenericPurpleSquare"));

			int yHeight2 = yHeight + 200;
			it.centerCollider.Innit(maxX, yHeight2 - 200, 100, 200, TexMan::GetTex("GenericOrangeSquare"));
			it.downWall.Innit(maxX, yHeight2, 100, 2000, TexMan::GetTex("GenericPurpleSquare"));
			break;
		}
	}

	for (auto &it:Walls)
	{
		it.upperWall.GetRectangle()->x -= wallSpeed;
		it.downWall.GetRectangle()->x -= wallSpeed;
		it.centerCollider.GetRectangle()->x -= wallSpeed;
	}
}

bool MiniGameThree::Collision() {
	for (auto& it : Walls)
	{
		if (SimpleCollision(*it.centerCollider.GetRectangle(), *player.GetRectangle())) {
			score++;
			ui->GetButton("ScoreButton")->SetText("Score: " + std::to_string(GetScore()));
			Logger::Log(std::to_string(Global::frameCounter) + ",2");
			it.centerCollider.GetRectangle()->y = -4000; // Do g�ry aby kolizja by�a tylko raz
			SoundMan::PlaySound("point");
		}
		if (SimpleCollision(*it.upperWall.GetRectangle(), *player.GetRectangle())) {
			SDL_Delay(500);
			return true;
		}
		if (SimpleCollision(*it.downWall.GetRectangle(), *player.GetRectangle())) {
			SDL_Delay(500);
			return true;
		}
	}
	if (player.GetRectangle()->y > Global::windowHeight + 200 || player.GetRectangle()->y < -200) {
		return true;
	}
	return false;
}

void MiniGameThree::Render() {
	if (playerMovement == 1) {
		SDL_RenderCopyEx(renderer, player.GetTexture(), nullptr, player.GetRectangle(), -15.0, nullptr, SDL_FLIP_NONE);
	}
	else {
		SDL_RenderCopy(renderer, player.GetTexture(), nullptr, player.GetRectangle());
	}
	for (auto& it : Walls)
	{
		SDL_RenderCopy(renderer, it.upperWall.GetTexture(), nullptr, it.upperWall.GetRectangle());
		SDL_RenderCopy(renderer, it.downWall.GetTexture(), nullptr, it.downWall.GetRectangle());
		SDL_RenderCopy(renderer, it.centerCollider.GetTexture(), nullptr, it.centerCollider.GetRectangle());
	}

}

void MiniGameThree::UpdateTime() {
	time++;
	ui->GetButton("TimeButton")->SetText("Time: " + std::to_string(GetTime()));
	if (time % 20 == 0) {
		wallSpeed++;
	}
}

void MiniGameThree::Clear() {
	ui->ClearAllButtons();
	ui->CreateButton("FinalScore", 0, 0, Global::windowWidth * 0.5, 200,
		TexMan::GetTex("buttonModern"), ui->GetFont("arial20px"),
		"Final Score: " + std::to_string(score), 1, 8, 12, 5);
	ui->SetElementBorderColor("FinalScore", 135, 206, 250);
	ui->SetElementFontColor("FinalScore", 255, 168, 0);

	ui->CreateButton("FinalTime", Global::windowWidth * 0.5, 0, Global::windowWidth * 0.5, 200,
		TexMan::GetTex("buttonModern"), ui->GetFont("arial20px"),
		"Final Time: " + std::to_string(GetTime()), 1, 8, 12, 5);
	ui->SetElementBorderColor("FinalTime", 135, 206, 250);
	ui->SetElementFontColor("FinalTime", 255, 168, 0);

	Logger::Log(std::to_string(Global::frameCounter) + ",Wynik:" + std::to_string(score));
	SceneMan::AddData<int>("Final Score", score);
	SceneMan::AddData<std::string>("Score File Path", "Data/gameThreeScores.txt");
}


int MiniGameThree::GetScore() {
	return score;
}

unsigned short MiniGameThree::GetTime() {
	return time;
}