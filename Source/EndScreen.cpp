#include "EndScreen.h"
#include "GlobalVariables.h"
#include <cctype>
#include <fstream>
#include <string>
#include <algorithm>

bool IsAlphabetic(const std::string& str) {
    for (char c : str) {
        if (!std::isalpha(static_cast<unsigned char>(c))) {
            return false;
        }
    }
    return true; 
}



void EndScreen::Init(SDL_Renderer* renderer, UI* ui) {
    this->renderer = renderer;
    this->ui = ui;

    std::vector<SDL_Rect> vec1;
    ScaleRectanglesToScreen(vec1, 3, 400, 200, 200, 250);

    ui->CreateButton("MainMenuIcon", vec1[0].x, vec1[0].y, vec1[0].w, vec1[0].h,
        TextureManager::GetTextureByName("MenuIcon"), ui->GetFont("arial20px"),
        "", 0, 0, 0, 5);
    ui->SetUIElementBorderColor("MainMenuIcon", 135, 206, 250);

    ui->CreateInteractionBox("ScoreBoardIcon", vec1[1].x, vec1[1].y, vec1[1].w, vec1[1].h,
        TextureManager::GetTextureByName("ScoreIcon"), ui->GetFont("arial20px"),
        "", 0, 0, 0, 5);
    ui->SetUIElementBorderColor("ScoreBoardIcon", 135, 206, 250);

    ui->CreateButton("RetryIcon", vec1[2].x, vec1[2].y, vec1[2].w, vec1[2].h,
        TextureManager::GetTextureByName("RetryIcon"), ui->GetFont("arial20px"),
        "", 0, 0, 0, 5);
    ui->SetUIElementBorderColor("RetryIcon", 135, 206, 250);




    ScaleRectanglesToScreen(vec1, 3, 625, 200, 100, 250);
    ui->CreateInteractionBox("MainMenuButton", vec1[0].x, vec1[0].y, vec1[0].w, vec1[0].h,
        TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial20px"),
        "      Main Menu", 1, 8, 40, 5);
    ui->SetUIElementBorderColor("MainMenuButton", 135, 206, 250);
    ui->SetUIElementFontColor("MainMenuButton", 255, 168, 0);

    ui->CreateInteractionBox("ScoreBoardButton", vec1[1].x, vec1[1].y, vec1[1].w, vec1[1].h,
        TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial20px"),
        "      Submit", 1, 8, 40, 5);
    ui->SetUIElementBorderColor("ScoreBoardButton", 135, 206, 250);
    ui->SetUIElementFontColor("ScoreBoardButton", 255, 168, 0);

    ui->CreateInteractionBox("RetryButton", vec1[2].x, vec1[2].y, vec1[2].w, vec1[2].h,
        TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial20px"),
        "         Retry", 1, 8, 40, 5);
    ui->SetUIElementBorderColor("RetryButton", 135, 206, 250);
    ui->SetUIElementFontColor("RetryButton", 255, 168, 0);

    ui->CreateInteractionBox("DrunkBox", Global::windowWidth - 100, Global::windowHeight - 200, 100, 100,
        nullptr, ui->GetFont("arial20px"), "", 1, 8, 12, 5);

    for (auto& it : ui->GetInteractionBoxes()) {
        it->SetHoverFilter(true, 255, 255, 255, 150, "hoverSound");
        it->SetClickSound("click");
    }

    if (SceneManager::GetData<bool>("UsesGoogles")) {
        ui->SetUIElementColor("DrunkBox", 255, 0, 0);
    }
    else {
        ui->SetUIElementColor("DrunkBox", 0, 255, 0);
    }
}

void EndScreen::LogicUpdate(){}
void EndScreen::FrameUpdate(){
    ManageScoreBoard();
    ManageDrunkBox();
}

