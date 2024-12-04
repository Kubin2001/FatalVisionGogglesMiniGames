#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>
#include <optional>
#include <map>
#include "Font.h"
#include "TextureManager.h"

class TemplateUIElement {
    private:
        SDL_Texture* texture;
        SDL_Rect rectangle;
        std::string name;
        std::string text;
        int textSize;
        int textStep;

        bool border = false;

        int borderThickness = 0;

        int textStartX = 0;
        int textStartY = 0;

        unsigned char borderRGB[3] = {0,0,0};

    public:

        SDL_Texture* GetTexture();

        void SetTexture(SDL_Texture* temp);

        SDL_Rect* GetRectangle();

        std::string& GetName();

        void SetName(const std::string value);

        std::string &GetText();
        void SetText(std::string temptext);

        int GetTextSize();
        void SetTextSize(int temp);
        int GetTextStep();
        void SetTextStep(int temp);

        bool GetBorder();

        void SetBorder(bool temp);

        int GetBorderThickness(int temp);

        void SetBorderThickness(int temp);

        int GetTextStartX();
        void SetTextStartX(int temp);
        int GetTextStartY();
        void SetTextStartY(int temp);

        void SetBorderRGB(unsigned char R, unsigned char G, unsigned char B);

        void RenderBorder(SDL_Renderer* renderer);
        
};

class InteractionBox : public TemplateUIElement {
    private:
        bool status = false;
    public:
        bool GetStatus();

        void SetStatus(bool value);
};

class MassageBox : public TemplateUIElement{
    private:
        bool turnedOn = false;
        bool autoFormating = false;
        int formatingStep = 0;
    public:

        int formatingXtune = 0;
        int formatingYtune = 0;
        void CheckInteraction(SDL_Event& event);

        void ManageTextInput(SDL_Event& event);

        bool GetAutoFormating();

        void SetAutoFormating(bool value);

        
};


class Button : public TemplateUIElement {


};


class UI
{
    private:
        SDL_Renderer* renderer;

        std::vector<Button*> Buttons;
        std::vector<MassageBox*> MassageBoxes;
        std::vector<InteractionBox*> InteractionBoxes;

    public:
        Font* font;

        UI(SDL_Renderer* renderer);

        void LoadTextures();

        void CreateButton(std::string name, int x, int y, int w, int h, SDL_Texture* texture, 
            std::string text = "", int textSize = 20, int textStep = 18, int textStartX=0, int textStartY=0, int borderThickness = 0);

        void CreateMassageBox(std::string name, int x, int y, int w, int h, SDL_Texture* texture,
            int textSize=20, int textStep=18, int textStartX = 0, int textStartY = 0 , int borderThickness = 0,bool autoFormating=false);

        void CreateInteractionBox(std::string name, int x, int y, int w, int h, SDL_Texture* texture,
            std::string text="", int textSize = 20, int textStep = 18, int textStartX = 0, int textStartY = 0, int borderThickness = 0);

        void CheckMasageBoxInteraction(SDL_Event& event);

        void ManageMassageBoxTextInput(SDL_Event& event);

        void CheckInteractionBoxes(SDL_Event& event);

        void SetUIElementBorderColor(const std::string& name, unsigned char R, unsigned char G, unsigned char B);

        void ManageInput(SDL_Event& event);

        void DeleteButton(const std::string& name);

        void DeleteMassageBox(const std::string& name);

        void DeleteInteractionBox(const std::string& name);

        void DeleteAnyButton(const std::string& name);

        void Render();

        void RenderButton(int index);

        void RenderMassageBox(int index);

        void RenderInteractionBox(int index);

        std::vector<Button*>& GetButtons();

        std::vector<MassageBox*>& GetMassageBoxes();

        std::vector<InteractionBox*>& GetInteractionBoxes();

        Button* GetButtonByName(const std::string& name);

        MassageBox* GetMassageBoxByName(const std::string& name);

        InteractionBox* GetInterctionBoxByName(const std::string& name);

        void ClearAllButtons();


        ~UI();
};
