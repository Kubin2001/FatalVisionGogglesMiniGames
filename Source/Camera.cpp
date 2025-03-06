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

void Camera::UseBorders(bool temp) {
    this->useBorders = temp;
}

void Camera::SetBorders(int minX, int maxX, int minY, int maxY) {
    this->useBorders = true;
    this->minX = minY;
    this->maxX = maxX;
    this->minY = minY;
    this->maxY = maxY;
}

void Camera::UpdatePosition(const SDL_Event& event, const Uint8* state) {
    if (!useBorders) {
        if (state[SDL_SCANCODE_D]) {
            rectangle.x += 3 + (zoomRelativeMoveSpeed * 15);
        }
        if (state[SDL_SCANCODE_A]) {
            rectangle.x -= 3 + (zoomRelativeMoveSpeed * 15);
        }
        if (state[SDL_SCANCODE_S]) {
            rectangle.y += 3 + (zoomRelativeMoveSpeed * 15);
        }
        if (state[SDL_SCANCODE_W]) {
            rectangle.y -= 3 + (zoomRelativeMoveSpeed * 15);
        }

        if (event.type == SDL_MOUSEWHEEL) {
            if (event.wheel.y > 0) { // Scroll Up (Zoom In)
                if (zoom < 2.0f) {
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
            else if (event.wheel.y < 0) { // Scroll Down (Zoom Out)
                if (zoom > 1.0f) {
                    zoom -= 0.1f;
                    zoomRelativeMoveSpeed += 0.5f;
                }
                else if (zoom > 0.25f) {
                    zoom -= 0.01f;
                    zoomRelativeMoveSpeed += 0.05f;
                }
            }
        }
    }
    else
    {
        if (state[SDL_SCANCODE_D] && (rectangle.x + GetScaledWidth()) < maxX) {
            rectangle.x += 3 + (zoomRelativeMoveSpeed * 15);
            
        }

        if (state[SDL_SCANCODE_A] && rectangle.x > minX) {
            rectangle.x -= 3 + (zoomRelativeMoveSpeed * 15);
        }
        if (state[SDL_SCANCODE_S] && (rectangle.y + GetScaledHeight()) < maxY) {
            rectangle.y += 3 + (zoomRelativeMoveSpeed * 15);
        }
        if (state[SDL_SCANCODE_W] && rectangle.y > minY) {
            rectangle.y -= 3 + (zoomRelativeMoveSpeed * 15);
        }

        if (event.type == SDL_MOUSEWHEEL) {
            if (event.wheel.y > 0) { // Scroll Up (Zoom In)
                if (zoom < 2.0f) {
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
            else if (event.wheel.y < 0) { // Scroll Down (Zoom Out)
                if (zoom > 1.0f) {
                    zoom -= 0.1f;
                    zoomRelativeMoveSpeed += 0.5f;
                }
                else if (zoom > 0.25f) {
                    zoom -= 0.01f;
                    zoomRelativeMoveSpeed += 0.05f;
                }
            }
        }
    }

}



SDL_Rect Camera::CalcScreenPosition(const SDL_Rect& rect) {
    SDL_Rect r{ 0,0,rect.w,rect.h };
    r.x = rect.x - rectangle.x;
    r.y = rect.y - rectangle.y;
    return r;
}

SDL_Rect Camera::CalcScreenPositionWithZoom(const SDL_Rect& rect) {
    SDL_Rect r{0, 0, static_cast<int>(rect.w * zoom) + 1,static_cast<int>(rect.h * zoom) + 1}; // +1 to prevent white lines
    r.x = static_cast<int>((rect.x - rectangle.x) * zoom);
    r.y = static_cast<int>((rect.y - rectangle.y) * zoom);
    return r;
}

Point Camera::RecoverPosition(int x, int y) {
    return { x + rectangle.x,y + rectangle.y };
}

Point Camera::RecoverZoomPosition(int x, int y) {
    return {
        static_cast<int>(x / zoom + rectangle.x),
        static_cast<int>(y / zoom + rectangle.y)
    };
}

int Camera::GetScaledWidth() {
    return static_cast<int>(rectangle.w / zoom);
}

int Camera::GetScaledHeight() {
    return static_cast<int>(rectangle.h / zoom);
}

Camera::~Camera() {
}

