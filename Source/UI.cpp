#include <iostream>
#include <string>
#include <fstream>
#include <SDL.h>
#include <optional>
#include "UI.h"
#include "Colision.h"
#include "Font.h"
#include "GlobalVariables.h"

//BUTTON


SDL_Texture* TemplateUIElement::GetTexture() {
    return texture;
}

void TemplateUIElement::SetTexture(SDL_Texture* temp) {
    texture = temp;
}

SDL_Rect* TemplateUIElement::GetRectangle() {
    return &rectangle;
}

std::string& TemplateUIElement::GetName() {
    return name;
}

void TemplateUIElement::SetName(const std::string value) {
    name = value;
}

void TemplateUIElement::SetText(std::string temptext) {
    text = temptext;
}

std::string& TemplateUIElement::GetText() {
    return text;
}

float TemplateUIElement::GetTextScale() {
    return textScale;
}
void TemplateUIElement::SetTextScale(float temp) {
    textScale = temp;
}
int TemplateUIElement::GetInterLine() {
    return interLine;
}
void TemplateUIElement::SetInterLine(int temp) {
    interLine = temp;
}

bool TemplateUIElement::GetBorder() {
    return border;
}

Font* TemplateUIElement::GetFont() {
    return font;
}

void TemplateUIElement::SetFont(Font* font) {
    this->font = font;
}

void TemplateUIElement::SetBorder(bool temp) {
    border = temp;
}

int TemplateUIElement::GetBorderThickness() {
    return borderThickness;
}

void TemplateUIElement::SetBorderThickness(int temp) {
    borderThickness = temp;
}

int TemplateUIElement::GetTextStartX() {
    return textStartX;
}
void TemplateUIElement::SetTextStartX(int temp) {
    textStartX = temp;
}
int TemplateUIElement::GetTextStartY() {
    return textStartY;
}
void TemplateUIElement::SetTextStartY(int temp) {
    textStartY = temp;
}

bool TemplateUIElement::GetTransparent() {
    return buttonTransparent;
}

void TemplateUIElement::SetTransparent(bool temp) {
    buttonTransparent = temp;
}

void TemplateUIElement::SetButtonColor(unsigned char R, unsigned char G, unsigned char B) {
    if (buttonTransparent) {
        buttonTransparent = false;
    }
    buttonColor[0] = R;
    buttonColor[1] = G;
    buttonColor[2] = B;
}


void TemplateUIElement::SetBorderRGB(unsigned char R, unsigned char G, unsigned char B) {
    borderRGB[0] = R;
    borderRGB[1] = G;
    borderRGB[2] = B;
}

void TemplateUIElement::SetFontColor(unsigned char R, unsigned char G, unsigned char B) {
    if (font != nullptr) {
        if (font->GetTexture() != nullptr) {
            fontRGB[0] = R;
            fontRGB[1] = G;
            fontRGB[2] = B;
        }
    }
}

void TemplateUIElement::Render(SDL_Renderer* renderer) {
    if (!hidden) {
        if (GetTexture() == nullptr) {
            RenderItslelf(renderer);
        }
        else {
            SDL_RenderCopy(renderer, GetTexture(), NULL, GetRectangle());
        }

        if (hovered && hoverable) {
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(renderer, hooverFilter[0], hooverFilter[1], hooverFilter[2], hooverFilter[3]);
            SDL_RenderFillRect(renderer, &rectangle);

            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
            SDL_SetRenderDrawColor(renderer, Global::defaultDrawColor[0], Global::defaultDrawColor[1], Global::defaultDrawColor[2], 255);
        }


        if (GetBorder()) {
            RenderBorder(renderer);
        }

        RenderText(renderer);
    }
}

