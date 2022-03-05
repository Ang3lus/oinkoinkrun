#pragma once
#include "image.h"

namespace oinkoinkrun::graphics {
    class ScrollingBackground final {
    public:
        ScrollingBackground(Image::Id id, std::size_t scrolling_speed);
        Image::Id image_id() const;
    private:
        Image::Id images_id_;
        std::size_t scrolling_speed_;
    };
}
