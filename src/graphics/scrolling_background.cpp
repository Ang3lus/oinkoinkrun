#include "scrolling_background.h"
#include "window/window.h"

namespace {
    glm::ivec2 fit_image_size_to_window_height(const oinkoinkrun::graphics::Image& image,
                                               const oinkoinkrun::window::Window &window) {
        const auto& rendering_surface_size = window.rendering_surface_size();

        float height_ratio = rendering_surface_size.y;
        const auto& image_size = image.size();
        height_ratio /= image_size.y;

        glm::ivec2 final_rendering_size = rendering_surface_size;
        final_rendering_size.x = image_size.x * height_ratio;

        return final_rendering_size;
    }
}

namespace oinkoinkrun::graphics {
    ScrollingBackground::ScrollingBackground(Image image, std::size_t scrolling_speed)
        : image_{std::move(image)},
          scrolling_speed_{scrolling_speed} {}

    void ScrollingBackground::render(window::Window &window) const {
        const auto& final_rendering_size = fit_image_size_to_window_height(image_, window);

        window.render(image_.id(), {{{0, 0}, image_.size()}}, {{{x_pos, 0}, final_rendering_size}});
        window.render(image_.id(), {{{0, 0}, image_.size()}},
                      {{{x_pos + final_rendering_size.x, 0}, final_rendering_size}});
    }

    void ScrollingBackground::update(float dt, const window::Window &window) {
        const auto& final_rendering_size = fit_image_size_to_window_height(image_, window);

        x_pos -= scrolling_speed_ * dt;

        if (-x_pos >= final_rendering_size.x) {
            x_pos = 0;
        }
    }
}