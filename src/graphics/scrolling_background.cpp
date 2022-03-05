#include "scrolling_background.h"

namespace oinkoinkrun::graphics {
    ScrollingBackground::ScrollingBackground(Image::Id id, std::size_t scrolling_speed)
        : images_id_(id),
          scrolling_speed_(scrolling_speed) {}

    Image::Id ScrollingBackground::image_id() const {
        return images_id_;
    }
}