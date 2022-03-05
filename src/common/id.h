#pragma once

#include <cstddef>

namespace oinkoinkrun::common {

template<class T>
class Id {
public:
    struct Hash {
        std::size_t operator()(const Id& id) const {
            return id.id_;
        }
    };
    Id() {
        static std::size_t new_id = 0;
        id_ = ++new_id;
    }

    bool operator==(const Id& rhs) const {
        return id_ == rhs.id_;
    }
private:
    std::size_t id_;
};
}
