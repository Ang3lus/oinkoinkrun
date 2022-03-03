#include "window.h"
#include <iostream>
#include <SDL2/SDL.h>

namespace oinkoinkrun::window {
    Window::Window() {
        std::cout << "Window::Window" << std::endl;
        if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
            std::cerr << SDL_GetError() << std::endl;
            throw std::runtime_error("Window initialization failed");
        }

        window = std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>>(
                SDL_CreateWindow( "Oink Oink run", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, SDL_WINDOW_HIDDEN),
                [](SDL_Window* window) {
                    SDL_DestroyWindow(window);
                });
    }

    Window::~Window() {
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
    }

    void Window::show() {
        std::cout << "Window::show" << std::endl;
        SDL_ShowWindow(window.get());
    }
}
