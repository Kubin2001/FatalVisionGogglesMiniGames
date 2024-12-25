#include "MiniGameThree.h"
#include "GlobalVariables.h"
#include "TextureManager.h"
#include "Colision.h"
#include <string>

/////////////////////////////////////////////

MiniGameThree::MiniGameThree(SDL_Renderer* renderer) {
	this->renderer = renderer;
}

void MiniGameThree::Innit(UI* ui) {
	ui->CreateButton("ScoreButton", 0, 0, Global::windowWidth * 0.5, 150,
		TextureManager::GetTextureByName("buttonModern"), "Score: " + std::to_string(GetScore()), 40, 35, 3, 40, 5);
	ui->SetUIElementBorderColor("ScoreButton", 135, 206, 250);

	ui->CreateButton("TimeButton", Global::windowWidth * 0.5, 0, Global::windowWidth * 0.5, 150,
		TextureManager::GetTextureByName("buttonModern"), "Time: " + std::to_string(GetTime()), 40, 35, 3, 40, 5);
	ui->SetUIElementBorderColor("TimeButton", 135, 206, 250);

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


void MiniGameThree::OnClick(SDL_Event& event) {
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

void MiniGameThree::Movement() {
	MovePlayer();
	MoveWalls();
}

bool MiniGameThree::Collision(UI *ui) {
	for (auto& it : Walls)
	{
		if (SimpleCollision(*it.centerCollider.GetRectangle(), *player.GetRectangle())) {
			score++;
			ui->GetButtonByName("ScoreButton")->SetText("Score: " + std::to_string(GetScore()));
			it.centerCollider.GetRectangle()->y = -4000; // Do góry aby kolizja by³a tylko raz
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

void MiniGameThree::UpdateTime(UI* ui) {
	time++;
	ui->GetButtonByName("TimeButton")->SetText("Time: " + std::to_string(GetTime()));
	if (time % 20 == 0) {
		wallSpeed++;
	}
}

void MiniGameThree::Finisch(UI* ui) {
	ui->ClearAllButtons();
	ui->CreateButton("FinalScore", 0, 0, Global::windowWidth * 0.5, 200,
		TextureManager::GetTextureByName("buttonModern"), "Final Score: " + std::to_string(score), 27, 24, 3, 40, 5);
	ui->SetUIElementBorderColor("FinalScore", 135, 206, 250);

	ui->CreateButton("FinalTime", Global::windowWidth * 0.5, 0, Global::windowWidth * 0.5, 200,
		TextureManager::GetTextureByName("buttonModern"), "Final Time: " + std::to_string(GetTime()), 27, 24, 3, 40, 5);
	ui->SetUIElementBorderColor("FinalTime", 135, 206, 250);


	ui->CreateButton("MainMenuIcon", 200, 400, 200, 200, TextureManager::GetTextureByName("MenuIcon"), "", 0, 0, 0, 0, 5);
	ui->SetUIElementBorderColor("MainMenuIcon", 135, 206, 250);

	ui->CreateInteractionBox("MainMenuButton", 200, 600, 200, 100,
		TextureManager::GetTextureByName("buttonModern"), "Main Menu;", 22, 19, 6, 40, 5);
	ui->SetUIElementBorderColor("MainMenuButton", 135, 206, 250);

	ui->CreateButton("RetryIcon", Global::windowWidth - 400, 400, 200, 200, TextureManager::GetTextureByName("RetryIcon"), "", 0, 0, 0, 0, 5);
	ui->SetUIElementBorderColor("RetryIcon", 135, 206, 250);

	ui->CreateInteractionBox("RetryButton", Global::windowWidth - 400, 600, 200, 100,
		TextureManager::GetTextureByName("buttonModern"), "Retry;", 22, 19, 6, 40, 5);
	ui->SetUIElementBorderColor("RetryButton", 135, 206, 250);
}


int MiniGameThree::GetScore() {
	return score;
}

unsigned short MiniGameThree::GetTime() {
	return time;
}