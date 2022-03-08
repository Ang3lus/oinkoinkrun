#pragma once
#include "graphics/image.h"
#include <glm/vec2.hpp>
#include <optional>
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

        graphics::Image load_image(const std::filesystem::path& path);

        void show();
        void clear();
        void render(const graphics::Image::Id& id,
                    const std::optional<std::pair<glm::ivec2, glm::ivec2>>& src_rect = std::nullopt,
                    const std::optional<std::pair<glm::ivec2, glm::ivec2>>& dst_rect = std::nullopt);
        void refresh();
        glm::ivec2 rendering_surface_size() const;
    private:
        std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>> window_;
        std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer*)>> renderer_;
        std::unordered_map<graphics::Image::Id, std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture*)>>,
            graphics::Image::Id::Hash> images_;
    };
}