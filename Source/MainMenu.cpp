#include "MainMenu.h"
#include "GlobalVariables.h"
#include "Addons.h"
#include <any>

void MainMenu::Init(SDL_Renderer* renderer, UI* ui) {
    this->renderer = renderer;

    this->ui = ui;

    std::vector<SDL_Rect> vec1;
    ScaleRectanglesToScreen(vec1, 1, 0, Global::windowWidth * 0.5, 150, 0);


    ui->CreateButton("MenuInfo", vec1[0].x, vec1[0].y, vec1[0].w, vec1[0].h,
        nullptr, ui->GetFont("arial40px"),
        "Choose Game", 1, 0, 0, 5);
    ui->SetElementBorderColor("MenuInfo", 135, 206, 250);
    ui->SetElementFontColor("MenuInfo", 255, 168, 0);
    ui->GetButton("MenuInfo")->SetRenderTextType(2);

    ScaleRectanglesToScreen(vec1, 3, 300, 200, 200, 200);

    ui->CreateButton("GameTab1", vec1[0].x, vec1[0].y, vec1[0].w, vec1[0].h,
        TexMan::GetTex("GameIcon1"), ui->GetFont("arial20px"),
        "", 1, 3, 40, 5);
    ui->SetElementBorderColor("GameTab1", 135, 206, 250);

    ui->CreateButton("GameTab2", vec1[1].x, vec1[1].y, vec1[1].w, vec1[1].h,
        TexMan::GetTex("GameIcon2"), ui->GetFont("arial20px"),
        "", 20, 3, 40, 5);
    ui->SetElementBorderColor("GameTab2", 135, 206, 250);

    ui->CreateButton("GameTab3", vec1[2].x, vec1[2].y, vec1[2].w, vec1[2].h,
        TexMan::GetTex("GameIcon3"), ui->GetFont("arial20px"),
        "", 20, 3, 40, 5);
    ui->SetElementBorderColor("GameTab3", 135, 206, 250);


    ScaleRectanglesToScreen(vec1, 3, 525, 200, 50, 200);

    ui->CreateClickBox("GameSubTab1", vec1[0].x, vec1[0].y, vec1[0].w, vec1[0].h,
        TexMan::GetTex("buttonModern"), ui->GetFont("arial20px"),
        "Precission Test", 1, 8, 12, 5);
    ui->SetElementBorderColor("GameSubTab1", 135, 206, 250);
    ui->SetElementFontColor("GameSubTab1", 255, 168, 0);


    ui->CreateClickBox("GameSubTab2", vec1[1].x, vec1[1].y, vec1[1].w, vec1[1].h,
        TexMan::GetTex("buttonModern"), ui->GetFont("arial20px"),
        "Reaction Test", 1, 8, 12, 5);
    ui->SetElementBorderColor("GameSubTab2", 135, 206, 250);
    ui->SetElementFontColor("GameSubTab2", 255, 168, 0);


    ui->CreateClickBox("GameSubTab3", vec1[2].x, vec1[2].y, vec1[2].w, vec1[2].h,
        TexMan::GetTex("buttonModern"), ui->GetFont("arial20px"),
        "Concentration Test", 1, 8, 12, 5);
    ui->SetElementBorderColor("GameSubTab3", 135, 206, 250);
    ui->SetElementFontColor("GameSubTab3", 255, 168, 0);



    ScaleRectanglesToScreen(vec1, 3, 725, 200, 200, 200);

    ui->CreateButton("GameTab4", vec1[0].x, vec1[0].y, vec1[0].w, vec1[0].h,
        TexMan::GetTex("GameIcon4"), ui->GetFont("arial20px"),
        "", 20, 3, 40, 5);
    ui->SetElementBorderColor("GameTab4", 135, 206, 250);
    ui->SetElementFontColor("GameTab4", 255, 168, 0);

    ui->CreateButton("GameTab5", vec1[1].x, vec1[1].y, vec1[1].w, vec1[1].h,
        TexMan::GetTex("GameIcon5"), ui->GetFont("arial20px"),
        "", 1, 8, 12, 5);
    ui->SetElementBorderColor("GameTab5", 135, 206, 250);
    ui->SetElementFontColor("GameTab5", 255, 168, 0);

    ui->CreateButton("GameTab6", vec1[2].x, vec1[2].y, vec1[2].w, vec1[2].h,
        TexMan::GetTex("GameIcon6"), ui->GetFont("arial20px"),
        "", 1, 8, 12, 5);
    ui->SetElementBorderColor("GameTab6", 135, 206, 250);
    ui->SetElementFontColor("GameTab6", 255, 168, 0);


    ScaleRectanglesToScreen(vec1, 3, 950, 200, 50, 200);
    ui->CreateClickBox("GameSubTab4", vec1[0].x, vec1[0].y, vec1[0].w, vec1[0].h,
        TexMan::GetTex("buttonModern"), ui->GetFont("arial20px"),
        "Vision Test", 1, 8, 12, 5);
    ui->SetElementBorderColor("GameSubTab4", 135, 206, 250);
    ui->SetElementFontColor("GameSubTab4", 255, 168, 0);

    ui->CreateClickBox("GameSubTab5", vec1[1].x, vec1[1].y, vec1[1].w, vec1[1].h,
        TexMan::GetTex("buttonModern"), ui->GetFont("arial20px"),
        "Memory Test", 1, 8, 12, 5);
    ui->SetElementBorderColor("GameSubTab5", 135, 206, 250);
    ui->SetElementFontColor("GameSubTab5", 255, 168, 0);



    ui->CreateClickBox("GameSubTab6", vec1[2].x, vec1[2].y, vec1[2].w, vec1[2].h,
        TexMan::GetTex("buttonModern"), ui->GetFont("arial20px"),
        "Stres Test", 1, 8, 12, 5);
    ui->SetElementBorderColor("GameSubTab6", 135, 206, 250);
    ui->SetElementFontColor("GameSubTab6", 255, 168, 0);

    ui->CreateClickBox("Exit", Global::windowWidth - 100, 0, 100, 100,
        TexMan::GetTex("buttonModern"), ui->GetFont("arial20px"),
        "Exit", 1, 8, 12, 5);
    ui->SetElementBorderColor("Exit", 135, 206, 250);
    ui->SetElementFontColor("Exit", 255, 168, 0);

    ui->CreateTextBox("PlayerNameBox", Global::windowWidth - 100, Global::windowHeight - 100, 100, 100,
        TexMan::GetTex("buttonModern"), ui->GetFont("arial20px"), "", 1, 8, 12, 5);

    ui->CreateClickBox("DrunkBox", Global::windowWidth - 100, Global::windowHeight - 200, 100, 100,
        nullptr, ui->GetFont("arial20px"), "", 1, 8, 12, 5);





    for (auto& it : ui->GetClickBoxes()) {
        it->SetHoverFilter(true, 255, 255, 255, 150,"hoverSound");
        it->SetClickSound("click");
    }

    if (SceneMan::IsData("UsesGoogles")) {
        if (SceneMan::GetData<bool>("UsesGoogles")) { 
            ui->SetElementColor("DrunkBox", 255, 0, 0);
        }
        else {
            ui->SetElementColor("DrunkBox", 0, 255, 0);
        }
    }
    else{ // jak pierwszy raz siê gra odpala (czyli nie ma jeszcze info) to jest zielone
        ui->SetElementColor("DrunkBox", 0, 255, 0);
    }

}


