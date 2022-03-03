#include "events.h"
#include <iostream>
#include <SDL2/SDL.h>

namespace oinkoinkrun::events {
    Events::Events() {
        std::cout << "Events::Events" << std::endl;
        if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0) {
            std::cerr << SDL_GetError() << std::endl;
            throw std::runtime_error("Events initialization failed");
        }
    }

    Events::~Events() {
        SDL_QuitSubSystem(SDL_INIT_EVENTS);
    }

    void Events::poll(const std::function<void(const Event&)>& callback) {
        SDL_Event sdl_event;
        while (SDL_PollEvent(&sdl_event)) {
            switch(sdl_event.type) {
                case SDL_KEYDOWN:
                    Event::Key key;
                    key.type = Event::Key::Type::Press;
                    switch(sdl_event.key.keysym.sym) {
                        case SDL_KeyCode::SDLK_ESCAPE:
                            key.code = Event::Key::Code::Escape;
                    }
                    callback(key);
                    break;
            }
        }
    }
}
