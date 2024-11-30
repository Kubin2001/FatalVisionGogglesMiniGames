
#include "MiniGameOne.h"
#include "GlobalVariables.h"
#include "TextureManager.h"
#include "Colision.h"

SDL_Rect* PopingCricle::GetRectangle() {
	return &rectangle;
}



PopingCricle::PopingCricle(int x, int y, int w, int h) {
	this->rectangle.x = x;
	this->rectangle.y = y;
	this->rectangle.w = w;
	this->rectangle.h = h;
}
/////////////////////////////////////////////
MiniGameOne::MiniGameOne(SDL_Renderer* renderer) {
	this->renderer = renderer;
	this->texture = TextureManager::GetTextureByName("Cricle");
}

void MiniGameOne::CreateCircle(int x, int y, int w, int h) {
	PopingCircles.emplace_back(x,y,w,h);
}

void MiniGameOne::ManageLifespan() {
	for (size_t i = 0; i < PopingCircles.size(); i++) {
		PopingCircles[i].lifeSpan--;
		if (PopingCircles[i].lifeSpan < 1) {
			PopingCircles.erase(PopingCircles.begin() + i);
			if (PopingCircles.size() > 0) {
				i--;
			}

		}
	}
}

void MiniGameOne::ManageCreation() {
	if (PopingCircles.size() < 20) {
		int random = rand() % 60;
		if (random == 0) {
			int x = rand() % (Global::windowWidth - 100) + 50;
			int y = rand() % (Global::windowHeight - 250) + 200;
			int w = (rand() % 60) + 10;
			int h = w;
			CreateCircle(x, y, w, h);
		}
	}
}

void MiniGameOne::ManageTime() {
	time--;
}

void MiniGameOne::OnClick(SDL_Event &event) {

	if (event.button.button == SDL_BUTTON_LEFT) {
		int x, y;
		SDL_GetMouseState(&x,&y);
		SDL_Rect mouse{ x,y,1,1 };
		for (size_t i = 0; i < PopingCircles.size(); i++)
		{
			if (CircleMouseCollision(*PopingCircles[i].GetRectangle(), mouse)) {

				score++;
				PopingCircles.erase(PopingCircles.begin() + i);
				break;
			}
		}


	}

}

void MiniGameOne::Render() {
	for (auto &it: PopingCircles)
	{
		SDL_RenderCopy(renderer, texture, NULL, it.GetRectangle());
	}
}


int MiniGameOne::GetScore() {
	return score;
}

unsigned short MiniGameOne::GetTime() {
	return time;
}