void EndScreen::Input(SDL_Event& event) {
    if (ui->GetInteractionBoxByName("MainMenuButton")->ConsumeStatus()) {
        SceneManager::GetData<int>("Game State") = 0;
        SceneManager::GetData<int>("Current Game") = 0;
        SceneManager::SwitchResetScene("Main Menu", renderer, ui);
        return;
    }
    int currentGame = SceneManager::GetData<int>("Current Game");
    switch (currentGame) {
        case 1:
            if (ui->GetInteractionBoxByName("RetryButton")->ConsumeStatus()) {
                SceneManager::GetData<int>("Game State") = 1;
                SceneManager::GetData<int>("Current Game") = 1;
                SceneManager::SwitchResetScene("MiniGameOne", renderer, ui);
                return;
            }
            break;
        case 2:
            if (ui->GetInteractionBoxByName("RetryButton")->ConsumeStatus()) {
                SceneManager::GetData<int>("Game State") = 1;
                SceneManager::GetData<int>("Current Game") = 2;
                SceneManager::SwitchResetScene("MiniGameTwo", renderer, ui);
                return;
            }
            break;
        case 3:
            if (ui->GetInteractionBoxByName("RetryButton")->ConsumeStatus()) {
                SceneManager::GetData<int>("Game State") = 1;
                SceneManager::GetData<int>("Current Game") = 3;
                SceneManager::SwitchResetScene("MiniGameThree", renderer, ui);
                return;
            }
            break;
        case 4:
            if (ui->GetInteractionBoxByName("RetryButton")->ConsumeStatus()) {
                SceneManager::GetData<int>("Game State") = 1;
                SceneManager::GetData<int>("Current Game") = 4;
                SceneManager::SwitchResetScene("MiniGameFour", renderer, ui);
                return;
            }
            break;

        case 5:
            if (ui->GetInteractionBoxByName("RetryButton")->ConsumeStatus()) {
                SceneManager::GetData<int>("Game State") = 1;
                SceneManager::GetData<int>("Current Game") = 5;
                SceneManager::SwitchResetScene("MiniGameFive", renderer, ui);
                return;
            }

        case 6:
            if (ui->GetInteractionBoxByName("RetryButton")->ConsumeStatus()) {
                SceneManager::GetData<int>("Game State") = 1;
                SceneManager::GetData<int>("Current Game") = 6;
                SceneManager::SwitchResetScene("MiniGameSix", renderer, ui);
                return;
            }

            break;
    }
    ScoreBoardInput(event);
}

void EndScreen::ManageScoreBoard() {
    if (ui->GetInteractionBoxByName("ScoreBoardButton")->ConsumeStatus()) { // Sprawdzanie czy trzeba utworzyæ submission button
        if (submissionButtonRef == nullptr) {

            scoreButtonRef = ui->GetInteractionBoxByName("ScoreBoardButton");
            ui->GetInteractionBoxByName("ScoreBoardButton")->TurnOff();
            ui->GetInteractionBoxByName("ScoreBoardButton")->Hide();
            ui->CreateMassageBox("SubmissionButton", scoreButtonRef->GetRectangle()->x, scoreButtonRef->GetRectangle()->y,
                scoreButtonRef->GetRectangle()->w, scoreButtonRef->GetRectangle()->h, nullptr, ui->GetFont("arial40px"), "", 1.0f, 0, 0, 5);


            submissionButtonRef = ui->GetMassageBoxByName("SubmissionButton");
            ui->SetUIElementColor("SubmissionButton", 255, 255, 255);
            ui->SetUIElementBorderColor("SubmissionButton", 135, 206, 250);
            ui->SetUIElementFontColor("SubmissionButton", 255, 168, 0);
            submissionButtonRef->SetRenderTextType(2);

        }
    }
    if (submissionButtonRef != nullptr) { // Sprawdzanie poprawnoœci nicku
        if (!IsAlphabetic(submissionButtonRef->GetText())) {
            submissionButtonRef->GetText().pop_back();
        }
        if (submissionButtonRef->GetText().length() > 5) {
            submissionButtonRef->GetText().pop_back();
        }
    }

    if (ui->GetInteractionBoxByName("ScoreBoardIcon")->ConsumeStatus()) {
        for (auto& it : ui->GetButtons()) {
            it->Hide();
        }
        for (auto& it : ui->GetInteractionBoxes()) {
            it->Hide();
            it->TurnOff();
        }
        for (auto& it : ui->GetMassageBoxes()) {
            it->Hide();
        }
        SetUpScoreBoard(5);
        
    }

    if (ui->GetInteractionBoxByName("X") != nullptr) {
        if (ui->GetInteractionBoxByName("X")->ConsumeStatus()) {
            for (auto& it : ui->GetButtons()) {
                it->Show();
            }
            for (auto& it : ui->GetInteractionBoxes()) {
                it->Show();
                it->TurnOn();
            }
            for (auto& it : ui->GetMassageBoxes()) {
                it->Show();
            }
            ui->DeleteAnyButton("SCOREBOARD");
            ui->DeleteAnyButton("SCOREBOARDTOP");
            ui->DeleteAnyButton("X");
        }
    }

}

