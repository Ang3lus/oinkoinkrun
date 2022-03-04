#include "window.h"
#include <iostream>
#include <filesystem>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace oinkoinkrun::window {
    Window::Window() {
        std::cout << "Window::Window" << std::endl;
        if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
            std::cerr << SDL_GetError() << std::endl;
            throw std::runtime_error("Video initialization failed");
        }

        if (IMG_Init(IMG_INIT_PNG) ^ IMG_INIT_PNG) {
            std::cerr << SDL_GetError() << std::endl;
            throw std::runtime_error("Img initialization failed");
        }

        window = std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>>(
                SDL_CreateWindow( "Oink Oink run", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, SDL_WINDOW_HIDDEN),
                [](SDL_Window* window) {
                    SDL_DestroyWindow(window);
                });

        if (!window) {
            std::cerr << SDL_GetError() << std::endl;
            throw std::runtime_error("Cannot create window");
        }

        renderer = std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer*)>>(
                SDL_CreateRenderer(window.get(), -1, 0),
                [](SDL_Renderer* renderer) {
                    SDL_DestroyRenderer(renderer);
                });

        if (!renderer) {
            std::cerr << SDL_GetError() << std::endl;
            throw std::runtime_error("Cannot create renderer");
        }
    }

    Window::~Window() {
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
    }

    void Window::show() {
        std::cout << "Window::show" << std::endl;
        SDL_ShowWindow(window.get());
    }

    void Window::clear() {
        SDL_RenderClear(renderer.get());
    }

    void Window::render() {
        SDL_Texture* texture = IMG_LoadTexture(
                renderer.get(),
                (std::filesystem::path("src") / "assets" / "graphics" / "background" / "layer-1-sky.png").c_str());
        if (!texture) {
            std::cerr << SDL_GetError() << std::endl;
            throw std::runtime_error("Cannot load image");
        }
        SDL_RenderCopy(renderer.get(), texture, NULL, NULL);
        SDL_DestroyTexture(texture);
    }

    void Window::refresh() {
        SDL_RenderPresent(renderer.get());
    }
}