void MainMenu::LogicUpdate() {

}

void MainMenu::FrameUpdate() {

}

void MainMenu::Input(SDL_Event& event) {
    ManagePlayerName(event);
    ManageDrunkBox();

    if (ui->GetClickBox("GameSubTab1")->ConsumeStatus()) {
        SceneMan::GetData<int>("Game State") = 1;
        SceneMan::GetData<int>("Current Game") = 1;
        SceneMan::SwitchResetScene("MiniGameOne", renderer, ui);
    }
    else if (ui->GetClickBox("GameSubTab2")->ConsumeStatus()) {
        SceneMan::GetData<int>("Game State") = 1;
        SceneMan::GetData<int>("Current Game") = 2;
        SceneMan::SwitchResetScene("MiniGameTwo", renderer, ui);
    }
    else if (ui->GetClickBox("GameSubTab3")->ConsumeStatus()) {
        SceneMan::GetData<int>("Game State") = 1;
        SceneMan::GetData<int>("Current Game") = 3;
        SceneMan::SwitchResetScene("MiniGameThree", renderer, ui);
    }
    else if (ui->GetClickBox("GameSubTab4")->ConsumeStatus()) {
        SceneMan::GetData<int>("Game State") = 1;
        SceneMan::GetData<int>("Current Game") = 4;
        SceneMan::SwitchResetScene("MiniGameFour", renderer, ui);
    }
    else if (ui->GetClickBox("GameSubTab5")->ConsumeStatus()) {
        SceneMan::GetData<int>("Game State") = 1;
        SceneMan::GetData<int>("Current Game") = 5;
        SceneMan::SwitchResetScene("MiniGameFive", renderer, ui);
    }

    else if (ui->GetClickBox("GameSubTab6")->ConsumeStatus()) {
        SceneMan::GetData<int>("Game State") = 1;
        SceneMan::GetData<int>("Current Game") = 6;
        SceneMan::SwitchResetScene("MiniGameSix", renderer, ui);
    }

    else if (ui->GetClickBox("Exit")->ConsumeStatus()) {
        Global::status = false;
    }
}

void MainMenu::Render() {

}

void MainMenu::Clear() {
    ui->ClearAllButtons();
}


void MainMenu::ManagePlayerName(SDL_Event &event) {
    if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_RETURN) { 
        ui->GetTextBox("PlayerNameBox")->GetText().pop_back(); // bo jest \n na koñcu
        std::string playerName = ui->GetTextBox("PlayerNameBox")->GetText();
        ui->GetTextBox("PlayerNameBox")->GetText().clear();
        SceneMan::GetData<std::string>("PlayerName") = playerName;
    }
}


void MainMenu::ManageDrunkBox() {
    if (ui->GetClickBox("DrunkBox")->ConsumeStatus()) {
        if (SceneMan::GetData<bool>("UsesGoogles")) { //zielony jak nie u¿ywa czyli jak false a czerwony jak true czyli u¿ywa
            SceneMan::GetData<bool>("UsesGoogles") = false;
            ui->SetElementColor("DrunkBox", 0, 255, 0);
        }
        else{
            SceneMan::GetData<bool>("UsesGoogles") = true;
            ui->SetElementColor("DrunkBox", 255, 0, 0);
        }
    }
}