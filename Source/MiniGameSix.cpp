#include "MiniGameSix.h"
#include "GlobalVariables.h"
#include "Colision.h"
#include "Logger.h"


void MiniGameSix::Init(SDL_Renderer* renderer, UI* ui) {
	this->ui = ui;
	this->renderer = renderer;
	movingCircles.clear();
	time = 0;
	speed = 1.0f;
	score = 0;
	spawnChance = 0;

	ui->CreateButton("ScoreButton", 0, 0, Global::windowWidth * 0.5, 150,
		TexMan::GetTex("buttonModern"), ui->GetFont("arial40px"),
		"Score: 0", 1, 8, 12, 5);
	ui->SetElementBorderColor("ScoreButton", 135, 206, 250);
	ui->SetElementFontColor("ScoreButton", 255, 168, 0);

	ui->CreateButton("TimeButton", Global::windowWidth * 0.5, 0, Global::windowWidth * 0.5, 150,
		TexMan::GetTex("buttonModern"), ui->GetFont("arial40px"),
		"Time: " + std::to_string(time), 1, 8, 12, 5);
	ui->SetElementBorderColor("TimeButton", 135, 206, 250);
	ui->SetElementFontColor("TimeButton", 255, 168, 0);

	SDL_Rect leftRect{ 0,150,100,Global::windowHeight };
	*borderLeft.GetRectangle() = leftRect;
	borderLeft.SetTexture(TexMan::GetTex("GenericOrangeSquare"));

	SDL_Rect downRect{ 0,Global::windowHeight - 100,Global::windowWidth,100 };
	*borderDown.GetRectangle() = downRect;
	borderDown.SetTexture(TexMan::GetTex("GenericOrangeSquare"));

	SDL_Rect rectRight{ Global::windowWidth - 100,150,100,Global::windowHeight };
	*borderRight.GetRectangle() = rectRight;
	borderRight.SetTexture(TexMan::GetTex("GenericOrangeSquare"));

	SDL_Rect upRect{ 0,150,Global::windowWidth,100 };
	*borderUp.GetRectangle() = upRect;
	borderUp.SetTexture(TexMan::GetTex("GenericOrangeSquare"));

	Logger::SetUpNewSession(SceneMan::GetData<std::string>("PlayerName"), SceneMan::GetData<int>("Current Game"));
	SDL_ShowCursor(SDL_DISABLE);
}

void MiniGameSix::LogicUpdate() {
	if (Global::frameCounter % 60 == 0) {
		time++;
		score += 1 * time;
		spawnChance++;
		if (time % 10 == 0) {
			speed += 0.2;
		}
	}

	MoveCirles();
	if (Global::frameCounter % 30 == 0) {
		CircleLifeTime();
	}

	int chance = rand() % 100;
	if (spawnChance > chance) {
		CreateCircle();
	}

	if (time > 2) {
		bool collided = false;

		for (auto it : movingCircles) {
			if (SimpleCollision(*it.GetRectangle(), cursorRect)) { collided = true; }
		}

		if (collided) {
			SceneMan::GetData<int>("Game State") = 2;
			SceneMan::GetData<int>("Current Game") = 6;
			SceneMan::SwitchResetScene("EndScreen", renderer, ui);
		}
	}
	

}

void MiniGameSix::FrameUpdate() {
	ui->GetButton("TimeButton")->SetText("Time: " + std::to_string(time));
	ui->GetButton("ScoreButton")->SetText("Score: " + std::to_string(score));
	UpdateCursor();

	if (Global::frameCounter % 5 == 0) {
		Point p = GetRectangleCenter(cursorRect);
		std::string massage = std::to_string(p.x) + "," + std::to_string(p.y);
		Logger::Log(std::to_string(Global::frameCounter) + ",1," + massage);
	}
	
}

void MiniGameSix::Input(SDL_Event& event) {
	if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
		SceneMan::GetData<int>("Game State") = 2;
		SceneMan::GetData<int>("Current Game") = 6;
		SceneMan::SwitchResetScene("EndScreen", renderer, ui);
	}
}

