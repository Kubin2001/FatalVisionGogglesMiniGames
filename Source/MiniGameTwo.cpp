
#include "MiniGameTwo.h"
#include "GlobalVariables.h"
#include "TextureManager.h"
#include "Colision.h"
#include <string>

SDL_Rect* Square::GetRectangle() {
	return &rectangle;
}


SDL_Texture* Square::GetTexture() {
	return texture;
}


void Square::SetTexture(SDL_Texture* text) {
	this->texture = text;
}

Square::Square() {

}

Square::Square(int x, int y, int w, int h, SDL_Texture* text) {
	this->rectangle.x = x;
	this->rectangle.y = y;
	this->rectangle.w = w;
	this->rectangle.h = h;
	this->texture = text;
}

/////////////////////////////////////////////
MiniGameTwo::MiniGameTwo(SDL_Renderer* renderer) {
	this->renderer = renderer;
	staticSquare.SetTexture(TextureManager::GetTextureByName("GenericPurpleSquare"));
	movingSquare.SetTexture(TextureManager::GetTextureByName("GenericOrangeSquare"));
}


void MiniGameTwo::SetUpSquares() {
	int w1 = 200;
	int h1 = 200;
	int x1 = 100;
	int y1 = (Global::windowHeight *0.5);

	SDL_Rect rect{ x1,y1,w1,h1 };
	*staticSquare.GetRectangle() = rect;


	int w2 = 200;
	int h2 = 200;
	int x2 = Global::windowWidth - 100;
	int y2 = (Global::windowHeight * 0.5);
	SDL_Rect rect2{ x2,y2,w2,h2 };
	*movingSquare.GetRectangle() = rect2;
}

void MiniGameTwo::OnClick(SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_SPACE) {
			if (delay < 1) {
				clicks++;

				delay = 6;
			}
		}
	}
	delay--;

}

void MiniGameTwo::Render() {

	SDL_RenderCopy(renderer, staticSquare.GetTexture(), NULL, staticSquare.GetRectangle());

	SDL_RenderCopy(renderer, movingSquare.GetTexture(), NULL, movingSquare.GetRectangle());
}

void MiniGameTwo::Finisch(UI* ui) {
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
		TextureManager::GetTextureByName("buttonModernBlueBorder"), "Final Score: " + std::to_string(score), 27, 24, 3, 40);

	ui->CreateButton("FinalAccuracy", Global::windowWidth * 0.5, 0, Global::windowWidth * 0.5, 200,
		TextureManager::GetTextureByName("buttonModernBlueBorder"), "Accuracy: " + std::to_string(accuracyInt) + "%", 27, 24, 3, 40);


	ui->CreateButton("MainMenuIcon", 200, 400, 200, 200, TextureManager::GetTextureByName("MenuIcon"));

	ui->CreateInteractionBox("MainMenuButton", 200, 600, 200, 100,
		TextureManager::GetTextureByName("buttonModernBlueBorder"), "Main Menu;", 24, 22, 3, 40);

	ui->CreateButton("RetryIcon", Global::windowWidth - 400, 400, 200, 200, TextureManager::GetTextureByName("RetryIcon"));

	ui->CreateInteractionBox("RetryButton", Global::windowWidth - 400, 600, 200, 100,
		TextureManager::GetTextureByName("buttonModernBlueBorder"), "Retry;", 24, 22, 3, 40);
}


int MiniGameTwo::GetScore() {
	return score;
}

