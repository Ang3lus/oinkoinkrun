#include "mainmenu.h"
#include "game.h"
#include <filesystem>
#include <iostream>

namespace oinkoinkrun::scenes {
    MainMenu::MainMenu(oinkoinkrun::Game& game) : Scene(game) {
        scrolling_backgrounds_.emplace_back(
                game.window().load_image(
                        std::filesystem::path("src") / "assets" / "graphics" / "background" / "layer-1-sky.png"),
                10);
        scrolling_backgrounds_.emplace_back(
                game.window().load_image(
                        std::filesystem::path("src") / "assets" / "graphics" / "background" / "layer-2-mountain.png"),
                25);
        scrolling_backgrounds_.emplace_back(
                game.window().load_image(
                        std::filesystem::path("src") / "assets" / "graphics" / "background" / "layer-3-ground.png"),
                50);
    }

    void MainMenu::handle_input(const events::Events::Event &event) {
        std::visit([&](const auto& data) {
            if constexpr(std::is_same_v<std::decay_t<decltype(data)>, events::Events::Event::Key>) {
                switch (data.code) {
                    case events::Events::Event::Key::Code::Escape: {
                        if (data.type == events::Events::Event::Key::Type::Press) {
                            std::cout << "ESC quit" << std::endl;
                            game().stop();
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
        }, event.data);
    }

    void MainMenu::render() {
        game().window().clear();

        for (const auto& scrolling_background: scrolling_backgrounds_) {
            scrolling_background.render(game().window());
        }
        game().window().refresh();
    }

    void MainMenu::update(float dt) {
        for (auto& scrolling_background: scrolling_backgrounds_) {
            scrolling_background.update(dt, game().window());
        }
    }
}
