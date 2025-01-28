#include <iostream>
#include <SDL.h>
#include "Camera.h"

Camera::Camera(bool useBorders) {
    this->useBorders = useBorders;

}
float Camera::GetZoom() {
    return zoom;
}

SDL_Rect* Camera::GetRectangle() {
    return &rectangle;
}


void Camera::UpdatePosition(const Uint8* state) {

    if (state[SDL_SCANCODE_D]) {
        rectangle.x  += 3 +(zoomRelativeMoveSpeed * 15);
    }
    if (state[SDL_SCANCODE_A]) {
        rectangle.x -= 3 + (zoomRelativeMoveSpeed *15);
    }
    if (state[SDL_SCANCODE_S]) {
        rectangle.y += 3 + (zoomRelativeMoveSpeed * 15);
    }
    if (state[SDL_SCANCODE_W]) {
        rectangle.y -= 3 + (zoomRelativeMoveSpeed * 15);
    }
    if (state[SDL_SCANCODE_O]) { // Zoom Out
        if (zoom > 1.0f) {
            zoom -= 0.1f;
            zoomRelativeMoveSpeed += 0.5f;
        }
        else if(zoom > 0.25f)
        {
            zoom -= 0.01f;
            zoomRelativeMoveSpeed += 0.05f;
        }
    }
    if (state[SDL_SCANCODE_P]) { // Zoom in
        if (zoom < 2.0f)
        {
            zoom += 0.01f;
            if (zoomRelativeMoveSpeed > 0.06f) {
                zoomRelativeMoveSpeed -= 0.05f;
            }

        }
        else if (zoom < 1.9f) {
            zoom += 0.1f;
            if (zoomRelativeMoveSpeed > 0.6f) {
                zoomRelativeMoveSpeed -= 0.5f;
            }

        }
    }
    //std::cout <<zoom<<"  " << zoomRelativeMoveSpeed << "\n";
}


Camera::~Camera() {
}