void TemplateUIElement::RenderItslelf(SDL_Renderer* renderer) {
    if (!buttonTransparent) {
        if (hovered && hoverable) {

            SDL_SetRenderDrawColor(renderer, buttonColor[0], buttonColor[1], buttonColor[2], 255);

            SDL_RenderFillRect(renderer, &rectangle);

            SDL_SetRenderDrawColor(renderer, Global::defaultDrawColor[0], Global::defaultDrawColor[1], Global::defaultDrawColor[2], 255);

            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(renderer, hooverFilter[0], hooverFilter[1], hooverFilter[2], hooverFilter[3]);
            SDL_RenderFillRect(renderer, &rectangle);
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, buttonColor[0], buttonColor[1], buttonColor[2], 255);

            SDL_RenderFillRect(renderer, &rectangle);

            SDL_SetRenderDrawColor(renderer, Global::defaultDrawColor[0], Global::defaultDrawColor[1], Global::defaultDrawColor[2], 255);
        }

    }
}

void TemplateUIElement::RenderBorder(SDL_Renderer* renderer) {
    SDL_Rect leftLine{ rectangle.x, rectangle.y, borderThickness, rectangle.h };
    SDL_Rect upperLine{ rectangle.x, rectangle.y, rectangle.w, borderThickness };
    SDL_Rect rightLine{ (rectangle.x + rectangle.w - borderThickness), rectangle.y, borderThickness, rectangle.h };
    SDL_Rect downLine{ rectangle.x, (rectangle.y + rectangle.h - borderThickness), rectangle.w, borderThickness };

    SDL_SetRenderDrawColor(renderer, borderRGB[0], borderRGB[1], borderRGB[2], 255);

    SDL_RenderFillRect(renderer, &leftLine);
    SDL_RenderFillRect(renderer, &upperLine);
    SDL_RenderFillRect(renderer, &rightLine);
    SDL_RenderFillRect(renderer, &downLine);

    SDL_SetRenderDrawColor(renderer, Global::defaultDrawColor[0], Global::defaultDrawColor[1], Global::defaultDrawColor[2], 255);
}

void TemplateUIElement::RenderText(SDL_Renderer* renderer) {
    if (font != nullptr) {
        SDL_SetTextureColorMod(font->GetTexture(), 255, 255, 255); // Reset anyway no matter the color
        SDL_SetTextureColorMod(font->GetTexture(), fontRGB[0], fontRGB[1], fontRGB[2]);
        switch (textRenderType) {
            case 1:
                font->RenderText(renderer, text, rectangle, textScale, interLine, textStartX, textStartY);
                break;
            case 2:
                font->RenderTextCenter(renderer, text, rectangle, textScale, interLine, textStartX, textStartY);
                break;
            case 3:
                font->RenderTextFromRight(renderer, text, rectangle, textScale, interLine, textStartX, textStartY);
                break;
            case 4:
                predefinedSize = font->CalculatePredefinedSize(text, interLine);
                font->RenderTextCenterPred(renderer, text, rectangle,predefinedSize, textScale, interLine, textStartX, textStartY);
                break;
            default: // Standardowa opcja
                font->RenderText(renderer, text, rectangle, textScale, interLine, textStartX, textStartY);
                break;
        }

    }
}

void TemplateUIElement::SetRenderTextType(const unsigned short textRenderType) {
    this->textRenderType = textRenderType;
}


bool TemplateUIElement::IsHidden() {
    return hidden;
}

void TemplateUIElement::Hide() {
    hidden = true;
}

void TemplateUIElement::Show() {
    hidden = false;
}

bool TemplateUIElement::IsHovered() {
    return hovered;
}

void TemplateUIElement::SetHover(bool temp) {
    hovered = temp;
}

void TemplateUIElement::SetHoverFilter(const bool filter, const unsigned char R, const unsigned char G, const unsigned char B, const unsigned char A, const std::string& sound) {
    this->hoverable = filter;
    hooverFilter[0] = R;
    hooverFilter[1] = G;
    hooverFilter[2] = B;
    hooverFilter[3] = A;
    hooverSound = sound;
}

std::string& TemplateUIElement::GetHooverSound() {
    return hooverSound;
}