bool SeperateData(std::string line, ScoreBox &scBox) {
    if (line == "") {
        return false;
    }
    int variableIndex = 1;
    
    std::string tempName = "";
    std::string tempScore = "";

    for (int i = 0; i <line.length(); i++){
        if (line[i] != ',') {
            switch (variableIndex) {
                case 1:
                    tempName += line[i];
                    break;
                case 2:
                    tempScore += line[i];
                    break;
            }
        }
        else
        {
            variableIndex++;
        }
    }
    scBox.name = tempName;
    scBox.score = std::stoi(tempScore);
    return true;
    
}

void EndScreen::ScoreBoardInput(SDL_Event& event) {
    if (submissionButtonRef != nullptr) {
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_RETURN) { // Return to enter  
            // Wczytywanie i sortowanie pliku
            int finalScore = SceneManager::GetData<int>("Final Score");
            if (submissionButtonRef->GetText().length() < 6 && submissionButtonRef->GetText().length() > 2) {
                std::ifstream scoreFile(SceneManager::GetData<std::string>("Score File Path"));

                std::string line;
                if (scoreFile.is_open()) {
                    while (std::getline(scoreFile, line)) {
                        ScoreContainer.emplace_back();
                        if (!SeperateData(line, ScoreContainer.back())) {
                            ScoreContainer.pop_back();
                        }
                    }
                    scoreFile.close();
                }
                else
                {
                    std::cerr << "Error missing score file\n";
                }

                std::sort(ScoreContainer.begin(), ScoreContainer.end());

                for (const auto& it : ScoreContainer) {
                    std::cout << "Name: " << it.name << " Score: " << it.score << "\n";
                }

                std::cout << "\n\n";

                ScoreBox playerScore{ submissionButtonRef->GetText(),finalScore };
                // Wprowadzanie wyniku gracza jeœli spe³nia wymogi
                if (ScoreContainer.empty()) {
                    ScoreContainer.push_back(playerScore);
                }
                else{
                    for (int i = 0; i < ScoreContainer.size(); i++) {
                        if (ScoreContainer[i] > playerScore || ScoreContainer.size() < 10) {
                            ScoreContainer.push_back(playerScore);
                            break;
                        }
                    }
                }


                std::sort(ScoreContainer.begin(), ScoreContainer.end());


                for (const auto& it : ScoreContainer) {
                    std::cout << "Name: " << it.name << " Score: " << it.score << "\n";
                }

                //Zapisywanie wyników
                std::ofstream file(SceneManager::GetData<std::string>("Score File Path"));
                if (file.is_open()) {
                    for (const auto& it : ScoreContainer) {
                        file <<it.name<<','<<it.score<<'\n';
                    }
                }
                else
                {
                    std::cerr << "Error score file not saved\n";
                }

                //Czyszczenie i usuwanie przycisku
                ui->DeleteMassageBox("SubmissionButton");
                submissionButtonRef = nullptr;
                scoreButtonRef->Show();
                scoreButtonRef->TurnOn();
                scoreButtonRef = nullptr;
                ScoreContainer.clear();
            }
        }
    }
}

