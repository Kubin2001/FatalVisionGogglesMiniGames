#include "MainMenu.h"
#include "GlobalVariables.h"

void MainMenu::Innit(UI *ui) {
    ui->CreateButton("MenuInfo", 300, 0, Global::windowWidth * 0.5, 150,
        nullptr, "Choose a test", 40, 35, 3, 40, 5);
    ui->SetUIElementColor("MenuInfo", 30, 30, 30);
    ui->SetUIElementBorderColor("MenuInfo", 135, 206, 250);

    ui->CreateButton("GameTab1", 150, 200, 200, 200,
        TextureManager::GetTextureByName("GameIcon1"), "", 20, 18, 3, 40, 5);
    ui->SetUIElementBorderColor("GameTab1", 135, 206, 250);

    ui->CreateInteractionBox("GameSubTab1", 150, 410, 200, 50,
        TextureManager::GetTextureByName("buttonModern"), "Precission Test", 15, 13, 0, 10, 5);
    ui->SetUIElementBorderColor("GameSubTab1", 135, 206, 250);

    ui->CreateButton("GameTab2", 450, 200, 200, 200,
        TextureManager::GetTextureByName("buttonModern"), "Precision2", 20, 18, 3, 40, 5);
    ui->SetUIElementBorderColor("GameTab2", 135, 206, 250);

    ui->CreateInteractionBox("GameSubTab2", 450, 410, 200, 50,
        TextureManager::GetTextureByName("buttonModern"), "Game2", 20, 18, 2, 10, 5);
    ui->SetUIElementBorderColor("GameSubTab2", 135, 206, 250);

    ui->CreateButton("GameTab3", 750, 200, 200, 200,
        TextureManager::GetTextureByName("buttonModern"), "Precision3", 20, 18, 3, 40, 5);
    ui->SetUIElementBorderColor("GameTab3", 135, 206, 250);

    ui->CreateInteractionBox("GameSubTab3", 750, 410, 200, 50,
        TextureManager::GetTextureByName("buttonModern"), "Game3", 20, 18, 2, 10, 5);
    ui->SetUIElementBorderColor("GameSubTab3", 135, 206, 250);

    ui->CreateButton("GameTab4", 1050, 200, 200, 200,
        TextureManager::GetTextureByName("buttonModern"), "Precision4", 20, 18, 3, 40, 5);
    ui->SetUIElementBorderColor("GameTab4", 135, 206, 250);

    ui->CreateInteractionBox("GameSubTab4", 1050, 410, 200, 50,
        TextureManager::GetTextureByName("buttonModern"), "Game4", 20, 18, 2, 10, 5);
    ui->SetUIElementBorderColor("GameSubTab4", 135, 206, 250);

    ui->CreateButton("GameTab5", 150, 500, 200, 200,
        TextureManager::GetTextureByName("buttonModern"), "Precision", 20, 18, 3, 40, 5);
    ui->SetUIElementBorderColor("GameTab5", 135, 206, 250);

    ui->CreateInteractionBox("GameSubTab5", 150, 710, 200, 50,
        TextureManager::GetTextureByName("buttonModern"), "Game5", 20, 18, 2, 10, 5);
    ui->SetUIElementBorderColor("GameSubTab5", 135, 206, 250);

    ui->CreateButton("GameTab6", 450, 500, 200, 200,
        TextureManager::GetTextureByName("buttonModern"), "Precision2", 20, 18, 3, 40, 5);
    ui->SetUIElementBorderColor("GameTab6", 135, 206, 250);

    ui->CreateInteractionBox("GameSubTab6", 450, 710, 200, 50,
        TextureManager::GetTextureByName("buttonModern"), "Game6", 20, 18, 2, 10, 5);
    ui->SetUIElementBorderColor("GameSubTab6", 135, 206, 250);

    ui->CreateButton("GameTab7", 750, 500, 200, 200,
        TextureManager::GetTextureByName("buttonModern"), "Precision3", 20, 18, 3, 40, 5);
    ui->SetUIElementBorderColor("GameTab7", 135, 206, 250);

    ui->CreateInteractionBox("GameSubTab7", 750, 710, 200, 50,
        TextureManager::GetTextureByName("buttonModern"), "Game7", 20, 18, 2, 10, 5);
    ui->SetUIElementBorderColor("GameSubTab7", 135, 206, 250);

    ui->CreateButton("GameTab8", 1050, 500, 200, 200,
        TextureManager::GetTextureByName("buttonModern"), "Precision4", 20, 18, 3, 40, 5);
    ui->SetUIElementBorderColor("GameTab8", 135, 206, 250);

    ui->CreateInteractionBox("GameSubTab8", 1050, 710, 200, 50,
        TextureManager::GetTextureByName("buttonModern"), "Game8", 20, 18, 2, 10, 5);
    ui->SetUIElementBorderColor("GameSubTab8", 135, 206, 250);
}

void MainMenu::OnClick(UI* ui) {

}

void MainMenu::Clear(UI* ui) {

}
