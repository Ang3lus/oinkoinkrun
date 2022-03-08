#pragma once
#include "image.h"

namespace oinkoinkrun::window {
    class Window;
}

namespace oinkoinkrun::graphics {
    class ScrollingBackground final {
    public:
        ScrollingBackground(Image image, std::size_t scrolling_speed);
        void render(window::Window& window) const;
        void update(float dt, const window::Window &window);
    private:
        Image image_;
        std::size_t scrolling_speed_;
        float x_pos = 0;
    };
}
