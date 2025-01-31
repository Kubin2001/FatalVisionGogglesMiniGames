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
    miniGameThree = nullptr;
    miniGameFour = nullptr;
    miniGameFive = nullptr;

    ui = nullptr;
    mainMenu = nullptr;
    endScreen = nullptr;
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

    ui = std::make_unique<UI>(renderer);
    ui->CreateFont("arial40px", TextureManager::GetTextureByName("arial40px"), "Textures/Interface/Fonts/arial40px.json");
    ui->CreateFont("arial20px", TextureManager::GetTextureByName("arial20px"), "Textures/Interface/Fonts/arial20px.json");
    ui->CreateFont("arial12px", TextureManager::GetTextureByName("arial12px"), "Textures/Interface/Fonts/arial12px.json");
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
                case 3:
                    miniGameThree = std::make_unique<MiniGameThree>(renderer);
                    miniGameThree->Innit(ui.get());
                    break;
                case 4:
                    miniGameFour = std::make_unique<MiniGameFour>(renderer);
                    miniGameFour->Innit(ui.get());
                    break;
                case 5:
                    miniGameFive = std::make_unique<MiniGameFive>(renderer);
                    miniGameFive->Innit(ui.get());
                    break;
            }
            break;

        case 2:
            endScreen = std::make_unique<EndScreen>(ui.get());
            
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
                case 3:
                    miniGameThree.reset();
                    break;
                case 4:
                    miniGameFour.reset();
                    break;
                case 5:
                    miniGameFive.reset();
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
                    break;
                case 3:
                    if (miniGameThree->Collision(ui.get())) {
                        miniGameThree->Finisch(ui.get());
                        ClearState();
                        gamestate = 2;
                        currentGame = 3;
                        SetUpState();
                    }
                    break;
                case 4:
                    miniGameFour->ManageCreation();
                    miniGameFour->ManageLifespan();
                    break;
                case 5:
                    miniGameFive->ManageStages(ui.get());
                    break;
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

                case 3:
                    miniGameThree->Movement();
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
                    if (miniGameOne->GetTime() < 29) { //bazowo na 1
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
                case 3:
                    miniGameThree->UpdateTime(ui.get());
                    break;
                case 4:
                    miniGameFour->ManageTime();
                    ui->GetButtons()[1]->SetText("Time: " + std::to_string(miniGameFour->GetTime()));
                    if (miniGameFour->GetTime() < 1) { //bazowo na 1
                        miniGameFour->Finisch(ui.get());
                        ClearState();
                        gamestate = 2;
                        currentGame = 4;
                        SetUpState();
                    }
                    break;
                case 5:
                    if (miniGameFive->GetTries() == 0) {
                        miniGameFive->Finisch(ui.get());
                        ClearState();
                        gamestate = 2;
                        currentGame = 5;
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
                if (ui->GetInteractionBoxByName("GameSubTab1")->GetStatus()) {
                    ui->GetInteractionBoxByName("GameSubTab1")->SetStatus(0);
                    ClearState();
                    gamestate = 1;
                    currentGame = 1;
                    SetUpState();
                }
                else if (ui->GetInteractionBoxByName("GameSubTab2")->GetStatus()) {
                    ui->GetInteractionBoxByName("GameSubTab2")->SetStatus(0);
                    ClearState();
                    gamestate = 1;
                    currentGame = 2;
                    SetUpState();
                }
                else if (ui->GetInteractionBoxByName("GameSubTab3")->GetStatus()) {
                    ui->GetInteractionBoxByName("GameSubTab3")->SetStatus(0);
                    ClearState();
                    gamestate = 1;
                    currentGame = 3;
                    SetUpState();
                }
                else if (ui->GetInteractionBoxByName("GameSubTab4")->GetStatus()) {
                    ui->GetInteractionBoxByName("GameSubTab4")->SetStatus(0);
                    ClearState();
                    gamestate = 1;
                    currentGame = 4;
                    SetUpState();
                }
                else if (ui->GetInteractionBoxByName("GameSubTab5")->GetStatus()) {
                    ui->GetInteractionBoxByName("GameSubTab5")->SetStatus(0);
                    ClearState();
                    gamestate = 1;
                    currentGame = 5;
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
                    case 3:
                        miniGameThree->OnClick(event);
                        break;
                    case 4:
                        miniGameFour->OnClick(event);
                        ui->GetButtons()[0]->SetText("Score: " + std::to_string(miniGameFour->GetScore()));
                        break;

                }
                break;
            case 2:
                endScreen->ScoreBoardInput(event);
                int beforeGameState = gamestate;
                int beforeCurrentGame = currentGame;
                if (endScreen->ManageInput(gamestate, currentGame)) {
                    int temp1 = gamestate;
                    int temp2 = currentGame;
                    gamestate = beforeGameState;
                    currentGame = beforeCurrentGame;
                    ClearState();
                    gamestate = temp1;
                    currentGame = temp2;
                    SetUpState();
                }

                break;
        }
    }

    switch (gamestate) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            endScreen->ManageScoreBoard();
            break;
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
                case 3:
                    miniGameThree->Render();
                    break;
                case 4:
                    miniGameFour->Render();
                    break;
                case 5:
                    miniGameFive->Render();
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
