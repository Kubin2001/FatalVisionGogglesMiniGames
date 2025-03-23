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
        "                Choose a test", 1, 3, 40, 5);
    ui->SetUIElementBorderColor("MenuInfo", 135, 206, 250);
    ui->SetUIElementFontColor("MenuInfo", 255, 168, 0);

    ScaleRectanglesToScreen(vec1, 3, 300, 200, 200, 200);

    ui->CreateButton("GameTab1", vec1[0].x, vec1[0].y, vec1[0].w, vec1[0].h,
        TextureManager::GetTextureByName("GameIcon1"), ui->GetFont("arial20px"),
        "", 1, 3, 40, 5);
    ui->SetUIElementBorderColor("GameTab1", 135, 206, 250);

    ui->CreateButton("GameTab2", vec1[1].x, vec1[1].y, vec1[1].w, vec1[1].h,
        TextureManager::GetTextureByName("GameIcon2"), ui->GetFont("arial20px"),
        "", 20, 3, 40, 5);
    ui->SetUIElementBorderColor("GameTab2", 135, 206, 250);

    ui->CreateButton("GameTab3", vec1[2].x, vec1[2].y, vec1[2].w, vec1[2].h,
        TextureManager::GetTextureByName("GameIcon3"), ui->GetFont("arial20px"),
        "", 20, 3, 40, 5);
    ui->SetUIElementBorderColor("GameTab3", 135, 206, 250);


    ScaleRectanglesToScreen(vec1, 3, 525, 200, 50, 200);

    ui->CreateInteractionBox("GameSubTab1", vec1[0].x, vec1[0].y, vec1[0].w, vec1[0].h,
        TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial20px"),
        "Precission Test", 1, 8, 12, 5);
    ui->SetUIElementBorderColor("GameSubTab1", 135, 206, 250);
    ui->SetUIElementFontColor("GameSubTab1", 255, 168, 0);


    ui->CreateInteractionBox("GameSubTab2", vec1[1].x, vec1[1].y, vec1[1].w, vec1[1].h,
        TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial20px"),
        "Reaction Test", 1, 8, 12, 5);
    ui->SetUIElementBorderColor("GameSubTab2", 135, 206, 250);
    ui->SetUIElementFontColor("GameSubTab2", 255, 168, 0);


    ui->CreateInteractionBox("GameSubTab3", vec1[2].x, vec1[2].y, vec1[2].w, vec1[2].h,
        TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial20px"),
        "Concentration Test", 1, 8, 12, 5);
    ui->SetUIElementBorderColor("GameSubTab3", 135, 206, 250);
    ui->SetUIElementFontColor("GameSubTab3", 255, 168, 0);



    ScaleRectanglesToScreen(vec1, 3, 725, 200, 200, 200);

    ui->CreateButton("GameTab4", vec1[0].x, vec1[0].y, vec1[0].w, vec1[0].h,
        TextureManager::GetTextureByName("GameIcon4"), ui->GetFont("arial20px"),
        "", 20, 3, 40, 5);
    ui->SetUIElementBorderColor("GameTab4", 135, 206, 250);
    ui->SetUIElementFontColor("GameTab4", 255, 168, 0);

    ui->CreateButton("GameTab5", vec1[1].x, vec1[1].y, vec1[1].w, vec1[1].h,
        TextureManager::GetTextureByName("GameIcon5"), ui->GetFont("arial20px"),
        "", 1, 8, 12, 5);
    ui->SetUIElementBorderColor("GameTab5", 135, 206, 250);
    ui->SetUIElementFontColor("GameTab5", 255, 168, 0);

    ui->CreateButton("GameTab6", vec1[2].x, vec1[2].y, vec1[2].w, vec1[2].h,
        TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial20px"),
        "Precision2", 1, 8, 12, 5);
    ui->SetUIElementBorderColor("GameTab6", 135, 206, 250);
    ui->SetUIElementFontColor("GameTab6", 255, 168, 0);


    ScaleRectanglesToScreen(vec1, 3, 950, 200, 50, 200);
    ui->CreateInteractionBox("GameSubTab4", vec1[0].x, vec1[0].y, vec1[0].w, vec1[0].h,
        TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial20px"),
        "Vision Test", 1, 8, 12, 5);
    ui->SetUIElementBorderColor("GameSubTab4", 135, 206, 250);
    ui->SetUIElementFontColor("GameSubTab4", 255, 168, 0);

    ui->CreateInteractionBox("GameSubTab5", vec1[1].x, vec1[1].y, vec1[1].w, vec1[1].h,
        TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial20px"),
        "Memory Test", 1, 8, 12, 5);
    ui->SetUIElementBorderColor("GameSubTab5", 135, 206, 250);
    ui->SetUIElementFontColor("GameSubTab5", 255, 168, 0);



    ui->CreateInteractionBox("GameSubTab6", vec1[2].x, vec1[2].y, vec1[2].w, vec1[2].h,
        TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial20px"),
        "Game6", 1, 8, 12, 5);
    ui->SetUIElementBorderColor("GameSubTab6", 135, 206, 250);
    ui->SetUIElementFontColor("GameSubTab6", 255, 168, 0);


    for (auto& it : ui->GetInteractionBoxes()) {
        it->SetHoverFilter(true, 255, 255, 255, 150,"hoverSound");
        it->SetClickSound("click");
    }
}


void MainMenu::LogicUpdate() {

}

void MainMenu::FrameUpdate() {

}

void MainMenu::Input(SDL_Event& event) {
    if (ui->GetInteractionBoxByName("GameSubTab1")->ConsumeStatus()) {
        SceneManager::GetData<int>("Game State") = 1;
        SceneManager::GetData<int>("Current Game") = 1;
        SceneManager::SwitchScene("MiniGameOne", renderer, ui);
    }
    else if (ui->GetInteractionBoxByName("GameSubTab2")->ConsumeStatus()) {
        SceneManager::GetData<int>("Game State") = 1;
        SceneManager::GetData<int>("Current Game") = 2;
        SceneManager::SwitchScene("MiniGameTwo", renderer, ui);
    }
    else if (ui->GetInteractionBoxByName("GameSubTab3")->ConsumeStatus()) {
        SceneManager::GetData<int>("Game State") = 1;
        SceneManager::GetData<int>("Current Game") = 3;
        SceneManager::SwitchScene("MiniGameThree", renderer, ui);
    }
    else if (ui->GetInteractionBoxByName("GameSubTab4")->ConsumeStatus()) {
        SceneManager::GetData<int>("Game State") = 1;
        SceneManager::GetData<int>("Current Game") = 4;
        SceneManager::SwitchScene("MiniGameFour", renderer, ui);
    }
    else if (ui->GetInteractionBoxByName("GameSubTab5")->ConsumeStatus()) {
        SceneManager::GetData<int>("Game State") = 1;
        SceneManager::GetData<int>("Current Game") = 5;
        SceneManager::SwitchScene("MiniGameFive", renderer, ui);
    }
}

void MainMenu::Render() {

}

void MainMenu::Clear() {
    ui->ClearAllButtons();
}
