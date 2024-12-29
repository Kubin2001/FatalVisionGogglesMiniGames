#include "MainMenu.h"
#include "GlobalVariables.h"

void MainMenu::Innit(UI *ui) {
    ui->CreateButton("MenuInfo", 300, 0, Global::windowWidth * 0.5, 150,
        nullptr, ui->GetFont("arial40px"),
        "                Choose a test", 1, 3, 40, 5);
    ui->SetUIElementBorderColor("MenuInfo", 135, 206, 250);
    ui->SetUIElementFontColor("MenuInfo", 255, 168, 0);

    ui->CreateButton("GameTab1", 150, 200, 200, 200,
        TextureManager::GetTextureByName("GameIcon1"), ui->GetFont("arial20px"),
        "", 1, 3, 40, 5);
    ui->SetUIElementBorderColor("GameTab1", 135, 206, 250);

    ui->CreateInteractionBox("GameSubTab1", 150, 410, 200, 50,
        TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial20px"),
        "Precission Test", 1, 8, 12, 5);
    ui->SetUIElementBorderColor("GameSubTab1", 135, 206, 250);
    ui->SetUIElementFontColor("GameSubTab1", 255, 168, 0);

    ui->CreateButton("GameTab2", 450, 200, 200, 200,
        TextureManager::GetTextureByName("GameIcon2"), ui->GetFont("arial20px"),
        "",20, 3, 40, 5);
    ui->SetUIElementBorderColor("GameTab2", 135, 206, 250);

    ui->CreateInteractionBox("GameSubTab2", 450, 410, 200, 50,
        TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial20px"),
        "Reaction Test", 1, 8, 12, 5);
    ui->SetUIElementBorderColor("GameSubTab2", 135, 206, 250);
    ui->SetUIElementFontColor("GameSubTab2", 255, 168, 0);

    ui->CreateButton("GameTab3", 750, 200, 200, 200,
        TextureManager::GetTextureByName("GameIcon3"), ui->GetFont("arial20px"),
        "", 20, 3, 40, 5);
    ui->SetUIElementBorderColor("GameTab3", 135, 206, 250);

    ui->CreateInteractionBox("GameSubTab3", 750, 410, 200, 50,
        TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial20px"),
        "Concentration Test", 1, 8, 12, 5);
    ui->SetUIElementBorderColor("GameSubTab3", 135, 206, 250);
    ui->SetUIElementFontColor("GameSubTab3", 255, 168, 0);

    ui->CreateButton("GameTab4", 1050, 200, 200, 200,
        TextureManager::GetTextureByName("GameIcon4"), ui->GetFont("arial20px"),
        "", 20, 3, 40, 5);
    ui->SetUIElementBorderColor("GameTab4", 135, 206, 250);
    ui->SetUIElementFontColor("GameTab4", 255, 168, 0);

    ui->CreateInteractionBox("GameSubTab4", 1050, 410, 200, 50,
        TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial20px"),
        "Vision Test", 1, 8, 12, 5);
    ui->SetUIElementBorderColor("GameSubTab4", 135, 206, 250);
    ui->SetUIElementFontColor("GameSubTab4", 255, 168, 0);

    ui->CreateButton("GameTab5", 150, 500, 200, 200,
        TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial20px"),
        "Precision", 1, 8, 12, 5);
    ui->SetUIElementBorderColor("GameTab5", 135, 206, 250);
    ui->SetUIElementFontColor("GameTab5", 255, 168, 0);

    ui->CreateInteractionBox("GameSubTab5", 150, 710, 200, 50,
        TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial20px"),
        "Game5", 1, 8, 12, 5);
    ui->SetUIElementBorderColor("GameSubTab5", 135, 206, 250);
    ui->SetUIElementFontColor("GameSubTab5", 255, 168, 0);

    ui->CreateButton("GameTab6", 450, 500, 200, 200,
        TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial20px"),
        "Precision2", 1, 8, 12, 5);
    ui->SetUIElementBorderColor("GameTab6", 135, 206, 250);
    ui->SetUIElementFontColor("GameTab6", 255, 168, 0);

    ui->CreateInteractionBox("GameSubTab6", 450, 710, 200, 50,
        TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial20px"),
        "Game6", 1, 8, 12, 5);
    ui->SetUIElementBorderColor("GameSubTab6", 135, 206, 250);
    ui->SetUIElementFontColor("GameSubTab6", 255, 168, 0);

    ui->CreateButton("GameTab7", 750, 500, 200, 200,
        TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial20px"),
        "Precision3", 1, 8, 12, 5);
    ui->SetUIElementBorderColor("GameTab7", 135, 206, 250);
    ui->SetUIElementFontColor("GameTab7", 255, 168, 0);

    ui->CreateInteractionBox("GameSubTab7", 750, 710, 200, 50,
        TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial20px"),
        "Game7", 1, 8, 12, 5);
    ui->SetUIElementBorderColor("GameSubTab7", 135, 206, 250);
    ui->SetUIElementFontColor("GameSubTab7", 255, 168, 0);

    ui->CreateButton("GameTab8", 1050, 500, 200, 200,
        TextureManager::GetTextureByName("buttonModern"), ui->GetFont("arial20px"),
        "Precision4", 1, 8, 12, 5);
    ui->SetUIElementBorderColor("GameTab8", 135, 206, 250);
    ui->SetUIElementFontColor("GameTab8", 255, 168, 0);

    ui->CreateInteractionBox("GameSubTab8", 1050, 710, 200, 50,
        TextureManager::GetTextureByName("buttonModern"),
        ui->GetFont("arial20px"), "Game8", 1, 8, 12, 5);
    ui->SetUIElementBorderColor("GameSubTab8", 135, 206, 250);
    ui->SetUIElementFontColor("GameSubTab8", 255, 168, 0);
}

void MainMenu::OnClick(UI* ui) {

}

void MainMenu::Clear(UI* ui) {

}
