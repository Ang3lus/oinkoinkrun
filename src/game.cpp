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
                std::visit([&]<class T>(T&& arg) {
                    if constexpr(std::is_same_v<std::decay_t<T>, events::Events::Event::Key>) {
                        const auto& key = std::get<events::Events::Event::Key>(event.data);
                        switch (key.code) {
                            case events::Events::Event::Key::Code::Escape: {
                                std::cout << "ESC quit" << std::endl;
                                run = false;
                                break;
                            }
                            default:
                                break;
                        }
                    }
                }, event.data);
            });
        }
    }
}