#include "MiniGameThree.h"
#include "GlobalVariables.h"
#include "TextureManager.h"
#include "Colision.h"
#include <string>

/////////////////////////////////////////////

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
		TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial20px"),
		"Score: " + std::to_string(GetScore()), 1, 8, 12, 5);
	ui->SetUIElementBorderColor("ScoreButton", 135, 206, 250);
	ui->SetUIElementFontColor("ScoreButton", 255, 168, 0);

	ui->CreateButton("TimeButton", Global::windowWidth * 0.5, 0, Global::windowWidth * 0.5, 150,
		TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial20px"),
		"Time: " + std::to_string(GetTime()), 1, 8, 12, 5);
	ui->SetUIElementBorderColor("TimeButton", 135, 206, 250);
	ui->SetUIElementFontColor("TimeButton", 255, 168, 0);

	player.GetRectangle()->x = 400;
	player.GetRectangle()->y = 400;
	player.GetRectangle()->w = 50;
	player.GetRectangle()->h = 50;
	player.SetTexture(TextureManager::GetTextureByName("PlayerGameThree"));

	int startX = 1200;

	for (size_t i = 0; i < 6; i++)
	{
		Walls.emplace_back();
		int yHeight = rand() % 400 + 300;
		Walls.back().upperWall.Innit(startX, 0, 100, yHeight, TextureManager::GetTextureByName("GenericPurpleSquare"));

		int yHeight2 = yHeight +200;
		Walls.back().centerCollider.Innit(startX,yHeight2 - 200,100,200, TextureManager::GetTextureByName("GenericOrangeSquare"));
		Walls.back().downWall.Innit(startX, yHeight2, 100, 2000, TextureManager::GetTextureByName("GenericPurpleSquare"));

		startX += 800;
	}
	maxX = startX - 800;
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
		SceneManager::GetData("Game State") = 2;
		SceneManager::GetData("Current Game") = 3;
		SceneManager::SwitchScene("EndScreen", renderer, ui);
	}
}


void MiniGameThree::Input(SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_SPACE) {
			if (playerMoveTimer < 1) {
				playerMoveTimer += 10;
				playerMovement = 1;
			}
		}
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
			it.upperWall.Innit(maxX, 0, 100, yHeight, TextureManager::GetTextureByName("GenericPurpleSquare"));

			int yHeight2 = yHeight + 200;
			it.centerCollider.Innit(maxX, yHeight2 - 200, 100, 200, TextureManager::GetTextureByName("GenericOrangeSquare"));
			it.downWall.Innit(maxX, yHeight2, 100, 2000, TextureManager::GetTextureByName("GenericPurpleSquare"));
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
			ui->GetButtonByName("ScoreButton")->SetText("Score: " + std::to_string(GetScore()));
			it.centerCollider.GetRectangle()->y = -4000; // Do g�ry aby kolizja by�a tylko raz
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
	ui->GetButtonByName("TimeButton")->SetText("Time: " + std::to_string(GetTime()));
	if (time % 20 == 0) {
		wallSpeed++;
	}
}

void MiniGameThree::Clear() {
	ui->ClearAllButtons();
	ui->CreateButton("FinalScore", 0, 0, Global::windowWidth * 0.5, 200,
		TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial20px"),
		"Final Score: " + std::to_string(score), 1, 8, 12, 5);
	ui->SetUIElementBorderColor("FinalScore", 135, 206, 250);
	ui->SetUIElementFontColor("FinalScore", 255, 168, 0);

	ui->CreateButton("FinalTime", Global::windowWidth * 0.5, 0, Global::windowWidth * 0.5, 200,
		TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial20px"),
		"Final Time: " + std::to_string(GetTime()), 1, 8, 12, 5);
	ui->SetUIElementBorderColor("FinalTime", 135, 206, 250);
	ui->SetUIElementFontColor("FinalTime", 255, 168, 0);


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


int MiniGameThree::GetScore() {
	return score;
}

unsigned short MiniGameThree::GetTime() {
	return time;
}