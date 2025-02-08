#pragma once
#include <SDL.h>
#include "MainMenu.h"
#include "EndScreen.h"
#include "MiniGameOne.h"
#include "MiniGameTwo.h"
#include "MiniGameThree.h"
#include "MiniGameFour.h"
#include "MiniGameFive.h"
#include "UI.h"
#include <memory>

class Game {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

    std::unique_ptr<UI> ui;


public:
    Game();

    void Start();

    void LoadTextures();

    void Logic();

    void Constant();

    void EventsConstant();


    void Exit();

    void Render();

    ~Game();

};
