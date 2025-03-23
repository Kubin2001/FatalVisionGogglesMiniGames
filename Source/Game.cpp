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

    std::cout << "X: " << Global::windowWidth << "Y: " << Global::windowHeight << "\n";



    Global::defaultDrawColor[0] = 30;
    Global::defaultDrawColor[1] = 30;
    Global::defaultDrawColor[2] = 30;
    SDL_SetRenderDrawColor(renderer, Global::defaultDrawColor[0], Global::defaultDrawColor[1], Global::defaultDrawColor[2], 255);
    TextureManager::Start(renderer);
    SoundManager::Innit();
    SoundManager::LoadSounds("Sounds");
    LoadTextures();

    ui = std::make_unique<UI>(renderer);
    ui->CreateFont("arial40px", TextureManager::GetTextureByName("arial40px"), "Textures/Interface/Fonts/arial40px.json");
    ui->CreateFont("arial20px", TextureManager::GetTextureByName("arial20px"), "Textures/Interface/Fonts/arial20px.json");
    ui->CreateFont("arial12px", TextureManager::GetTextureByName("arial12px"), "Textures/Interface/Fonts/arial12px.json");

    SceneManager::AddData("Game State", 0);

    SceneManager::AddData("Current Game", 0);

    MainMenu* mainMenu = new MainMenu();

    MiniGameOne* miniGameOne = new MiniGameOne();

    MiniGameTwo* miniGameTwo = new MiniGameTwo();

    MiniGameThree* miniGameThree = new MiniGameThree();

    MiniGameFour* miniGameFour = new MiniGameFour();

    MiniGameFive* miniGameFive = new MiniGameFive();

    EndScreen* endScreen = new EndScreen();

    SceneManager::AddScene(mainMenu,"Main Menu");

    SceneManager::AddScene(miniGameOne, "MiniGameOne");

    SceneManager::AddScene(miniGameTwo, "MiniGameTwo");

    SceneManager::AddScene(miniGameThree, "MiniGameThree");

    SceneManager::AddScene(miniGameFour, "MiniGameFour");

    SceneManager::AddScene(miniGameFive, "MiniGameFive");

    SceneManager::AddScene(endScreen, "EndScreen");

    SceneManager::SwitchScene("Main Menu",renderer,ui.get());
}



void Game::LoadTextures() {
    TextureManager::LoadMultipleTextures("Textures/Objects");
}

void Game::Logic() {
    Global::frameCounter++;
    SceneManager::GetCurrentScene()->LogicUpdate();
}



void Game::Constant() {
    EventsConstant();
    Render();
}




void Game::EventsConstant() {
    SceneManager::GetCurrentScene()->FrameUpdate();
    while (SDL_PollEvent(&event)) {
        ui->ManageInput(event);
        SceneManager::GetCurrentScene()->Input(event);
        Exit();
    }

}


void Game::Exit() {
    if (event.type == SDL_QUIT) {
        Global::status = false;
    }
    else if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
        Global::status = false;
    }
}


void Game::Render() {
    SDL_RenderClear(renderer);
    SceneManager::GetCurrentScene()->Render();
    ui->Render();
    SDL_RenderPresent(renderer);
}

Game::~Game() {
    TextureManager::Clear();
    SceneManager::Clear();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    //std::cout << "Resources Destroyed";
}
