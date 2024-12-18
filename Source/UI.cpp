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

int TemplateUIElement::GetTextSize() {
    return textSize;
}
void TemplateUIElement::SetTextSize(int temp) {
    textSize = temp;
}
int TemplateUIElement::GetTextStep() {
    return textStep;
}
void TemplateUIElement::SetTextStep(int temp) {
    textStep = temp;
}

bool TemplateUIElement::GetBorder() {
    return border;
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

void TemplateUIElement::SetButtonColor(unsigned char R, unsigned char G, unsigned char B) {
    buttonColor[0] = R;
    buttonColor[1] = G;
    buttonColor[2] = B;
}


void TemplateUIElement::SetBorderRGB(unsigned char R, unsigned char G, unsigned char B) {
    borderRGB[0] = R;
    borderRGB[1] = G;
    borderRGB[2] = B;
}

void TemplateUIElement::RenderItslelf(SDL_Renderer* renderer) {

    SDL_SetRenderDrawColor(renderer, buttonColor[0], buttonColor[1], buttonColor[2], 255);

    SDL_RenderFillRect(renderer, &rectangle);

    SDL_SetRenderDrawColor(renderer, Global::defaultDrawColor[0], Global::defaultDrawColor[1], Global::defaultDrawColor[2], 255);
}

void TemplateUIElement::RenderBorder(SDL_Renderer* renderer) {
    SDL_Rect leftLine(rectangle.x, rectangle.y, borderThickness, rectangle.h);
    SDL_Rect upperLine(rectangle.x, rectangle.y, rectangle.w, borderThickness);
    SDL_Rect rightLine((rectangle.x + rectangle.w - borderThickness), rectangle.y, borderThickness, rectangle.h);
    SDL_Rect downLine(rectangle.x, (rectangle.y + rectangle.h - borderThickness), rectangle.w, borderThickness);

    SDL_SetRenderDrawColor(renderer, borderRGB[0], borderRGB[1], borderRGB[2], 255);

    SDL_RenderFillRect(renderer, &leftLine);
    SDL_RenderFillRect(renderer, &upperLine);
    SDL_RenderFillRect(renderer, &rightLine);
    SDL_RenderFillRect(renderer, &downLine);

    SDL_SetRenderDrawColor(renderer, Global::defaultDrawColor[0], Global::defaultDrawColor[1], Global::defaultDrawColor[2], 255);
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
            if (autoFormating) {
                int currentLenght = GetText().length() - formatingStep;
                if ((GetTextSize() * currentLenght) > GetRectangle()->w - (formatingXtune * 3)) {
                    GetText() += '/';
                    formatingStep = GetText().length();
                }
            }
        }

        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && GetText().length() > 0) {
            GetText().pop_back();
        }
    }

}


bool MassageBox::GetAutoFormating() {
    return autoFormating;
}

void MassageBox::SetAutoFormating(bool value) {
    autoFormating = value;
}
//MassageBox
//InteractionBox
bool InteractionBox::GetStatus() {
    return status;
}

void InteractionBox::SetStatus(bool value) {
    status = value;
}
//InteractionBox

UI::UI(SDL_Renderer* renderer,bool setUpFont) {
    font = new Font(74);
    this->renderer = renderer;
    if (setUpFont) {
        font->LoadText(29, 29);
    }
}


void UI::LoadTextures() {
    TextureManager::LoadMultipleTextures("Textures/Interface");
    TextureManager::LoadMultipleTextures("Textures/Interface/Fonts");
    TextureManager::LoadMultipleTextures("Textures/Interface/Others");
    font->SetTexture(TextureManager::GetTextureByName("fontStandard"));
}

void UI::SetFontColor(const unsigned char R, const unsigned char G, const unsigned char B) {
    if (font->GetTexture() != nullptr) {
        SDL_SetTextureColorMod(font->GetTexture(), 255, 255, 255); // Reset tak czy siak niewa¿ne czy bia³e czy nie
        SDL_SetTextureColorMod(font->GetTexture(), R, G, B);
    }
}

void UI::Render() {
    for (size_t i = 0; i < Buttons.size(); i++)
    {
        RenderButton(i);
    }
    for (size_t i = 0; i < MassageBoxes.size(); i++)
    {
        RenderMassageBox(i);
    }

    for (size_t i = 0; i < InteractionBoxes.size(); i++)
    {
        RenderInteractionBox(i);
    }
}


void UI::CreateButton(std::string name, int x, int y, int w, int h, SDL_Texture* texture, std::string text, int textSize, int textStep, int textStartX, int textStartY, int borderThickness) {
    Buttons.emplace_back(new Button());
    Buttons.back()->SetName(name);
    Buttons.back()->GetRectangle()->x = x;
    Buttons.back()->GetRectangle()->y = y;
    Buttons.back()->GetRectangle()->w = w;
    Buttons.back()->GetRectangle()->h = h;

    Buttons.back()->SetTexture(texture);


    Buttons.back()->SetText(text);
    Buttons.back()->SetTextSize(textSize);
    Buttons.back()->SetTextStep(textStep);

    Buttons.back()->SetTextStartX(textStartX);

    Buttons.back()->SetTextStartY(textStartY);

    if (borderThickness > 0) {
        Buttons.back()->SetBorderThickness(borderThickness);
        Buttons.back()->SetBorder(true);
    }
}

