#pragma once
#include "events/events.h"
#include "window/window.h"

namespace oinkoinkrun {
    class Game {
    public:
        Game();
        void start();
    private:
        events::Events events;
        window::Window window;
    };
}