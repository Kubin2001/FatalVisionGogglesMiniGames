#include <SDL.h>
#include <iostream>
#include <string>
#include "SDL_image.h"
#include "Game.h"
#include "GlobalVariables.h"
#include "TextureManager.h"


Game::Game() {
    window = nullptr;
    renderer = nullptr;

    ui = nullptr;
}

void Game::Start() {
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Global::windowWidth, Global::windowHeight, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);

    SDL_GetWindowSize(window, &Global::windowWidth, &Global::windowHeight);

    //std::cout << "X: " << Global::windowWidth << "Y: " << Global::windowHeight << "\n";



    Global::defaultDrawColor[0] = 30;
    Global::defaultDrawColor[1] = 30;
    Global::defaultDrawColor[2] = 30;
    SDL_SetRenderDrawColor(renderer, Global::defaultDrawColor[0], Global::defaultDrawColor[1], Global::defaultDrawColor[2], 255);
    TexMan::Start(renderer);
    SoundMan::Innit();
    SoundMan::LoadSounds("Sounds");
    LoadTextures();

    ui = std::make_unique<UI>(renderer);
    ui->CreateFont("arial40px", TexMan::GetTex("arial40px"), "Textures/Interface/Fonts/arial40px.json");
    ui->CreateFont("arial20px", TexMan::GetTex("arial20px"), "Textures/Interface/Fonts/arial20px.json");
    ui->CreateFont("arial12px", TexMan::GetTex("arial12px"), "Textures/Interface/Fonts/arial12px.json");

    SceneMan::AddData("Game State", 0);

    SceneMan::AddData("Current Game", 0);

    MainMenu* mainMenu = new MainMenu();

    MiniGameOne* miniGameOne = new MiniGameOne();

    MiniGameTwo* miniGameTwo = new MiniGameTwo();

    MiniGameThree* miniGameThree = new MiniGameThree();

    MiniGameFour* miniGameFour = new MiniGameFour();

    MiniGameFive* miniGameFive = new MiniGameFive();

    MiniGameSix* miniGameSix = new MiniGameSix();

    EndScreen* endScreen = new EndScreen();

    SceneMan::AddRegisterScene(mainMenu,"Main Menu", []() { return new MainMenu(); });

    SceneMan::AddRegisterScene(miniGameOne, "MiniGameOne", []() { return new MiniGameOne(); });

    SceneMan::AddRegisterScene(miniGameTwo, "MiniGameTwo", []() { return new MiniGameTwo; });

    SceneMan::AddRegisterScene(miniGameThree, "MiniGameThree", []() { return new MiniGameThree(); });

    SceneMan::AddRegisterScene(miniGameFour, "MiniGameFour", []() { return new MiniGameFour(); });

    SceneMan::AddRegisterScene(miniGameFive, "MiniGameFive", []() { return new MiniGameFive; });

    SceneMan::AddRegisterScene(miniGameSix, "MiniGameSix", []() { return new MiniGameSix; });

    SceneMan::AddRegisterScene(endScreen, "EndScreen", []() { return new EndScreen(); });

    SceneMan::SwitchResetScene("Main Menu",renderer,ui.get());


    //Ustawianie na pocz¹tek pustego nicku gracza i false jako ¿e gra leci bez googli 
    SceneMan::AddData<std::string>("PlayerName", "");
    SceneMan::AddData<bool>("UsesGoogles",false);
}



void Game::LoadTextures() {
    TexMan::LoadMultiple("Textures/Objects");
}

void Game::Logic() {
    Global::frameCounter++;
    SceneMan::GetCurrentScene()->LogicUpdate();
}



void Game::Constant() {
    EventsConstant();
    Render();
}




void Game::EventsConstant() {
    SceneMan::GetCurrentScene()->FrameUpdate();
    while (SDL_PollEvent(&event)) {
        ui->ManageInput(event);
        SceneMan::GetCurrentScene()->Input(event);
        Exit();
    }

}


void Game::Exit() {
    if (event.type == SDL_QUIT) {
        Global::status = false;
    }
}


void Game::Render() {
    SDL_RenderClear(renderer);
    SceneMan::GetCurrentScene()->Render();
    ui->Render();
    SDL_RenderPresent(renderer);
}

Game::~Game() {
    TexMan::Clear();
    SceneMan::Clear();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    //std::cout << "Resources Destroyed";
}
