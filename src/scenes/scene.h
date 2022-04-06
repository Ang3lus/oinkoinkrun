#pragma once
#include "events/events.h"

namespace oinkoinkrun {
    class Game;
}

namespace oinkoinkrun::scenes {
    class Scene {
    public:
        Scene(oinkoinkrun::Game&);
        virtual ~Scene() = default;
        virtual void handle_input(const events::Events::Event &event) = 0;
        virtual void render() = 0;
        virtual void update(float dt) = 0;

        oinkoinkrun::Game& game();
        const oinkoinkrun::Game& game() const;
    private:
        oinkoinkrun::Game& game_;
    };
}

