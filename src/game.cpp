#include "game.h"
#include <iostream>
#include <chrono>

namespace oinkoinkrun {
    Game::Game() {
        std::cout << "Game::Game" << std::endl;
    }

    void Game::start() {
        std::cout << "Game::start" << std::endl;
        scrolling_backgrounds_.emplace_back(
                window_.load_image(
                        std::filesystem::path("src") / "assets" / "graphics" / "background" / "layer-1-sky.png"),
                10);
        scrolling_backgrounds_.emplace_back(
                window_.load_image(
                        std::filesystem::path("src") / "assets" / "graphics" / "background" / "layer-2-mountain.png"),
                25);
        scrolling_backgrounds_.emplace_back(
                window_.load_image(
                        std::filesystem::path("src") / "assets" / "graphics" / "background" / "layer-3-ground.png"),
                50);

        window_.show();

        bool run = true;
        float dt = 0;
        auto prev_tick = std::chrono::steady_clock::now();
        auto next_tick = prev_tick;
        while(run) {
            dt = std::chrono::duration<float>(next_tick - prev_tick).count();
            prev_tick = next_tick;
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
                scrolling_background.render(window_);
            }
            window_.refresh();

            for (auto& scrolling_background: scrolling_backgrounds_) {
                scrolling_background.update(dt, window_);
            }

            next_tick = std::chrono::steady_clock::now();
        }
    }
}