void UI::CreateMassageBox(std::string name, int x, int y, int w, int h, SDL_Texture* texture, int textSize, int textStep, int textStartX, int textStartY, int borderThickness, bool autoFormating) {
    MassageBoxes.emplace_back(new MassageBox());
    MassageBoxes.back()->SetName(name);
    MassageBoxes.back()->GetRectangle()->x = x;
    MassageBoxes.back()->GetRectangle()->y = y;
    MassageBoxes.back()->GetRectangle()->w = w;
    MassageBoxes.back()->GetRectangle()->h = h;

    MassageBoxes.back()->SetTexture(texture);

    MassageBoxes.back()->SetText("");

    MassageBoxes.back()->SetTextSize(textSize);

    MassageBoxes.back()->SetTextStep(textStep);

    MassageBoxes.back()->SetTextStartX(textStartX);

    MassageBoxes.back()->SetTextStartY(textStartY);

    MassageBoxes.back()->SetAutoFormating(autoFormating);
    MassageBoxes.back()->formatingXtune = MassageBoxes.back()->GetRectangle()->x / 10;
    MassageBoxes.back()->formatingYtune = MassageBoxes.back()->GetRectangle()->y / 10;

    if (borderThickness > 0) {
        MassageBoxes.back()->SetBorderThickness(borderThickness);
        MassageBoxes.back()->SetBorder(true);
    }


}