void MiniGameSix::Render() {
	for (auto& it : movingCircles) {
		SDL_RenderCopy(renderer, it.GetTexture(), nullptr, it.GetRectangle());
	}

	SDL_RenderCopy(renderer, borderLeft.GetTexture(), nullptr, borderLeft.GetRectangle());

	SDL_RenderCopy(renderer, borderUp.GetTexture(), nullptr, borderUp.GetRectangle());

	SDL_RenderCopy(renderer, borderDown.GetTexture(), nullptr, borderDown.GetRectangle());

	SDL_RenderCopy(renderer, borderRight.GetTexture(), nullptr, borderRight.GetRectangle());

	SDL_RenderCopy(renderer, TexMan::GetTex("cursor"), nullptr, &cursorRect);
}

void MiniGameSix::Clear() {
	SDL_ShowCursor(SDL_ENABLE);
	ui->ClearAllButtons();

	ui->CreateButton("FinalScore", 0, 0, Global::windowWidth, 200,
		TexMan::GetTex("buttonModern"), ui->GetFont("arial40px"),
		"FinalScore: " + std::to_string(score), 1, 8, 12, 5);
	ui->SetElementBorderColor("FinalScore", 135, 206, 250);
	ui->SetElementFontColor("FinalScore", 255, 168, 0);
	ui->GetButton("FinalScore")->SetRenderTextType(2);

	Logger::Log(std::to_string(Global::frameCounter) + ",Wynik:" + std::to_string(score));
	SceneMan::AddData<int>("Final Score", score);
	SceneMan::AddData<std::string>("Score File Path", "Data/gameSixScores.txt");
}

void MiniGameSix::UpdateCursor() {
	int x, y;
	SDL_GetMouseState(&x,&y);
	cursorRect.x = x;
	cursorRect.y = y;
	if (cursorRect.x < borderLeft.GetRectangle()->x + borderLeft.GetRectangle()->w) { //left
		cursorRect.x = borderLeft.GetRectangle()->x + borderLeft.GetRectangle()->w;
	}
	if (cursorRect.y < borderUp.GetRectangle()->y + borderUp.GetRectangle()->h) { //up
		cursorRect.y = borderUp.GetRectangle()->y + borderUp.GetRectangle()->h;
	}
	if (cursorRect.x > borderRight.GetRectangle()->x) { //right
		cursorRect.x = borderRight.GetRectangle()->x - cursorRect.w;
	}
	if (cursorRect.y > borderDown.GetRectangle()->y) { //down
		cursorRect.y = borderDown.GetRectangle()->y - cursorRect.h;
	}
}

void MiniGameSix::CreateCircle() {
	movingCircles.emplace_back();
	int random = rand() % 4; // decyzja o kierunku

	switch (random) {
		case 0: // Dodajemy z lewej
			movingCircles.back().GetRectangle()->x = 100;
			movingCircles.back().GetRectangle()->y = rand() % (Global::windowHeight -100) + 150;
			movingCircles.back().speedX = speed;
			movingCircles.back().speedY = 0.0f;
			break;
		case 1: // Dodajemy z góry
			movingCircles.back().GetRectangle()->x = rand() % (Global::windowWidth - 100) + 150;
			movingCircles.back().GetRectangle()->y = 100;
			movingCircles.back().speedX = 0.0f;
			movingCircles.back().speedY = speed;
			break;
		case 2:// Dodajemy z prawej
			movingCircles.back().GetRectangle()->x = Global::windowWidth - 100;
			movingCircles.back().GetRectangle()->y = rand() % (Global::windowHeight - 100) + 150;
			movingCircles.back().speedX = -speed;
			movingCircles.back().speedY = 0.0f;
			break;
		case 3:// Dodajemy z do³u
			movingCircles.back().GetRectangle()->x = rand() % (Global::windowWidth - 100) + 150;;
			movingCircles.back().GetRectangle()->y = Global::windowHeight - 100;
			movingCircles.back().speedX = 0.0f;
			movingCircles.back().speedY = -speed;
			break;
	}
	movingCircles.back().GetRectangle()->w = 30;
	movingCircles.back().GetRectangle()->h = 30;
	movingCircles.back().SetTexture(TexMan::GetTex("MovingCircle"));



}

void MiniGameSix::CircleLifeTime() {
	int maxLifeTime = 20 + speed;
	for (int i = 0; i < movingCircles.size(); i++) {
		movingCircles[i].lifeTime++;
		if (movingCircles[i].lifeTime > maxLifeTime) {
			movingCircles.erase(movingCircles.begin() + i);
			i--;
		}
	}
}

void MiniGameSix::MoveCirles() {
	for (auto& it : movingCircles) {
		it.GetRectangle()->x += it.speedX;
		it.GetRectangle()->y += it.speedY;
	}
}