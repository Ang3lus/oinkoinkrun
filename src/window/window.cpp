#include "window.h"
#include <iostream>
#include <filesystem>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace {
    SDL_Rect sdl_rect_from_pair(const std::pair<glm::ivec2, glm::ivec2>& src) {

        return {
            .x = src.first.x,
            .y = src.first.y,
            .w = src.second.x,
            .h = src.second.y,
        };
    }
}

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

        window_ = std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>>(
                SDL_CreateWindow( "Oink Oink run", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_HIDDEN),
                [](SDL_Window* window) {
                    SDL_DestroyWindow(window);
                });

        if (!window_) {
            std::cerr << SDL_GetError() << std::endl;
            throw std::runtime_error("Cannot create window_");
        }

        renderer_ = std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer*)>>(
                SDL_CreateRenderer(window_.get(), -1, 0),
                [](SDL_Renderer* renderer) {
                    SDL_DestroyRenderer(renderer);
                });

        if (!renderer_) {
            std::cerr << SDL_GetError() << std::endl;
            throw std::runtime_error("Cannot create renderer_");
        }
    }

    Window::~Window() {
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
    }

    oinkoinkrun::graphics::Image::Id Window::load_image(const std::filesystem::path &path) {
        oinkoinkrun::graphics::Image::Id id;
        std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture*)>> image = {IMG_LoadTexture(
            renderer_.get(),
            path.c_str()),
            [](SDL_Texture* texture) {
                SDL_DestroyTexture(texture);
            }};

        if (!image) {
            std::cerr << SDL_GetError() << std::endl;
            throw std::runtime_error("Cannot load image");
        }

        images_.emplace(id, std::move(image));

        return id;
    }

    void Window::show() {
        std::cout << "Window::show" << std::endl;
        SDL_ShowCursor(SDL_DISABLE);
        SDL_ShowWindow(window_.get());
    }

    void Window::clear() {
        SDL_RenderClear(renderer_.get());
    }

    void Window::render(const graphics::Image::Id& id,
                        const std::optional<std::pair<glm::ivec2, glm::ivec2>>& src_rect,
                        const std::optional<std::pair<glm::ivec2, glm::ivec2>>& dst_rect) {
        std::unique_ptr<SDL_Rect> src_sdl_rect;
        std::unique_ptr<SDL_Rect> dst_sdl_rect;

        if (src_rect) {
            src_sdl_rect = std::make_unique<SDL_Rect>(sdl_rect_from_pair(*src_rect));
        }

        if (dst_rect) {
            dst_sdl_rect = std::make_unique<SDL_Rect>(sdl_rect_from_pair(*dst_rect));
        }
        if (SDL_RenderCopy(renderer_.get(), images_[id].get(), src_sdl_rect.get(), dst_sdl_rect.get())) {
            std::cerr << SDL_GetError() << std::endl;
            throw std::runtime_error("Cannot render image");
        }
    }

    void Window::refresh() {
        SDL_RenderPresent(renderer_.get());
    }
}
