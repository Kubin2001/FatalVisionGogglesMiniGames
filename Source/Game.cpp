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
    miniGameOne = nullptr;
    ui = nullptr;
}

void Game::Start() {
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Global::windowWidth, Global::windowHeight, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    TextureManager::Start(renderer);
    LoadTextures();

    ui = std::make_unique<UI>(renderer);
    ui->LoadTextures();
    ui->font->LoadText(29, 29);
    ui->font->SetTexture(TextureManager::GetTextureByName("fontOrange"));
}

void Game::SetUpState() {
    switch (gamestate) {
        case 0:
            ui->CreateButton("MenuInfo", 300, 0, Global::windowWidth * 0.5, 150,
                TextureManager::GetTextureByName("buttonModernBlueBorder"), "Choose a test", 40, 35, 3, 40);

            ui->CreateButton("GameTab1", 150, 200, 200, 200,
                TextureManager::GetTextureByName("buttonModernBlueBorder"), "Precision", 20, 18, 3, 40);

            ui->CreateInteractionBox("GameSubTab1", 150, 410, 200, 50,
                TextureManager::GetTextureByName("buttonModernBlueBorder"), "Game1", 20, 18, 2, 10);

            ui->CreateButton("GameTab2", 450, 200, 200, 200,
                TextureManager::GetTextureByName("buttonModernBlueBorder"), "Precision2", 20, 18, 3, 40);

            ui->CreateInteractionBox("GameSubTab2", 450, 410, 200, 50,
                TextureManager::GetTextureByName("buttonModernBlueBorder"), "Game2", 20, 18, 2, 10);

            ui->CreateButton("GameTab3", 750, 200, 200, 200,
                TextureManager::GetTextureByName("buttonModernBlueBorder"), "Precision3", 20, 18, 3, 40);

            ui->CreateInteractionBox("GameSubTab3", 750, 410, 200, 50,
                TextureManager::GetTextureByName("buttonModernBlueBorder"), "Game3", 20, 18, 2, 10);

            ui->CreateButton("GameTab4", 1050, 200, 200, 200,
                TextureManager::GetTextureByName("buttonModernBlueBorder"), "Precision4", 20, 18, 3, 40);

            ui->CreateInteractionBox("GameSubTab4", 1050, 410, 200, 50,
                TextureManager::GetTextureByName("buttonModernBlueBorder"), "Game4", 20, 18, 2, 10);

            ui->CreateButton("GameTab5", 150, 500, 200, 200,
                TextureManager::GetTextureByName("buttonModernBlueBorder"), "Precision", 20, 18, 3, 40);

            ui->CreateInteractionBox("GameSubTab5", 150, 710, 200, 50,
                TextureManager::GetTextureByName("buttonModernBlueBorder"), "Game5", 20, 18, 2, 10);

            ui->CreateButton("GameTab6", 450, 500, 200, 200,
                TextureManager::GetTextureByName("buttonModernBlueBorder"), "Precision2", 20, 18, 3, 40);

            ui->CreateInteractionBox("GameSubTab6", 450, 710, 200, 50,
                TextureManager::GetTextureByName("buttonModernBlueBorder"), "Game6", 20, 18, 2, 10);

            ui->CreateButton("GameTab7", 750, 500, 200, 200,
                TextureManager::GetTextureByName("buttonModernBlueBorder"), "Precision3", 20, 18, 3, 40);

            ui->CreateInteractionBox("GameSubTab7", 750, 710, 200, 50,
                TextureManager::GetTextureByName("buttonModernBlueBorder"), "Game7", 20, 18, 2, 10);

            ui->CreateButton("GameTab8", 1050, 500, 200, 200,
                TextureManager::GetTextureByName("buttonModernBlueBorder"), "Precision4", 20, 18, 3, 40);

            ui->CreateInteractionBox("GameSubTab7", 1050, 710, 200, 50,
                TextureManager::GetTextureByName("buttonModernBlueBorder"), "Game8", 20, 18, 2, 10);

            break;
        case 1:
            switch (currentGame) {
                case 1:
                    miniGameOne = std::make_unique<MiniGameOne>(renderer);
                    ui->CreateButton("ScoreButton", 0, 0, Global::windowWidth * 0.5, 150, 
                        TextureManager::GetTextureByName("buttonModernBlueBorder"), "Score: 0", 40, 35, 3, 40);
                    ui->CreateButton("TimeButton", Global::windowWidth * 0.5, 0, Global::windowWidth * 0.5, 150,
                        TextureManager::GetTextureByName("buttonModernBlueBorder"), "Time: " + std::to_string(miniGameOne->GetTime()), 40, 35, 3, 40);
                    break;
            }
            break;
    }
}

