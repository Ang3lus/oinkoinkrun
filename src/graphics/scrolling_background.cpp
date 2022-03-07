#include "scrolling_background.h"
#include "window/window.h"

namespace oinkoinkrun::graphics {
    ScrollingBackground::ScrollingBackground(Image::Id id, std::size_t scrolling_speed)
        : image_id_(id),
          scrolling_speed_(scrolling_speed) {}

    void ScrollingBackground::render(window::Window &window) const {

        window.render(image_id_, {{{100, 100}, {300, 300}}}, {{{100, 100}, {300, 300}}});
    }
}