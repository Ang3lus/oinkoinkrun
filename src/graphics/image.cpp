#include "image.h"
#include <utility>

namespace oinkoinkrun::graphics {
    Image::Image(Image::Id id, glm::ivec2 size): id_{std::move(id)}, size_{std::move(size)} {}

    Image::Id Image::id() const {
        return id_;
    }

    glm::ivec2 Image::size() const {
        return size_;
    }
}
