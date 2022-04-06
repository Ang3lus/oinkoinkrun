#include "game.h"
#include "scenes/mainmenu.h"
#include <iostream>
#include <chrono>
#include <functional>

namespace oinkoinkrun {
    Game::Game() : active_scene_{typeid(scenes::MainMenu)} {
        std::cout << "Game::Game" << std::endl;
        scenes_.emplace(typeid(scenes::MainMenu), std::make_unique<scenes::MainMenu>(*this));
    }

    void Game::start() {
        run_ = true;

        std::cout << "Game::start" << std::endl;
        window_.show();

        float dt = 0;
        auto prev_tick = std::chrono::steady_clock::now();
        auto next_tick = prev_tick;
        while(run_) {
            dt = std::chrono::duration<float>(next_tick - prev_tick).count();
            prev_tick = next_tick;

            handle_input();
            render();
            update(dt);

            next_tick = std::chrono::steady_clock::now();
        }
    }

    void Game::stop() {
        run_ = false;
    }

    window::Window& Game::window() {
        return window_;
    }

    void Game::handle_input() {
        events_.poll(std::bind(&scenes::Scene::handle_input, scenes_.at(active_scene_).get(), std::placeholders::_1));
    }

    void Game::render() {
        scenes_.at(active_scene_)->render();
    }

    void Game::update(float dt) {
        scenes_.at(active_scene_)->update(dt);
    }
}