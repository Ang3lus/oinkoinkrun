#pragma once
#include "events/events.h"
#include "window/window.h"
#include "graphics/scrolling_background.h"

namespace oinkoinkrun {
    class Game {
    public:
        Game();
        void start();
    private:
        events::Events events_;
        window::Window window_;
        std::vector<graphics::ScrollingBackground> scrolling_backgrounds_;
    };
}