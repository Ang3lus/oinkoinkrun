#pragma once
#include "scene.h"
#include "graphics/scrolling_background.h"
#include <vector>

namespace oinkoinkrun::scenes {
    class MainMenu : public Scene {
    public:
        MainMenu(oinkoinkrun::Game& game);

        void handle_input(const events::Events::Event &event) override;
        void render() override;
        void update(float dt) override;
    private:
        std::vector<graphics::ScrollingBackground> scrolling_backgrounds_;
    };
}

