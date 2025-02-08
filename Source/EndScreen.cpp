#include "EndScreen.h"
#include "GlobalVariables.h"
#include <cctype>
#include <fstream>
#include <string>

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
}

void EndScreen::LogicUpdate(){}
void EndScreen::FrameUpdate(){
    ManageScoreBoard();
}

void EndScreen::Input(SDL_Event& event) {
    if (ui->GetInteractionBoxByName("MainMenuButton")->ConsumeStatus()) {
        SceneManager::GetData("Game State") = 0;
        SceneManager::GetData("Current Game") = 0;
        SceneManager::SwitchScene("Main Menu", renderer, ui);
        return;
    }
    int currentGame = std::any_cast<int>(SceneManager::GetData("Current Game"));
    switch (currentGame) {
        case 1:
            if (ui->GetInteractionBoxByName("RetryButton")->ConsumeStatus()) {
                SceneManager::GetData("Game State") = 1;
                SceneManager::GetData("Current Game") = 1;
                SceneManager::SwitchScene("MiniGameOne", renderer, ui);
                return;
            }
            break;
        case 2:
            if (ui->GetInteractionBoxByName("RetryButton")->ConsumeStatus()) {
                SceneManager::GetData("Game State") = 1;
                SceneManager::GetData("Current Game") = 2;
                SceneManager::SwitchScene("MiniGameTwo", renderer, ui);
                return;
            }
            break;
        case 3:
            if (ui->GetInteractionBoxByName("RetryButton")->ConsumeStatus()) {
                SceneManager::GetData("Game State") = 1;
                SceneManager::GetData("Current Game") = 3;
                SceneManager::SwitchScene("MiniGameThree", renderer, ui);
                return;
            }
            break;
        case 4:
            if (ui->GetInteractionBoxByName("RetryButton")->ConsumeStatus()) {
                SceneManager::GetData("Game State") = 1;
                SceneManager::GetData("Current Game") = 4;
                SceneManager::SwitchScene("MiniGameFour", renderer, ui);
                return;
            }
            break;

        case 5:
            if (ui->GetInteractionBoxByName("RetryButton")->ConsumeStatus()) {
                SceneManager::GetData("Game State") = 1;
                SceneManager::GetData("Current Game") = 5;
                SceneManager::SwitchScene("MiniGameFive", renderer, ui);
                return;
            }

            break;
    }
    ScoreBoardInput(event);
}

void EndScreen::ManageScoreBoard() {
    if (ui->GetInteractionBoxByName("ScoreBoardButton")->ConsumeStatus()) {
        if (submissionButtonRef == nullptr) {

            scoreButtonRef = ui->GetInteractionBoxByName("ScoreBoardButton");
            ui->CreateMassageBox("SubmissionButton", scoreButtonRef->GetRectangle()->x, scoreButtonRef->GetRectangle()->y,
                scoreButtonRef->GetRectangle()->w, scoreButtonRef->GetRectangle()->h, nullptr, ui->GetFont("arial40px"), "", 1.0f, 0, 0, 5);

            scoreButtonRef->TurnOff();
            SDL_Rect rect{ 0,0,0,0 }; // Schowanie przycisku
            *scoreButtonRef->GetRectangle() = rect;
            scoreButtonRef->SetText("");
            scoreButtonRef->SetBorderThickness(0);


            submissionButtonRef = ui->GetMassageBoxByName("SubmissionButton");
            ui->SetUIElementColor("SubmissionButton", 255, 255, 255);
            ui->SetUIElementBorderColor("SubmissionButton", 135, 206, 250);
            ui->SetUIElementFontColor("SubmissionButton", 255, 168, 0);
            submissionButtonRef->SetRenderTextType(2);

        }
    }
    if (submissionButtonRef != nullptr) {
        if (!IsAlphabetic(submissionButtonRef->GetText())) {
            submissionButtonRef->GetText().pop_back();
        }
        if (submissionButtonRef->GetText().length() > 5) {
            submissionButtonRef->GetText().pop_back();
        }
    }

}

void EndScreen::ScoreBoardInput(SDL_Event& event) {
    if (submissionButtonRef != nullptr) {
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_RETURN) {
            int finalScore = ui->GetButtonByName("MainMenuIcon")->GetInterLine(); // G³upie ale dzia³a XD
            if (submissionButtonRef->GetText().length() < 6 && submissionButtonRef->GetText().length() > 2) {
                std::ifstream namesFile("Data/gameOneNames.txt");
                std::ifstream scoreFile("Data/gameOneScores.txt");

                std::vector<std::string> namesVector;
                std::vector<int> scoresVector;

                std::string namesFileLine;
                std::string scoreFileLine;

                int counter = 0;
                while (std::getline(namesFile, namesFileLine)) {
                    if (counter > 19) {
                        break;
                    }
                    namesVector.emplace_back(namesFileLine);
                    counter++;
                }

                counter = 0;
                while (std::getline(scoreFile, scoreFileLine)) {
                    if (counter > 19) {
                        break;
                    }
                    scoresVector.emplace_back(std::stoi(scoreFileLine));
                    counter++;
                }

                if (!namesVector.empty()) {
                    for (const auto& it : namesVector) {
                        std::cout << it << "\n";
                    }
                    std::cout << "\n";
                    for (const auto& it : scoresVector) {
                        std::cout << it << "\n";
                    }


                    int insertIndex = -1;
                    if (scoresVector.size() < 20) {
                        scoresVector.emplace_back(finalScore);
                        namesVector.emplace_back(submissionButtonRef->GetText());
                    }
                    else
                    {
                        for (size_t i = 0; i < scoresVector.size(); i++) {
                            if (finalScore > scoresVector[i]) {
                                scoresVector.insert(scoresVector.begin() + i, finalScore);
                                insertIndex = i;
                                break;
                            }
                        }
                        if (insertIndex != -1) {
                            namesVector.insert(namesVector.begin() + insertIndex, submissionButtonRef->GetText());
                        }
                    }

                }
                else
                {
                    scoresVector.emplace_back(finalScore);
                    namesVector.emplace_back(submissionButtonRef->GetText());
                }
                namesFile.close();
                scoreFile.close();

                if (!namesVector.empty()) {
                    std::ofstream namesOutFile("Data/gameOneNames.txt");
                    std::ofstream scoresOutFile("Data/gameOneScores.txt");

                    if (namesOutFile.is_open() && scoresOutFile.is_open()) {
                        for (const auto& name : namesVector) {
                            namesOutFile << name << "\n";
                        }

                        for (const auto& score : scoresVector) {
                            scoresOutFile << score << "\n";
                        }

                        namesOutFile.close();
                        scoresOutFile.close();
                    }
                    else {
                        std::cerr << "Error: Unable to open files for writing.\n";
                    }
                }
            }

        }
    }
}

void EndScreen::Render() {}
void EndScreen::Clear() {
    ui->ClearAllButtons();
};