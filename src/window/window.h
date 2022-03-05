#pragma once
#include "graphics/image.h"
#include <functional>
#include <memory>
#include <filesystem>
#include <unordered_map>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

namespace oinkoinkrun::window {
    class Window final {
    public:
        Window();
        ~Window();

        graphics::Image::Id load_image(const std::filesystem::path& path);

        void show();
        void clear();
        void render(const graphics::Image::Id& id);
        void refresh();
    private:
        std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>> window_;
        std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer*)>> renderer_;
        std::unordered_map<graphics::Image::Id, std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture*)>>,
            graphics::Image::Id::Hash> images_;
    };
}