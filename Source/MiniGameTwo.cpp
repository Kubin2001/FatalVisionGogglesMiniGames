
#include "MiniGameTwo.h"
#include "GlobalVariables.h"
#include "TextureManager.h"
#include "Colision.h"
#include <string>
#include "Addons.h"

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

void MiniGameTwo::Innit(UI* ui) {
	ui->CreateButton("ScoreButton", 0, 0, Global::windowWidth * 0.5, 150,
		TextureManager::GetTextureByName("buttonModern"), "Score: 0", 40, 35, 3, 40, 5);
	ui->SetUIElementBorderColor("ScoreButton", 135, 206, 250);

	ui->CreateButton("TimesLeftButton", Global::windowWidth * 0.5, 0, Global::windowWidth * 0.5, 150,
		TextureManager::GetTextureByName("buttonModern"), "Times Left: ", 40, 35, 3, 40, 5);
	ui->SetUIElementBorderColor("TimesLeftButton", 135, 206, 250);
	SetUpSquares();
}


void MiniGameTwo::SetUpSquares() {
	int w1 = 200;
	int h1 = 200;
	int x1 = (Global::windowWidth * 0.5) - 100;
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
				tries--;
				std::cout << "Clicked\n";
				score -= CalculateEuclidean(colliderMoving.x, colliderStatic.x, colliderMoving.y, colliderStatic.y);
				colided = true;
				delay = 20;
			}
		}
	}

}

void MiniGameTwo::UpdateColliders() {
	colliderMoving.x = movingSquare.GetRectangle()->x + (movingSquare.GetRectangle()->w * 0.5) - 10;
	colliderMoving.y = movingSquare.GetRectangle()->y - (movingSquare.GetRectangle()->h * 0.5) - 10;
	colliderMoving.w = 10;
	colliderMoving.h = 10;

	colliderStatic.x = staticSquare.GetRectangle()->x + (staticSquare.GetRectangle()->w * 0.5) - 10;
	colliderStatic.y = staticSquare.GetRectangle()->y - (staticSquare.GetRectangle()->h * 0.5) - 10;
	colliderStatic.w = 10;
	colliderStatic.h = 10;
}

void MiniGameTwo::MoveSquares() {
	delay--;
	UpdateColliders();
	if (SimpleCollision(colliderMoving, colliderStatic)) {
		colided = true;
	}
	if (colided) {
		movingSquare.GetRectangle()->x = (rand() % 2000) - 1000;
		movingSquare.GetRectangle()->y = (rand() % 2000) - 1000;
		colided = false;
	}
	else
	{
		if (!SimpleCollision(colliderMoving, colliderStatic)) {
			bool xDist = false;
			bool yDist = false;
			int currentMoveSpeed = moveSpeed;
			if (std::abs(GetRectangleCenter(*staticSquare.GetRectangle()).x - 
				GetRectangleCenter(*movingSquare.GetRectangle()).x) > moveSpeed) {
				xDist = true;
			}
			if (std::abs(GetRectangleCenter(*staticSquare.GetRectangle()).y -
				GetRectangleCenter(*movingSquare.GetRectangle()).y) > moveSpeed) {
				yDist = true;
			}




			if (!xDist || !yDist) {
				currentMoveSpeed += currentMoveSpeed;
			}

			if (xDist) {
				if (colliderMoving.x > GetRectangleCenter(colliderStatic).x) {
					movingSquare.GetRectangle()->x -= currentMoveSpeed;
				}
				else
				{
					movingSquare.GetRectangle()->x += currentMoveSpeed;
				}
			}

			if (yDist) {
				if (colliderMoving.y > GetRectangleCenter(colliderStatic).y) {
					movingSquare.GetRectangle()->y -= currentMoveSpeed;
				}
				else
				{
					movingSquare.GetRectangle()->y += currentMoveSpeed;
				}
			}
		}
	}
}

void MiniGameTwo::Render() {

	SDL_RenderCopy(renderer, staticSquare.GetTexture(), NULL, staticSquare.GetRectangle());

	SDL_RenderCopy(renderer, movingSquare.GetTexture(), NULL, movingSquare.GetRectangle());
}

void MiniGameTwo::Finisch(UI* ui) {
	ui->ClearAllButtons();
	ui->CreateButton("FinalScore", 0, 0, Global::windowWidth * 0.5, 200,
		TextureManager::GetTextureByName("buttonModern"), "Final Score: " + std::to_string(score), 27, 24, 3, 40,5);
	ui->SetUIElementBorderColor("FinalScore", 135, 206, 250);

	ui->CreateButton("MainMenuIcon", 200, 400, 200, 200, TextureManager::GetTextureByName("MenuIcon"),"",0,0,0,0,5);
	ui->SetUIElementBorderColor("MainMenuIcon", 135, 206, 250);

	ui->CreateInteractionBox("MainMenuButton", 200, 600, 200, 100,
		TextureManager::GetTextureByName("buttonModern"), "Main Menu;", 24, 22, 3, 40,5);
	ui->SetUIElementBorderColor("MainMenuButton", 135, 206, 250);

	ui->CreateButton("RetryIcon", Global::windowWidth - 400, 400, 200, 200, TextureManager::GetTextureByName("RetryIcon"), "", 0, 0, 0, 0, 5);
	ui->SetUIElementBorderColor("RetryIcon", 135, 206, 250);

	ui->CreateInteractionBox("RetryButton", Global::windowWidth - 400, 600, 200, 100,
		TextureManager::GetTextureByName("buttonModern"), "Retry;", 24, 22, 3, 40,5);
	ui->SetUIElementBorderColor("RetryButton", 135, 206, 250);
}


int MiniGameTwo::GetScore() {
	return score;
}

unsigned short MiniGameTwo::getTries() {
	return tries;
}

void MiniGameTwo::UpdateScore(UI* ui) {
	ui->GetButtonByName("ScoreButton")->SetText("Score: " + std::to_string(score));
	ui->GetButtonByName("TimesLeftButton")->SetText("Tries Left: " + std::to_string(tries));
}