void UI::CreateInteractionBox(std::string name, int x, int y, int w, int h, SDL_Texture* texture, std::string text, int textSize, int textStep, int textStartX, int textStartY, int borderThickness) {
    InteractionBoxes.emplace_back(new InteractionBox());
    InteractionBoxes.back()->SetName(name);
    InteractionBoxes.back()->GetRectangle()->x = x;
    InteractionBoxes.back()->GetRectangle()->y = y;
    InteractionBoxes.back()->GetRectangle()->w = w;
    InteractionBoxes.back()->GetRectangle()->h = h;

    InteractionBoxes.back()->SetTexture(texture);

    InteractionBoxes.back()->SetText(text);

    InteractionBoxes.back()->SetTextSize(textSize);

    InteractionBoxes.back()->SetTextStep(textStep);

    InteractionBoxes.back()->SetTextStartX(textStartX);

    InteractionBoxes.back()->SetTextStartY(textStartY);

    if (borderThickness > 0) {
        InteractionBoxes.back()->SetBorderThickness(borderThickness);
        InteractionBoxes.back()->SetBorder(true);
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
    for (size_t i = 0; i < InteractionBoxes.size(); i++)
    {
        if (event.button.button == SDL_BUTTON_LEFT) {
            SDL_Rect temprect{ event.button.x ,event.button.y,1,1 };
            if (SimpleCollision(*InteractionBoxes[i]->GetRectangle(), temprect)) {
                InteractionBoxes[i]->SetStatus(true);
            }
        }
    }

}

void UI::SetUIElementColor(const std::string& name, unsigned char R, unsigned char G, unsigned char B) {
    for (const auto& it : Buttons)
    {
        if (it->GetName() == name) {
            it->SetButtonColor(R, G, B);
            return;
        }
    }
    for (const auto& it : MassageBoxes)
    {
        if (it->GetName() == name) {
            it->SetButtonColor(R, G, B);
            return;
        }
    }
    for (const auto& it : InteractionBoxes)
    {
        if (it->GetName() == name) {
            it->SetButtonColor(R, G, B);
            return;
        }
    }
}

void UI::SetUIElementBorderColor(const std::string& name, unsigned char R, unsigned char G, unsigned char B) {
    for (const auto& it : Buttons)
    {
        if (it->GetName() == name) {
            it->SetBorderRGB(R, G, B);
            return;
        }
    }
    for (const auto& it : MassageBoxes)
    {
        if (it->GetName() == name) {
            it->SetBorderRGB(R, G, B);
            return;
        }
    }
    for (const auto& it : InteractionBoxes)
    {
        if (it->GetName() == name) {
            it->SetBorderRGB(R, G, B);
            return;
        }
    }
}

void UI::ManageInput(SDL_Event& event) {
    CheckMasageBoxInteraction(event);

    ManageMassageBoxTextInput(event);

    CheckInteractionBoxes(event);
}

void UI::DeleteButton(const std::string& name) {
    for (size_t i = 0; i < Buttons.size(); i++)
    {
        if (Buttons[i]->GetName() == name) {
            Buttons.erase(Buttons.begin() + i);
            return;
        }
    }
}

void UI::DeleteMassageBox(const std::string& name) {
    for (size_t i = 0; i < MassageBoxes.size(); i++)
    {
        if (MassageBoxes[i]->GetName() == name) {
            MassageBoxes.erase(MassageBoxes.begin() + i);
            return;
        }
    }
}

void UI::DeleteInteractionBox(const std::string& name) {
    for (size_t i = 0; i < InteractionBoxes.size(); i++)
    {
        if (InteractionBoxes[i]->GetName() == name) {
            InteractionBoxes.erase(InteractionBoxes.begin() + i);
            return;
        }
    }
}

void UI::DeleteAnyButton(const std::string& name) {
    for (size_t i = 0; i < Buttons.size(); i++)
    {
        if (Buttons[i]->GetName() == name) {
            Buttons.erase(Buttons.begin() + i);
            return;
        }
    }
    for (size_t i = 0; i < MassageBoxes.size(); i++)
    {
        if (MassageBoxes[i]->GetName() == name) {
            MassageBoxes.erase(MassageBoxes.begin() + i);
            return;
        }
    }
    for (size_t i = 0; i < InteractionBoxes.size(); i++)
    {
        if (InteractionBoxes[i]->GetName() == name) {
            InteractionBoxes.erase(InteractionBoxes.begin() + i);
            return;
        }
    }
}

void UI::RenderButton(int index) {
    if (Buttons[index]->GetTexture() == nullptr) {
        Buttons[index]->RenderItslelf(renderer);
    }
    else
    {
        SDL_RenderCopy(renderer, Buttons[index]->GetTexture(), NULL, Buttons[index]->GetRectangle());
    }


    if (Buttons[index]->GetBorder()) {
        Buttons[index]->RenderBorder(renderer);
    }

    if (Buttons[index]->GetText() != "") {
        font->RenderText(renderer, Buttons[index]->GetText(), Buttons[index]->GetRectangle()->x,
            Buttons[index]->GetRectangle()->y, Buttons[index]->GetTextSize(), Buttons[index]->GetTextSize(), Buttons[index]->GetTextStep()
            , Buttons[index]->GetTextStartX(), Buttons[index]->GetTextStartY());
    }
}

void UI::RenderMassageBox(int index) {
    if (MassageBoxes[index]->GetTexture() == nullptr) {
        MassageBoxes[index]->RenderItslelf(renderer);
    }
    else
    {
        SDL_RenderCopy(renderer, MassageBoxes[index]->GetTexture(), NULL, MassageBoxes[index]->GetRectangle());
    }

    if (MassageBoxes[index]->GetBorder()) {
        MassageBoxes[index]->RenderBorder(renderer);
    }

    if (MassageBoxes[index]->GetText() != "") {
        font->RenderText(renderer, MassageBoxes[index]->GetText(), MassageBoxes[index]->GetRectangle()->x + MassageBoxes[index]->formatingXtune,
            MassageBoxes[index]->GetRectangle()->y + +MassageBoxes[index]->formatingYtune,
            MassageBoxes[index]->GetTextSize(), MassageBoxes[index]->GetTextSize(), MassageBoxes[index]->GetTextStep()
            , MassageBoxes[index]->GetTextStartX(), MassageBoxes[index]->GetTextStartY());
    }
}

void UI::RenderInteractionBox(int index) {
    if (InteractionBoxes[index]->GetTexture() == nullptr) {
        InteractionBoxes[index]->RenderItslelf(renderer);
    }
    else
    {
        SDL_RenderCopy(renderer, InteractionBoxes[index]->GetTexture(), NULL, InteractionBoxes[index]->GetRectangle());
    }

    if (InteractionBoxes[index]->GetBorder()) {
        InteractionBoxes[index]->RenderBorder(renderer);
    }

    if (InteractionBoxes[index]->GetText() != "") {
        font->RenderText(renderer, InteractionBoxes[index]->GetText(), InteractionBoxes[index]->GetRectangle()->x,
            InteractionBoxes[index]->GetRectangle()->y, InteractionBoxes[index]->GetTextSize(),
            InteractionBoxes[index]->GetTextSize(), InteractionBoxes[index]->GetTextStep()
            , InteractionBoxes[index]->GetTextStartX(), InteractionBoxes[index]->GetTextStartY());
    }
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

Button* UI::GetButtonByName(const std::string& name) {
    for (auto it = Buttons.begin(); it != Buttons.end(); ++it) {
        if ((*it)->GetName() == name) {
            return *it;
            break;
        }
    }
    return nullptr;
}

MassageBox* UI::GetMassageBoxByName(const std::string& name) {
    for (auto it = MassageBoxes.begin(); it != MassageBoxes.end(); ++it) {
        if ((*it)->GetName() == name) {
            return *it;
            break;
        }
    }
    return nullptr;
}

InteractionBox* UI::GetInterctionBoxByName(const std::string& name) {
    for (auto it = InteractionBoxes.begin(); it != InteractionBoxes.end(); ++it) {
        if ((*it)->GetName() == name) {
            return *it;
            break;
        }
    }
    return nullptr;
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
}



UI::~UI() {
    ClearAllButtons();
}
