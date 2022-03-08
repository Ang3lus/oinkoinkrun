#pragma once

#include "common/id.h"
#include <glm/vec2.hpp>
#include <cstddef>

namespace oinkoinkrun::graphics {
    class Image {
    public:
        using Id = common::Id<Image>;
        Image(Id id, glm::ivec2 size);
        Id id() const;
        glm::ivec2 size() const;
    private:
        Id id_;
        glm::ivec2 size_;
    };
}