//BUTTON
//MassageBox
void MassageBox::CheckInteraction(SDL_Event& event) {
    if (event.button.button == SDL_BUTTON_LEFT) {
        SDL_Rect temprect{ event.button.x ,event.button.y,1,1 };
        if (SimpleCollision(*GetRectangle(), temprect)) {
            turnedOn = true;
        }
        else if (!SimpleCollision(*GetRectangle(), temprect) && turnedOn) {
            turnedOn = false;
        }
    }
}

void MassageBox::ManageTextInput(SDL_Event& event) {
    if (turnedOn) {
        SDL_StartTextInput();

        if (event.type == SDL_TEXTINPUT) {
            GetText() += event.text.text;
        }
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_RETURN) {
                GetText() += '\n';
            }
        }

        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && GetText().length() > 0) {
            GetText().pop_back();
        }
    }

}

//MassageBox
//InteractionBox
bool InteractionBox::GetStatus() {
    return status;
}

void InteractionBox::SetStatus(bool value) {
    status = value;
}

bool InteractionBox::ConsumeStatus() {
    if (status) {
        status = false;
        return true;
    }
    return false;
}

void InteractionBox::TurnOn() {
    turnedOn = true;
}

void InteractionBox::TurnOff() {
    turnedOn = false;
}

bool InteractionBox::IsOn() {
    return turnedOn;
}

void InteractionBox::SetClickSound(const std::string& temp) {
    this->clickSound = temp;
}

std::string& InteractionBox::GetClickSound() {
    return clickSound;
}
//InteractionBox

UI::UI(SDL_Renderer* renderer) {
    fontManager = new FontManager();
    this->renderer = renderer;
    if (TextureManager::isWorking()) {
        LoadTextures();
    }

    lastMousePos.x = -10000000;
    lastMousePos.y = -10000000;
}


void UI::LoadTextures() {
    TextureManager::LoadMultipleTextures("Textures/Interface");
    TextureManager::LoadMultipleTextures("Textures/Interface/Fonts");
    TextureManager::LoadMultipleTextures("Textures/Interface/Others");
}

void UI::Render() {
    for (const auto &it: Buttons)
    {
        it->Render(renderer);
    }

    for (const auto& it : MassageBoxes)
    {
        it->Render(renderer);
    }

    for (const auto& it : InteractionBoxes)
    {
        it->Render(renderer);
    }
}


void UI::CreateButton(std::string name, int x, int y, int w, int h, SDL_Texture* texture, Font* font,
    std::string text, float textScale, int textStartX, int textStartY, int borderThickness) {

    if (GetButtonByName(name) != nullptr) {
        std::cout << "Warning name collision button with name: " << name << " already exists addition abborted\n";
        return;
    }

    Buttons.emplace_back(new Button());
    Buttons.back()->SetName(name);
    Buttons.back()->GetRectangle()->x = x;
    Buttons.back()->GetRectangle()->y = y;
    Buttons.back()->GetRectangle()->w = w;
    Buttons.back()->GetRectangle()->h = h;

    Buttons.back()->SetTexture(texture);
    if (texture == nullptr) {
        Buttons.back()->SetTransparent(true);
    }

    Buttons.back()->SetText(text);
    Buttons.back()->SetTextScale(textScale);
    Buttons.back()->SetFont(font);
    if (font != nullptr) {
        Buttons.back()->SetInterLine(font->GetStandardInterline());
    }

    Buttons.back()->SetTextStartX(textStartX);

    Buttons.back()->SetTextStartY(textStartY);

    if (borderThickness > 0) {
        Buttons.back()->SetBorderThickness(borderThickness);
        Buttons.back()->SetBorder(true);
    }

    ButtonsMap.emplace(Buttons.back()->GetName(), Buttons.back());
}

