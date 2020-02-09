#include "application.hpp"
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <clog/clog.hpp>
#include <cprof/profiler.hpp>
#include <events/event.hpp>
#include <events/keyboard-event.hpp>
#include <events/mouse-event.hpp>
#include <events/window-event.hpp>
#include <unordered_map>
#include "inputs.hpp"
#include "render/renderer.hpp"
#include "window.hpp"

static const std::unordered_map<SDL_Keycode, KeyType> key_lut = {
    {SDLK_a, KeyType::Key_A},        {SDLK_b, KeyType::Key_B},
    {SDLK_c, KeyType::Key_C},        {SDLK_d, KeyType::Key_D},
    {SDLK_e, KeyType::Key_E},        {SDLK_f, KeyType::Key_F},
    {SDLK_g, KeyType::Key_G},        {SDLK_h, KeyType::Key_H},
    {SDLK_i, KeyType::Key_I},        {SDLK_j, KeyType::Key_J},
    {SDLK_k, KeyType::Key_K},        {SDLK_l, KeyType::Key_L},
    {SDLK_m, KeyType::Key_M},        {SDLK_n, KeyType::Key_N},
    {SDLK_o, KeyType::Key_O},        {SDLK_p, KeyType::Key_P},
    {SDLK_q, KeyType::Key_Q},        {SDLK_r, KeyType::Key_R},
    {SDLK_s, KeyType::Key_S},        {SDLK_t, KeyType::Key_T},
    {SDLK_u, KeyType::Key_U},        {SDLK_v, KeyType::Key_V},
    {SDLK_w, KeyType::Key_W},        {SDLK_x, KeyType::Key_X},
    {SDLK_y, KeyType::Key_Y},        {SDLK_z, KeyType::Key_Z},
    {SDLK_ESCAPE, KeyType::Key_ESC},
};

Application::Application() : quit_{false} {
    clog::Log::get()->info("Application constructor");

    {
        auto flags = SDL_INIT_EVERYTHING;
        auto n = SDL_Init(SDL_INIT_EVERYTHING);
        if (n) {
            clog::Log::get()->error("SDL_Init failed: ", flags);
            throw std::exception();
        }
        clog::Log::get()->info("SDL initialised: ", flags);
    }

    {
        auto flags = IMG_INIT_PNG;
        auto n = IMG_Init(flags);
        if (n != flags) {
            clog::Log::get()->error("IMG_Init failed: ", flags);
            throw std::exception();
        }
        clog::Log::get()->info("SDL IMG initialised: ", flags);
    }

    window_ = std::make_unique<Window>("Roguelike", 512, 512);
    renderer_ = std::shared_ptr<Renderer>(new Renderer(window_->renderer()));
    game_ = std::make_unique<Game>(renderer_);

    // Prepare renderer
    renderer_->load_texture(0, "./assets/colored_transparent.png");

    // Prepare game
    game_->load();
}

Application::~Application() {
    clog::Log::get()->info("Application destructor");
    IMG_Quit();
    SDL_Quit();

    // Write profiling
    cprof::Profiler::get()->write("profile.csv");
}

void Application::on_key_press(KeyPressEvent &e) {
    Inputs::get()->set_key(e.key(), KeyState::Down);
}

void Application::on_key_release(KeyReleaseEvent &e) {
    Inputs::get()->set_key(e.key(), KeyState::Up);
}

void Application::on_window_close(WindowCloseEvent &e) {
}

void Application::on_window_resize(WindowResizeEvent &e) {
    window_->resize(e.width(), e.height());
}

void Application::on_event(Event &e) {
    switch (e.type()) {
        case EventType::KeyPressEvent:
            on_key_press(static_cast<KeyPressEvent &>(e));
            break;
        case EventType::KeyReleaseEvent:
            on_key_release(static_cast<KeyReleaseEvent &>(e));
            break;
        case EventType::WindowCloseEvent:
            on_window_close(static_cast<WindowCloseEvent &>(e));
            break;
        case EventType::WindowResizeEvent:
            on_window_resize(static_cast<WindowResizeEvent &>(e));
            break;
        default:
            break;
    }

    // Event is done with, no need to pass further
    if (e.handled_) {
        return;
    }

    // Pass along to the game
    game_->on_event(e);
}

void Application::run() {
    auto t = cprof::Timer(__PRETTY_FUNCTION__);

    while (!quit_) {
        // Handle SDL events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit_ = true;
                    break;
                case SDL_KEYDOWN: {
                    const auto key = key_lut.find(event.key.keysym.sym);
                    if (key != key_lut.end()) {
                        auto e = KeyPressEvent(key->second, 0, 0);
                        on_event(e);
                    }
                    break;
                }
                case SDL_KEYUP: {
                    const auto key = key_lut.find(event.key.keysym.sym);
                    if (key != key_lut.end()) {
                        auto e = KeyReleaseEvent(key->second, 0, 0);
                        on_event(e);
                    }
                    break;
                }
                case SDL_MOUSEBUTTONDOWN:
                    break;
                case SDL_WINDOWEVENT:
                    switch (event.window.event) {
                        case SDL_WINDOWEVENT_RESIZED: {
                            auto e = WindowResizeEvent(event.window.data1,
                                                       event.window.data2);
                            on_event(e);
                            break;
                        }
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }

        // Clear
        renderer_->clear();

        // Render game
        game_->render();
        renderer_->render();

        // Swap
        window_->swap();

        // Wait
        SDL_Delay(16);
    }
}
