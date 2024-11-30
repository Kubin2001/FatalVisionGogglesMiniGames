#pragma once
#include <SDL.h>
#include "MiniGameOne.h"
#include "UI.h"
#include <memory>

class Game {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

    int gamestate = 0; //0 Menu 1 Gra 2 Wyniki???
    int currentGame = 0; //O Brak Gry Inna wartosæ jakaœ gra


    std::unique_ptr<MiniGameOne> miniGameOne;
    std::unique_ptr<UI> ui;




public:
    Game();

    void Start();

    void SetUpState();

    void ClearState();

    void LoadTextures();

    void GameLogic();

    void EventsLogic();

    void MovementLogic();

    void FiveTickEvents();

    void TwentyTickEvents();

    void FiftyTickEvents();

    void OneSecondTickEvents();

    void HundretTickEvents();

    void FiveHundretTickEvents();

    void GameConstant();

    void EventsConstant();

    void MovementConstant();

    void Exit(const Uint8* state);

    void Render();

    ~Game();

};