void UI::CreateMassageBox(std::string name, int x, int y, int w, int h, SDL_Texture* texture, Font* font,
    std::string text, float textScale, int textStartX, int textStartY, int borderThickness) {

    if (GetMassageBoxByName(name) != nullptr) {
        std::cout << "Warning name collision massage box with name: " << name << " already exists addition abborted\n";
        return;
    }

    MassageBoxes.emplace_back(new MassageBox());
    MassageBoxes.back()->SetName(name);
    MassageBoxes.back()->GetRectangle()->x = x;
    MassageBoxes.back()->GetRectangle()->y = y;
    MassageBoxes.back()->GetRectangle()->w = w;
    MassageBoxes.back()->GetRectangle()->h = h;

    MassageBoxes.back()->SetTexture(texture);
    if (texture == nullptr) {
        MassageBoxes.back()->SetTransparent(true);
    }

    MassageBoxes.back()->SetText("");

    MassageBoxes.back()->SetTextScale(textScale);
    MassageBoxes.back()->SetFont(font);
    if (font != nullptr) {
        MassageBoxes.back()->SetInterLine(font->GetStandardInterline());
    }

    MassageBoxes.back()->SetTextStartX(textStartX);

    MassageBoxes.back()->SetTextStartY(textStartY);


    if (borderThickness > 0) {
        MassageBoxes.back()->SetBorderThickness(borderThickness);
        MassageBoxes.back()->SetBorder(true);
    }

    MassageBoxesMap.emplace(MassageBoxes.back()->GetName(), MassageBoxes.back());


}

void UI::CreateInteractionBox(std::string name, int x, int y, int w, int h, SDL_Texture* texture, Font* font,
    std::string text, float textScale, int textStartX, int textStartY, int borderThickness) {

    if (GetInteractionBoxByName(name) != nullptr) {
        std::cout << "Warning name collision interaction box with name: " << name << " already exists addition abborted\n";
        return;
    }

    InteractionBoxes.emplace_back(new InteractionBox());
    InteractionBoxes.back()->SetName(name);
    InteractionBoxes.back()->GetRectangle()->x = x;
    InteractionBoxes.back()->GetRectangle()->y = y;
    InteractionBoxes.back()->GetRectangle()->w = w;
    InteractionBoxes.back()->GetRectangle()->h = h;

    InteractionBoxes.back()->SetTexture(texture);
    if (texture == nullptr) {
        InteractionBoxes.back()->SetTransparent(true);
    }

    InteractionBoxes.back()->SetText(text);

    InteractionBoxes.back()->SetTextScale(textScale);
    InteractionBoxes.back()->SetFont(font);
    if (font != nullptr) {
        InteractionBoxes.back()->SetInterLine(font->GetStandardInterline());
    }

    InteractionBoxes.back()->SetTextStartX(textStartX);

    InteractionBoxes.back()->SetTextStartY(textStartY);

    if (borderThickness > 0) {
        InteractionBoxes.back()->SetBorderThickness(borderThickness);
        InteractionBoxes.back()->SetBorder(true);
    }

    InteractionBoxesMap.emplace(InteractionBoxes.back()->GetName(), InteractionBoxes.back());
}



