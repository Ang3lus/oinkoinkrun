#pragma once
#include <functional>
#include <memory>

struct SDL_Window;
struct SDL_Surface;

namespace oinkoinkrun::window {
    class Window final {
    public:
        Window();
        ~Window();
        void show();
    private:
        std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>> window;
        SDL_Surface* surface = nullptr;
    };
}