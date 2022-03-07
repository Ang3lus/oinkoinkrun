#pragma once
#include "image.h"

namespace oinkoinkrun::window {
    class Window;
}

namespace oinkoinkrun::graphics {
    class ScrollingBackground final {
    public:
        ScrollingBackground(Image::Id id, std::size_t scrolling_speed);
        void render(window::Window& window) const;
    private:
        Image::Id image_id_;
        std::size_t scrolling_speed_;
    };
}
