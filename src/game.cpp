#include "game.h"
#include "input/input.h"
#include <iostream>

namespace oinkoinkrun {
    Game::Game() {
        input::Input();
        std::cout << "Game::Game" << std::endl;
    }
}