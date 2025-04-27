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
        TexMan::GetTex("MenuIcon"), ui->GetFont("arial20px"),
        "", 0, 0, 0, 5);
    ui->SetElementBorderColor("MainMenuIcon", 135, 206, 250);

    ui->CreateClickBox("ScoreBoardIcon", vec1[1].x, vec1[1].y, vec1[1].w, vec1[1].h,
        TexMan::GetTex("ScoreIcon"), ui->GetFont("arial20px"),
        "", 0, 0, 0, 5);
    ui->SetElementBorderColor("ScoreBoardIcon", 135, 206, 250);

    ui->CreateButton("RetryIcon", vec1[2].x, vec1[2].y, vec1[2].w, vec1[2].h,
        TexMan::GetTex("RetryIcon"), ui->GetFont("arial20px"),
        "", 0, 0, 0, 5);
    ui->SetElementBorderColor("RetryIcon", 135, 206, 250);




    ScaleRectanglesToScreen(vec1, 3, 625, 200, 100, 250);
    ui->CreateClickBox("MainMenuButton", vec1[0].x, vec1[0].y, vec1[0].w, vec1[0].h,
        TexMan::GetTex("buttonModern"), ui->GetFont("arial20px"),
        "      Main Menu", 1, 8, 40, 5);
    ui->SetElementBorderColor("MainMenuButton", 135, 206, 250);
    ui->SetElementFontColor("MainMenuButton", 255, 168, 0);

    ui->CreateClickBox("ScoreBoardButton", vec1[1].x, vec1[1].y, vec1[1].w, vec1[1].h,
        TexMan::GetTex("buttonModern"), ui->GetFont("arial20px"),
        "      Submit", 1, 8, 40, 5);
    ui->SetElementBorderColor("ScoreBoardButton", 135, 206, 250);
    ui->SetElementFontColor("ScoreBoardButton", 255, 168, 0);

    ui->CreateClickBox("RetryButton", vec1[2].x, vec1[2].y, vec1[2].w, vec1[2].h,
        TexMan::GetTex("buttonModern"), ui->GetFont("arial20px"),
        "         Retry", 1, 8, 40, 5);
    ui->SetElementBorderColor("RetryButton", 135, 206, 250);
    ui->SetElementFontColor("RetryButton", 255, 168, 0);

    ui->CreateClickBox("DrunkBox", Global::windowWidth - 100, Global::windowHeight - 200, 100, 100,
        nullptr, ui->GetFont("arial20px"), "", 1, 8, 12, 5);

    for (auto& it : ui->GetClickBoxes()) {
        it->SetHoverFilter(true, 255, 255, 255, 150, "hoverSound");
        it->SetClickSound("click");
    }

    if (SceneMan::GetData<bool>("UsesGoogles")) {
        ui->SetElementColor("DrunkBox", 255, 0, 0);
    }
    else {
        ui->SetElementColor("DrunkBox", 0, 255, 0);
    }
}

void EndScreen::LogicUpdate(){}
void EndScreen::FrameUpdate(){
    ManageScoreBoard();
    ManageDrunkBox();
}

void EndScreen::Input(SDL_Event& event) {
    if (ui->GetClickBox("MainMenuButton")->ConsumeStatus()) {
        SceneMan::GetData<int>("Game State") = 0;
        SceneMan::GetData<int>("Current Game") = 0;
        SceneMan::SwitchResetScene("Main Menu", renderer, ui);
        return;
    }
    int currentGame = SceneMan::GetData<int>("Current Game");
    switch (currentGame) {
        case 1:
            if (ui->GetClickBox("RetryButton")->ConsumeStatus()) {
                SceneMan::GetData<int>("Game State") = 1;
                SceneMan::GetData<int>("Current Game") = 1;
                SceneMan::SwitchResetScene("MiniGameOne", renderer, ui);
                return;
            }
            break;
        case 2:
            if (ui->GetClickBox("RetryButton")->ConsumeStatus()) {
                SceneMan::GetData<int>("Game State") = 1;
                SceneMan::GetData<int>("Current Game") = 2;
                SceneMan::SwitchResetScene("MiniGameTwo", renderer, ui);
                return;
            }
            break;
        case 3:
            if (ui->GetClickBox("RetryButton")->ConsumeStatus()) {
                SceneMan::GetData<int>("Game State") = 1;
                SceneMan::GetData<int>("Current Game") = 3;
                SceneMan::SwitchResetScene("MiniGameThree", renderer, ui);
                return;
            }
            break;
        case 4:
            if (ui->GetClickBox("RetryButton")->ConsumeStatus()) {
                SceneMan::GetData<int>("Game State") = 1;
                SceneMan::GetData<int>("Current Game") = 4;
                SceneMan::SwitchResetScene("MiniGameFour", renderer, ui);
                return;
            }
            break;

        case 5:
            if (ui->GetClickBox("RetryButton")->ConsumeStatus()) {
                SceneMan::GetData<int>("Game State") = 1;
                SceneMan::GetData<int>("Current Game") = 5;
                SceneMan::SwitchResetScene("MiniGameFive", renderer, ui);
                return;
            }

        case 6:
            if (ui->GetClickBox("RetryButton")->ConsumeStatus()) {
                SceneMan::GetData<int>("Game State") = 1;
                SceneMan::GetData<int>("Current Game") = 6;
                SceneMan::SwitchResetScene("MiniGameSix", renderer, ui);
                return;
            }

            break;
    }
    ScoreBoardInput(event);
}

