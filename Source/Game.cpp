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
    miniGameTwo = nullptr;
    ui = nullptr;
    mainMenu = nullptr;
}

void Game::Start() {
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Global::windowWidth, Global::windowHeight, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    Global::defaultDrawColor[0] = 30;
    Global::defaultDrawColor[1] = 30;
    Global::defaultDrawColor[2] = 30;
    SDL_SetRenderDrawColor(renderer, Global::defaultDrawColor[0], Global::defaultDrawColor[1], Global::defaultDrawColor[2], 255);
    TextureManager::Start(renderer);
    LoadTextures();

    ui = std::make_unique<UI>(renderer,1);
    ui->LoadTextures();
    ui->font->LoadText(29, 29);
    ui->font->SetTexture(TextureManager::GetTextureByName("fontStandard"));
    ui->SetFontColor(255, 168, 0);
}

void Game::SetUpState() {
    switch (gamestate) {
        case 0:
            mainMenu = std::make_unique<MainMenu>();
            mainMenu->Innit(ui.get());

            break;
        case 1:
            switch (currentGame) {
                case 1:
                    miniGameOne = std::make_unique<MiniGameOne>(renderer);
                    miniGameOne->Innit(ui.get());
                    break;
                case 2:
                    miniGameTwo = std::make_unique<MiniGameTwo>(renderer);
                    miniGameTwo->Innit(ui.get());
                    break;
            }
            break;
    }
}

void Game::ClearState() {

    switch (gamestate) {
        case 0:
            ui->ClearAllButtons();
            break;
        case 1:
            switch (currentGame) {
                case 1:
                    miniGameOne.reset();
                    break;
                case 2:
                    miniGameTwo.reset();
                    break;
            }
            break;
        case 2:
            ui->ClearAllButtons();
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
                case 2:
                    miniGameTwo->UpdateScore(ui.get());
            }
            break;
    }

    FiveTickEvents();
}

void Game::MovementLogic() {
    switch (gamestate) {
        case 0:
            break;
        case 1:
            switch (currentGame) {
                case 1:

                    break;
                case 2:
                    miniGameTwo->MoveSquares();
                    break;
            }
            break;
    }
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
                    if (miniGameOne->GetTime() < 1) { //bazowo na 1
                        miniGameOne->Finisch(ui.get());
                        ClearState();
                        gamestate = 2;
                        currentGame = 1;
                        SetUpState();
                    }
                    
                    break;
                case 2:
                    if (miniGameTwo->getTries() == 0) {
                        miniGameTwo->Finisch(ui.get());
                        ClearState();
                        gamestate = 2;
                        currentGame = 2;
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
                else if (ui->GetInterctionBoxByName("GameSubTab2")->GetStatus()) {
                    ui->GetInterctionBoxByName("GameSubTab2")->SetStatus(0);
                    ClearState();
                    gamestate = 1;
                    currentGame = 2;
                    SetUpState();
                }
                break;
            case 1:
                switch (currentGame) {
                    case 1:
                        miniGameOne->OnClick(event);
                        ui->GetButtons()[0]->SetText("Score: " + std::to_string(miniGameOne->GetScore()));
                        break;
                    case 2:
                        miniGameTwo->OnClick(event);
                        break;

                }
                break;
            case 2:     
                switch (currentGame) {
                    case 1:
                        if (ui->GetInterctionBoxByName("MainMenuButton")->GetStatus()) {
                            ui->GetInterctionBoxByName("MainMenuButton")->SetStatus(0);
                            ClearState();
                            gamestate = 0;
                            currentGame = 0;
                            SetUpState();
                        }
                        else if (ui->GetInterctionBoxByName("RetryButton")->GetStatus()) {
                            ui->GetInterctionBoxByName("RetryButton")->SetStatus(0);
                            ClearState();
                            gamestate = 1;
                            currentGame = 1;
                            SetUpState();
                        }

                        break;
                    case 2:
                        if (ui->GetInterctionBoxByName("MainMenuButton")->GetStatus()) {
                            ui->GetInterctionBoxByName("MainMenuButton")->SetStatus(0);
                            ClearState();
                            gamestate = 0;
                            currentGame = 0;
                            SetUpState();
                        }
                        else if (ui->GetInterctionBoxByName("RetryButton")->GetStatus()) {
                            ui->GetInterctionBoxByName("RetryButton")->SetStatus(0);
                            ClearState();
                            gamestate = 1;
                            currentGame = 2;
                            SetUpState();
                        }
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
                case 2:
                    miniGameTwo->Render();
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
