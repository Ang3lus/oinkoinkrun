#pragma once
#include "events/events.h"
#include "window/window.h"
#include "scenes/scene.h"
#include <typeindex>

namespace oinkoinkrun {
    class Game final {
    public:
        Game();
        void start();
        void stop();
        window::Window& window();
    private:
        void handle_input();
        void render();
        void update(float dt);

        bool run_ = false;
        events::Events events_;
        window::Window window_;
        std::unordered_map<std::type_index, std::unique_ptr<scenes::Scene>> scenes_;
        std::type_index active_scene_;
    };
}