#include "game.h"
#include <iostream>

namespace oinkoinkrun {
    Game::Game() {
        window::Window();
        std::cout << "Game::Game" << std::endl;
    }

    void Game::start() {
        std::cout << "Game::start" << std::endl;
        window.show();

        bool run = true;
        while(run) {
            events.poll([&run](const events::Events::Event &event) {
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

            window.clear();
            window.render();
            window.refresh();
        }
    }
}