void EndScreen::ManageScoreBoard() {
    if (ui->GetClickBox("ScoreBoardButton")->ConsumeStatus()) { // Sprawdzanie czy trzeba utworzyæ submission button
        if (submissionButtonRef == nullptr) {

            scoreButtonRef = ui->GetClickBox("ScoreBoardButton");
            ui->GetClickBox("ScoreBoardButton")->TurnOff();
            ui->GetClickBox("ScoreBoardButton")->Hide();
            ui->CreateTextBox("SubmissionButton", scoreButtonRef->GetRectangle()->x, scoreButtonRef->GetRectangle()->y,
                scoreButtonRef->GetRectangle()->w, scoreButtonRef->GetRectangle()->h, nullptr, ui->GetFont("arial40px"), "", 1.0f, 0, 0, 5);


            submissionButtonRef = ui->GetTextBox("SubmissionButton");
            ui->SetElementColor("SubmissionButton", 255, 255, 255);
            ui->SetElementBorderColor("SubmissionButton", 135, 206, 250);
            ui->SetElementFontColor("SubmissionButton", 255, 168, 0);
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

    if (ui->GetClickBox("ScoreBoardIcon")->ConsumeStatus()) {
        for (auto& it : ui->GetButtons()) {
            it->Hide();
        }
        for (auto& it : ui->GetClickBoxes()) {
            it->Hide();
            it->TurnOff();
        }
        for (auto& it : ui->GetTextBoxes()) {
            it->Hide();
        }
        SetUpScoreBoard(5);
        
    }

    if (ui->GetClickBox("X") != nullptr) {
        if (ui->GetClickBox("X")->ConsumeStatus()) {
            for (auto& it : ui->GetButtons()) {
                it->Show();
            }
            for (auto& it : ui->GetClickBoxes()) {
                it->Show();
                it->TurnOn();
            }
            for (auto& it : ui->GetTextBoxes()) {
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
            int finalScore = SceneMan::GetData<int>("Final Score");
            if (submissionButtonRef->GetText().length() < 6 && submissionButtonRef->GetText().length() > 2) {
                std::ifstream scoreFile(SceneMan::GetData<std::string>("Score File Path"));

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
                std::ofstream file(SceneMan::GetData<std::string>("Score File Path"));
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
                ui->DeleteTextBox("SubmissionButton");
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
    ui->GetButton("SCOREBOARD")->SetBorder(8, 255, 168, 0);
    ui->GetButton("SCOREBOARD")->SetFontColor(255, 168, 0);


    ui->CreateButton("SCOREBOARDTOP", p.x - (w / 2), 50, w, 80, nullptr, ui->GetFont("arial40px"), "SCOREBOARD ",
        1.0f, 12, 12);

    ui->GetButton("SCOREBOARDTOP")->SetBorder(8, 255, 168, 0);
    ui->GetButton("SCOREBOARDTOP")->SetFontColor(255, 168, 0);
    ui->GetButton("SCOREBOARDTOP")->SetRenderTextType(2);


    int xCord = ui->GetButton("SCOREBOARD")->GetRectangle()->x +
        ui->GetButton("SCOREBOARD")->GetRectangle()->w;
    int yCord = ui->GetButton("SCOREBOARD")->GetRectangle()->y;

    ui->CreateClickBox("X", xCord, yCord, 50, 50, nullptr, ui->GetFont("arial40px"), "X",
        1.0f, 0, 5);

    ui->GetClickBox("X")->SetBorder(2, 255, 168, 0);
    ui->GetClickBox("X")->SetFontColor(255, 168, 0);
    ui->GetClickBox("X")->SetRenderTextType(2);
    ui->GetClickBox("X")->SetHoverFilter(true, 255, 255, 255, 150);



    //Wczytywanie danych do tekstu
    std::ifstream scoreFile(SceneMan::GetData<std::string>("Score File Path"));

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
    ui->GetButton("SCOREBOARD")->SetText(scoreBoardText);

    ScoreContainer.clear();
}

void EndScreen::Render() {}

void EndScreen::ManageDrunkBox() {
    if (ui->GetClickBox("DrunkBox")->ConsumeStatus()) {
        if (SceneMan::GetData<bool>("UsesGoogles")) { //zielony jak nie u¿ywa czyli jak false a czerwony jak true czyli u¿ywa
            SceneMan::GetData<bool>("UsesGoogles") = false;
            ui->SetElementColor("DrunkBox", 0, 255, 0);
        }
        else {
            SceneMan::GetData<bool>("UsesGoogles") = true;
            ui->SetElementColor("DrunkBox", 255, 0, 0);
        }
    }
}

void EndScreen::Clear() {
    ui->ClearAllButtons();
};