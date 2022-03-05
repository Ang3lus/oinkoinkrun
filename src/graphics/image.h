#pragma once

#include "common/id.h"
#include <cstddef>

namespace oinkoinkrun::graphics {
    class Image {
    public:
        using Id = common::Id<Image>;
        Id id() const;
    private:
        Id id_;

    };
}
