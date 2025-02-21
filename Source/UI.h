#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>
#include <optional>
#include <map>
#include "Font.h"
#include "TextureManager.h"
#include "unordered_map"


class TemplateUIElement {
protected:
    SDL_Texture* texture;
    SDL_Rect rectangle;
    std::string name;
    std::string text;
    float textScale = 1.0f;
    int interLine = 20;

    bool border = false;

    int borderThickness = 0;

    int textStartX = 0;
    int textStartY = 0;

    bool buttonTransparent = false;
    unsigned char buttonColor[3] = { 255,255,255 };

    unsigned char borderRGB[3] = { 255,255,255 };

    unsigned char fontRGB[3] = { 255,255,255 };

    Font* font = nullptr;

    unsigned short textRenderType = 1;

    Point predefinedSize;

    bool hidden = false;

    bool hovered = false; // Is button in collidion with mouse

    bool hoverable = false; // Is hover filter aplied with mouse collisojn

    unsigned char hooverFilter[4] = { 0,0,0,0 };

public:

    SDL_Texture* GetTexture();

    void SetTexture(SDL_Texture* temp);

    SDL_Rect* GetRectangle();

    std::string& GetName();

    void SetName(const std::string value);

    std::string& GetText();
    void SetText(std::string temptext);

    float GetTextScale();
    void SetTextScale(float temp);
    int GetInterLine();
    void SetInterLine(int temp);

    bool GetBorder();

    void SetBorder(bool temp);

    int GetBorderThickness();

    void SetBorderThickness(int temp);

    int GetTextStartX();
    void SetTextStartX(int temp);
    int GetTextStartY();
    void SetTextStartY(int temp);

    bool GetTransparent();
    void SetTransparent(bool temp);

    Font* GetFont();

    void SetFont(Font* font);

    void SetButtonColor(unsigned char R, unsigned char G, unsigned char B);

    void SetBorderRGB(unsigned char R, unsigned char G, unsigned char B);

    void SetFontColor(unsigned char R, unsigned char G, unsigned char B);

    void Render(SDL_Renderer *renderer);

    void RenderItslelf(SDL_Renderer* renderer);

    void RenderBorder(SDL_Renderer* renderer);

    void RenderText(SDL_Renderer* renderer);

    void SetRenderTextType(const unsigned short textRenderType);

    bool IsHidden();

    void Hide();

    void Show();

    bool IsHovered();

    void SetHover(bool temp);

    void SetHoverFilter(const bool filter,const unsigned char R, const unsigned char G, const unsigned char B, const unsigned char A);

};

// A button that can be clicked with a mouse
class InteractionBox : public TemplateUIElement {
private:
    bool status = false;
    bool turnedOn = true;
public:
    bool GetStatus();

    void SetStatus(bool value);

    bool ConsumeStatus();

    void TurnOn();

    void TurnOff();

    bool IsOn();

};


// Button that can accept text input
class MassageBox : public TemplateUIElement {
private:
    bool turnedOn = false;
public:
    void CheckInteraction(SDL_Event& event);

    void ManageTextInput(SDL_Event& event);
};

// Basic non interactive button
class Button : public TemplateUIElement {


};

// To propelly start the UI you need to pleace manage input function in event loop and render in rendering loop
class UI
{
private:
    SDL_Renderer* renderer;

    std::vector<Button*> Buttons;
    std::vector<MassageBox*> MassageBoxes;
    std::vector<InteractionBox*> InteractionBoxes;

    std::unordered_map<std::string, Button*> ButtonsMap;
    std::unordered_map<std::string, MassageBox*> MassageBoxesMap;
    std::unordered_map<std::string, InteractionBox*> InteractionBoxesMap;

    FontManager* fontManager;

public:

    UI(SDL_Renderer* renderer);

    void LoadTextures();

    void CreateButton(std::string name, int x, int y, int w, int h, SDL_Texture* texture, Font* font = nullptr,
        std::string text = "", float textScale = 1.0f, int textStartX = 0, int textStartY = 0, int borderThickness = 0);

    void CreateMassageBox(std::string name, int x, int y, int w, int h, SDL_Texture* texture, Font* font = nullptr,
        std::string text = "", float textScale = 1.0f, int textStartX = 0, int textStartY = 0, int borderThickness = 0);

    void CreateInteractionBox(std::string name, int x, int y, int w, int h, SDL_Texture* texture, Font* font = nullptr,
        std::string text = "", float textScale = 1.0f, int textStartX = 0, int textStartY = 0, int borderThickness = 0);


    void CheckHover();

    void CheckMasageBoxInteraction(SDL_Event& event);

    void ManageMassageBoxTextInput(SDL_Event& event);

    void CheckInteractionBoxes(SDL_Event& event);

    Button* GetButtonByName(const std::string& name);
    MassageBox* GetMassageBoxByName(const std::string& name);
    InteractionBox* GetInteractionBoxByName(const std::string& name);

    void SetUIElementColor(const std::string& name, unsigned char R, unsigned char G, unsigned char B);

    void SetUIElementBorderColor(const std::string& name, unsigned char R, unsigned char G, unsigned char B);
    void SetUIElementFontColor(const std::string& name, unsigned char R, unsigned char G, unsigned char B);

    void ManageInput(SDL_Event& event);

    bool DeleteButton(const std::string& name);

    bool DeleteMassageBox(const std::string& name);

    bool DeleteInteractionBox(const std::string& name);

    bool DeleteAnyButton(const std::string& name);

    void Render();

    std::vector<Button*>& GetButtons();

    std::vector<MassageBox*>& GetMassageBoxes();

    std::vector<InteractionBox*>& GetInteractionBoxes();

    // You need to provide not name (made up by you) texture (needs to be already loaded by texture manager) path to pregenerated json file
    void CreateFont(const std::string& name, SDL_Texture* texture, const std::string& jsonPath);

    Font* GetFont(const std::string& name);

    //Function to create json file for font png file that contains charcter glyps separated by lines in other color than the font
    //Requires provided txt file with ordered glyps
    //Example:
    //A
    //B
    //C
    //And so on...
    void ScanFont(const std::string& texturePath, const std::string& charactersDataPath,
        unsigned char fR, unsigned char fG, unsigned char fB, unsigned char bR, unsigned char bG, unsigned char bB, Point size,
        const std::string& outputPath);

    void ClearAllButtons();


    ~UI();
};