void EndScreen::SetUpScoreBoard(int entries) {
    // Atrybuty przycisków
    SDL_Rect rect{ 0,0,Global::windowWidth,Global::windowHeight };
    Point p = GetRectangleCenter(rect);
    int w = 400;
    int h = (100 * entries);
    ui->CreateButton("SCOREBOARD", p.x - (w / 2), 130, w, h, nullptr, ui->GetFont("arial40px"), "test",
        1.0f,20);
    ui->GetButtonByName("SCOREBOARD")->SetBorder(true);
    ui->GetButtonByName("SCOREBOARD")->SetBorderThickness(8);
    ui->GetButtonByName("SCOREBOARD")->SetBorderRGB(255, 168, 0);
    ui->GetButtonByName("SCOREBOARD")->SetFontColor(255, 168, 0);


    ui->CreateButton("SCOREBOARDTOP", p.x - (w / 2), 50, w, 80, nullptr, ui->GetFont("arial40px"), "SCOREBOARD ",
        1.0f, 12, 12);

    ui->GetButtonByName("SCOREBOARDTOP")->SetBorder(true);
    ui->GetButtonByName("SCOREBOARDTOP")->SetBorderThickness(8);
    ui->GetButtonByName("SCOREBOARDTOP")->SetBorderRGB(255, 168, 0);
    ui->GetButtonByName("SCOREBOARDTOP")->SetFontColor(255, 168, 0);
    ui->GetButtonByName("SCOREBOARDTOP")->SetRenderTextType(2);


    int xCord = ui->GetButtonByName("SCOREBOARD")->GetRectangle()->x +
        ui->GetButtonByName("SCOREBOARD")->GetRectangle()->w;
    int yCord = ui->GetButtonByName("SCOREBOARD")->GetRectangle()->y;

    ui->CreateInteractionBox("X", xCord, yCord, 50, 50, nullptr, ui->GetFont("arial40px"), "X",
        1.0f, 0, 5);

    ui->GetInteractionBoxByName("X")->SetBorder(true);
    ui->GetInteractionBoxByName("X")->SetBorderThickness(2);
    ui->GetInteractionBoxByName("X")->SetBorderRGB(255, 168, 0);
    ui->GetInteractionBoxByName("X")->SetFontColor(255, 168, 0);
    ui->GetInteractionBoxByName("X")->SetRenderTextType(2);
    ui->GetInteractionBoxByName("X")->SetHoverFilter(true, 255, 255, 255, 150);



    //Wczytywanie danych do tekstu
    std::ifstream scoreFile(SceneManager::GetData<std::string>("Score File Path"));

    std::string line;
    if (scoreFile.is_open()) {
        while (std::getline(scoreFile, line)) {
            ScoreContainer.emplace_back();
            if (!SeperateData(line, ScoreContainer.back())) {
                ScoreContainer.pop_back();
            }
        }
        scoreFile.close();
    }
    else
    {
        std::cerr << "Error missing score file\n";
    }

    // Tworzenie stringa

    std::string scoreBoardText = "\n";

    for (size_t i = 0; i < ScoreContainer.size(); i++){
        if (i > entries - 1) {
            break;
        }
        scoreBoardText += ScoreContainer[i].name + " :" + 
            std::to_string(ScoreContainer[i].score) + "\n\n";
    }
    ui->GetButtonByName("SCOREBOARD")->SetText(scoreBoardText);

    ScoreContainer.clear();
}

void EndScreen::Render() {}

void EndScreen::ManageDrunkBox() {
    if (ui->GetInteractionBoxByName("DrunkBox")->ConsumeStatus()) {
        if (SceneManager::GetData<bool>("UsesGoogles")) { //zielony jak nie u¿ywa czyli jak false a czerwony jak true czyli u¿ywa
            SceneManager::GetData<bool>("UsesGoogles") = false;
            ui->SetUIElementColor("DrunkBox", 0, 255, 0);
        }
        else {
            SceneManager::GetData<bool>("UsesGoogles") = true;
            ui->SetUIElementColor("DrunkBox", 255, 0, 0);
        }
    }
}

void EndScreen::Clear() {
    ui->ClearAllButtons();
};