void UI::CheckHover() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    SDL_Rect rect{ x,y,1,1 };
    for (auto& it : Buttons) {
        if (SimpleCollision(*it->GetRectangle(), rect)) {
            it->SetHover(true);
            // patrzenie czy mo�e by� wydany d�wi�k tylko wtedy zadzia�a gdy mysz pierwszy raz jest na przycisku
            if (it->GetHooverSound() != "") { 
                SDL_Rect prevMousePos{ lastMousePos.x,lastMousePos.y,1,1 };
                if (!SimpleCollision(prevMousePos, *it->GetRectangle())) {
                    SoundManager::PlaySound(it->GetHooverSound());
                }
            }
        }
        else
        {
            it->SetHover(false);
        }
    }
    for (auto& it : MassageBoxes) {
        if (SimpleCollision(*it->GetRectangle(), rect)) {
            it->SetHover(true);
            // patrzenie czy mo�e by� wydany d�wi�k tylko wtedy zadzia�a gdy mysz pierwszy raz jest na przycisku
            if (it->GetHooverSound() != "") {
                SDL_Rect prevMousePos{ lastMousePos.x,lastMousePos.y,1,1 };
                if (!SimpleCollision(prevMousePos, *it->GetRectangle())) {
                    SoundManager::PlaySound(it->GetHooverSound());
                }
            }
        }
        else
        {
            it->SetHover(false);
        }
    }
    for (auto& it : InteractionBoxes) {
        if (SimpleCollision(*it->GetRectangle(), rect)) {
            it->SetHover(true);
            // patrzenie czy mo�e by� wydany d�wi�k tylko wtedy zadzia�a gdy mysz pierwszy raz jest na przycisku
            if (it->GetHooverSound() != "") {
                SDL_Rect prevMousePos{ lastMousePos.x,lastMousePos.y,1,1 };
                if (!SimpleCollision(prevMousePos, *it->GetRectangle())) {
                    SoundManager::PlaySound(it->GetHooverSound());
                }
            }
        }
        else
        {
            it->SetHover(false);
        }
    }
}

void  UI::CheckMasageBoxInteraction(SDL_Event& event) {
    for (auto& it : MassageBoxes) {
        it->CheckInteraction(event);
    }
}

void UI::ManageMassageBoxTextInput(SDL_Event& event) {
    for (auto& it : MassageBoxes) {
        it->ManageTextInput(event);
    }
}

void UI::CheckInteractionBoxes(SDL_Event& event) {
    if (event.type == SDL_MOUSEBUTTONUP) {
        for (size_t i = 0; i < InteractionBoxes.size(); i++) {
            if (InteractionBoxes[i]->IsOn()) {
                SDL_Rect temprect{ event.button.x ,event.button.y,1,1 };
                if (SimpleCollision(*InteractionBoxes[i]->GetRectangle(), temprect)) {
                    InteractionBoxes[i]->SetStatus(true);
                    if (InteractionBoxes[i]->GetClickSound() != "") {
                        SoundManager::PlaySound(InteractionBoxes[i]->GetClickSound());
                    }
                }
            }
        }
    }
}

Button* UI::GetButtonByName(const std::string& name) {
    auto btnFind = ButtonsMap.find(name);
    if (btnFind != ButtonsMap.end()) {
        return btnFind->second;
    }
    else
    {
        return nullptr;
    }
}
MassageBox* UI::GetMassageBoxByName(const std::string& name) {
    auto msBoxFind = MassageBoxesMap.find(name);
    if (msBoxFind != MassageBoxesMap.end()) {
        return msBoxFind->second;
    }
    else
    {
        return nullptr;
    }
}
InteractionBox* UI::GetInteractionBoxByName(const std::string& name) {
    auto interBoxFind = InteractionBoxesMap.find(name);
    if (interBoxFind != InteractionBoxesMap.end()) {
        return interBoxFind->second;
    }
    else
    {
        return nullptr;
    }
}

void UI::SetUIElementColor(const std::string& name, unsigned char R, unsigned char G, unsigned char B) {
    Button* button = GetButtonByName(name);
    if (button != nullptr) {
        button->SetButtonColor(R, G, B);
        return;
    }

    MassageBox* massageBox = GetMassageBoxByName(name);
    if (massageBox != nullptr) {
        massageBox->SetButtonColor(R, G, B);
        return;
    }

    InteractionBox* interactionBox = GetInteractionBoxByName(name);
    if (interactionBox != nullptr) {
        interactionBox->SetButtonColor(R, G, B);
        return;
    }
}

void UI::SetUIElementBorderColor(const std::string& name, unsigned char R, unsigned char G, unsigned char B) {
    Button* button = GetButtonByName(name);
    if (button != nullptr) {
        button->SetBorderRGB(R, G, B);
        return;
    }

    MassageBox* massageBox = GetMassageBoxByName(name);
    if (massageBox != nullptr) {
        massageBox->SetBorderRGB(R, G, B);
        return;
    }

    InteractionBox* interactionBox = GetInteractionBoxByName(name);
    if (interactionBox != nullptr) {
        interactionBox->SetBorderRGB(R, G, B);
        return;
    }
}

