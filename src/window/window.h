#pragma once
#include <functional>
#include <memory>

struct SDL_Window;
struct SDL_Renderer;

namespace oinkoinkrun::window {
    class Window final {
    public:
        Window();
        ~Window();
        void show();
        void clear();
        void render();
        void refresh();
    private:
        std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>> window;
        std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer*)>> renderer;
    };
}