void Game::ClearState() {
    ui->ClearAllButtons();
    switch (gamestate) {
        case 0:

            break;
        case 1:
            switch (currentGame) {
                case 1:
                    miniGameOne.reset();

                    break;
            }
            break;
    }
}

void Game::LoadTextures() {
    TextureManager::LoadMultipleTextures("Textures/Objects");
}

void Game::GameLogic() {
    EventsLogic();
    MovementLogic();
}

void Game::EventsLogic() {
    Global::frameCounter++;
    switch (gamestate) {
        case 0:
            break;
        case 1:
            switch (currentGame) {
                case 1:
                    miniGameOne->ManageCreation();
                    miniGameOne->ManageLifespan();
                    break;
            }
            break;
    }

    FiveTickEvents();
}

void Game::MovementLogic() {

}

void Game::FiveTickEvents() {
    if (Global::frameCounter % 5 == 0) {
        //FiveTicks
        //FiveTicks
        if (Global::frameCounter % 20 == 0) {
            TwentyTickEvents();
        }
        if (Global::frameCounter % 60 == 0) {
            OneSecondTickEvents();
        }
        if (Global::frameCounter % 50 == 0) {
            FiftyTickEvents();

            if (Global::frameCounter % 100 == 0) {
                HundretTickEvents();
            }
            if (Global::frameCounter % 500 == 0) {
                FiveHundretTickEvents();
            }
        }
    }
}

void Game::TwentyTickEvents() {

}

void Game::FiftyTickEvents() {

}

void Game::OneSecondTickEvents() {
    switch (gamestate) {
        case 0:
            break;
        case 1:
            switch (currentGame) {
                case 1:
                    miniGameOne->ManageTime();
                    ui->GetButtons()[1]->SetText("Time: " + std::to_string(miniGameOne->GetTime()));
                    if (miniGameOne->GetTime() < 1) {
                        ClearState();
                        gamestate = 0;
                        currentGame = 0;
                        SetUpState();
                    }
                    
                    break;
            }
            break;
    }


}

void Game::HundretTickEvents() {

}

void Game::FiveHundretTickEvents() {

}

void Game::GameConstant() {
    EventsConstant();
    MovementConstant();
    Render();
}




void Game::EventsConstant() {
    while (SDL_PollEvent(&event)) {
        ui->ManageInput(event);
        switch (gamestate) {
            case 0:
                if (ui->GetInterctionBoxByName("GameSubTab1")->GetStatus()) {
                    ui->GetInterctionBoxByName("GameSubTab1")->SetStatus(0);
                    ClearState();
                    gamestate = 1;
                    currentGame = 1;
                    SetUpState();
                }
                break;
            case 1:
                switch (currentGame) {
                    case 1:
                        miniGameOne->OnClick(event);
                        ui->GetButtons()[0]->SetText("Score: " + std::to_string(miniGameOne->GetScore()));

                        break;
                }
                break;
        }

    }
}

void Game::MovementConstant() {
    SDL_PumpEvents();
    const Uint8* state = SDL_GetKeyboardState(NULL);
    Exit(state);
}




void Game::Exit(const Uint8* state) {
    if (state[SDL_SCANCODE_ESCAPE]) {
        Global::status = false;
    }
}


void Game::Render() {
    SDL_RenderClear(renderer);
    switch (gamestate) {
        case 0:
            break;
        case 1:
            switch (currentGame) {
                case 1:
                    miniGameOne->Render();
                    break;
            }
            break;
    }

    ui->Render();
    SDL_RenderPresent(renderer);
}

Game::~Game() {
    TextureManager::Clear();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    //std::cout << "Resources Destroyed";
}
