#include "game.h"
#include <iostream>

namespace oinkoinkrun {
    Game::Game() {
        std::cout << "Game::Game" << std::endl;
    }

    void Game::start() {
        std::cout << "Game::start" << std::endl;
        scrolling_backgrounds_.emplace_back(
                window_.load_image(
                        std::filesystem::path("src") / "assets" / "graphics" / "background" / "layer-1-sky.png"),
                1);
        scrolling_backgrounds_.emplace_back(
                window_.load_image(
                        std::filesystem::path("src") / "assets" / "graphics" / "background" / "layer-2-mountain.png"),
                1);
        scrolling_backgrounds_.emplace_back(
                window_.load_image(
                        std::filesystem::path("src") / "assets" / "graphics" / "background" / "layer-3-ground.png"),
                1);

        window_.show();

        bool run = true;
        while(run) {
            events_.poll([&run](const events::Events::Event &event) {
                std::visit([&run](const auto& data) {
                    if constexpr(std::is_same_v<std::decay_t<decltype(data)>, events::Events::Event::Key>) {
                        switch (data.code) {
                            case events::Events::Event::Key::Code::Escape: {
                                if (data.type == events::Events::Event::Key::Type::Press) {
                                    std::cout << "ESC quit" << std::endl;
                                    run = false;
                                }
                                break;
                            }
                            default:
                                break;
                        }
                    }
                }, event.data);
            });

            window_.clear();
            for (const auto& scrolling_background: scrolling_backgrounds_) {
                window_.render(scrolling_background.image_id());
            }
            window_.refresh();
        }
    }
}