#include "scene.h"

namespace oinkoinkrun::scenes {
    Scene::Scene(oinkoinkrun::Game& game) : game_(game) {};

    oinkoinkrun::Game &Scene::game() {
        return game_;
    }

    const oinkoinkrun::Game &Scene::game() const {
        return game_;
    }
}