void UI::SetUIElementFontColor(const std::string& name, unsigned char R, unsigned char G, unsigned char B) {
    Button* button = GetButtonByName(name);
    if (button != nullptr) {
        button->SetFontColor(R, G, B);
        return;
    }

    MassageBox* massageBox = GetMassageBoxByName(name);
    if (massageBox != nullptr) {
        massageBox->SetFontColor(R, G, B);
        return;
    }

    InteractionBox* interactionBox = GetInteractionBoxByName(name);
    if (interactionBox != nullptr) {
        interactionBox->SetFontColor(R, G, B);
        return;
    }
}

void UI::ManageInput(SDL_Event& event) {
    

    CheckHover();

    CheckMasageBoxInteraction(event);

    ManageMassageBoxTextInput(event);

    CheckInteractionBoxes(event);

    SDL_GetMouseState(&lastMousePos.x, &lastMousePos.y);
}

bool UI::DeleteButton(const std::string& name) {
    ButtonsMap.erase(name);
    for (size_t i = 0; i < Buttons.size(); i++)
    {
        if (Buttons[i]->GetName() == name) {
            delete Buttons[i];
            Buttons.erase(Buttons.begin() + i);
            return true;
        }
    }
    return false;
}

bool UI::DeleteMassageBox(const std::string& name) {
    MassageBoxesMap.erase(name);
    for (size_t i = 0; i < MassageBoxes.size(); i++)
    {
        if (MassageBoxes[i]->GetName() == name) {
            delete MassageBoxes[i];
            MassageBoxes.erase(MassageBoxes.begin() + i);
            return true;
        }
    }
    return false;
}

bool UI::DeleteInteractionBox(const std::string& name) {
    InteractionBoxesMap.erase(name);
    for (size_t i = 0; i < InteractionBoxes.size(); i++)
    {
        if (InteractionBoxes[i]->GetName() == name) {
            delete InteractionBoxes[i];
            InteractionBoxes.erase(InteractionBoxes.begin() + i);
            return true;
        }
    }
    return false;
}

bool UI::DeleteAnyButton(const std::string& name) {
    if (DeleteButton(name)) { return true; }
    if (DeleteMassageBox(name)) { return true; }
    if (DeleteInteractionBox(name)) { return true; }
    return false;
}

std::vector<Button*>& UI::GetButtons() {
    return Buttons;
}

std::vector<MassageBox*>& UI::GetMassageBoxes() {
    return MassageBoxes;
}

std::vector<InteractionBox*>& UI::GetInteractionBoxes() {
    return InteractionBoxes;
}

void UI::CreateFont(const std::string& name, SDL_Texture* texture, const std::string& jsonPath) {
    fontManager->CreateFont(name, texture, jsonPath);
}

Font* UI::GetFont(const std::string& name) {
    return fontManager->GetFont(name);
}

void UI::ScanFont(const std::string& texturePath, const std::string& charactersDataPath,
    unsigned char fR, unsigned char fG, unsigned char fB, unsigned char bR, unsigned char bG, unsigned char bB, Point size,
    const std::string& outputPath) {
    fontManager->ScanFont(texturePath, charactersDataPath, fR, fG, fB, bR, bG, bB, size.x, size.y);
}

void UI::ClearAllButtons() {
    for (auto& it : Buttons) {
        delete it;
    }
    for (auto& it : MassageBoxes) {
        delete it;
    }
    for (auto& it : InteractionBoxes) {
        delete it;
    }
    Buttons.clear();
    MassageBoxes.clear();
    InteractionBoxes.clear();
    ButtonsMap.clear();
    MassageBoxesMap.clear();
    InteractionBoxesMap.clear();
}



UI::~UI() {
    ClearAllButtons();
    delete fontManager;
}
