
#include "MiniGameTwo.h"
#include "GlobalVariables.h"
#include "TextureManager.h"
#include "Colision.h"
#include <string>
#include "Addons.h"
#include "Logger.h"

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


void MiniGameTwo::Init(SDL_Renderer* renderer, UI* ui) {
	this->renderer = renderer;
	this->ui = ui;

	score = 10000;
	tries = 6;
	clicks = 0;
	colided = false;

	unsigned short moveSpeed = 6;
	SetUpSquares();

	staticSquare.SetTexture(TexMan::GetTex("GenericPurpleSquare"));
	movingSquare.SetTexture(TexMan::GetTex("GenericOrangeSquare"));

	ui->CreateButton("ScoreButton", 0, 0, Global::windowWidth * 0.5, 150,
		TexMan::GetTex("buttonModern"), ui->GetFont("arial40px"), "Score: 0", 1, 8, 12, 5);
	ui->SetElementBorderColor("ScoreButton", 135, 206, 250);
	ui->SetElementFontColor("ScoreButton", 255, 168, 0);

	ui->CreateButton("TimesLeftButton", Global::windowWidth * 0.5, 0, Global::windowWidth * 0.5, 150,
		TexMan::GetTex("buttonModern"), ui->GetFont("arial40px"), "Times Left: ", 1, 8, 12, 5);
	ui->SetElementBorderColor("TimesLeftButton", 135, 206, 250);
	ui->SetElementFontColor("TimesLeftButton", 255, 168, 0);

	Logger::SetUpNewSession(SceneMan::GetData<std::string>("PlayerName"), SceneMan::GetData<int>("Current Game"));
}

void MiniGameTwo::LogicUpdate() {

}

void MiniGameTwo::FrameUpdate() {
	MoveSquares();

	UpdateScore();

	if (getTries() == 0) {
		SceneMan::GetData<int>("Game State") = 2;
		SceneMan::GetData<int>("Current Game") = 2;
		SceneMan::SwitchResetScene("EndScreen", renderer, ui);
	}
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

void MiniGameTwo::Input(SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_SPACE) {
			tries--;
			score -= CalculateEuclidean(colliderMoving.x, colliderStatic.x, colliderMoving.y, colliderStatic.y);
			colided = true;
			Logger::Log(std::to_string(Global::frameCounter) + "," + std::to_string(CalculateEuclidean(colliderMoving.x, colliderStatic.x, colliderMoving.y, colliderStatic.y)));
		}
	}
	if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
		SceneMan::GetData<int>("Game State") = 2;
		SceneMan::GetData<int>("Current Game") = 2;
		SceneMan::SwitchResetScene("EndScreen", renderer, ui);
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

void MiniGameTwo::Clear() {
	ui->ClearAllButtons();
	ui->CreateButton("FinalScore", 0, 0, Global::windowWidth, 200,
		TexMan::GetTex("buttonModern"), ui->GetFont("arial40px"),
		"Final Score: " + std::to_string(score), 1, 8, 12, 5);
	ui->SetElementBorderColor("FinalScore", 135, 206, 250);
	ui->SetElementFontColor("FinalScore", 255, 168, 0);

	Logger::Log(std::to_string(Global::frameCounter) + ",Wynik:" + std::to_string(score));
	SceneMan::AddData<int>("Final Score", score);
	SceneMan::AddData<std::string>("Score File Path", "Data/gameTwoScores.txt");
}


int MiniGameTwo::GetScore() {
	return score;
}

unsigned short MiniGameTwo::getTries() {
	return tries;
}

void MiniGameTwo::UpdateScore() {
	ui->GetButton("ScoreButton")->SetText("Score: " + std::to_string(score));
	ui->GetButton("TimesLeftButton")->SetText("Tries Left: " + std::to_string(tries));
}

