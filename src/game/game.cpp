#include "game.hpp"
#include <cassert>
#include <cprof/profiler.hpp>
// Events
#include <events/event.hpp>
#include <events/keyboard-event.hpp>
#include <events/mouse-event.hpp>
#include <events/window-event.hpp>
// Rendering
#include "../render/renderer.hpp"
// Components
#include "components/age.hpp"
#include "components/flammable.hpp"
#include "components/health.hpp"
#include "components/movement.hpp"
#include "components/player_input.hpp"
#include "components/position.hpp"
#include "components/render.hpp"
#include "components/spellbook.hpp"
#include "components/timer.hpp"

const int components::Position::id = 0;
const int components::Render::id = 1;
const int components::Age::id = 2;
const int components::PlayerInput::id = 3;
const int components::Movement::id = 4;
const int components::Flammable::id = 5;
const int components::Timer::id = 6;
const int components::Spellbook::id = 7;
const int components::Health::id = 8;

Game::Game(std::shared_ptr<Renderer> r)
    : ecs_{},
      frame_{0},
      renderer_{r},
      tile_map_{},
      spell_manager_{},
      camera_{0, 0, 32, 32} {
    assert(r);
    auto t = cprof::Timer(__PRETTY_FUNCTION__);

    // Register components
    ecs_.reg<components::Position>();
    ecs_.reg<components::Render>();
    ecs_.reg<components::Age>();
    ecs_.reg<components::PlayerInput>();
    ecs_.reg<components::Movement>();
    ecs_.reg<components::Flammable>();
    ecs_.reg<components::Timer>();
    ecs_.reg<components::Spellbook>();
    ecs_.reg<components::Health>();

    // Check components
    assert(ecs_.registered<components::Position>());
    assert(ecs_.registered<components::Render>());
    assert(ecs_.registered<components::Age>());
    assert(ecs_.registered<components::PlayerInput>());
    assert(ecs_.registered<components::Movement>());
    assert(ecs_.registered<components::Flammable>());
    assert(ecs_.registered<components::Timer>());
    assert(ecs_.registered<components::Spellbook>());
    assert(ecs_.registered<components::Health>());
}

void Game::step() {
    auto t = cprof::Timer(__PRETTY_FUNCTION__);

    s_input();
    s_movement_input();
    s_movement();
    s_fire();
    s_age();
    s_timer();
    s_spells();
    s_health();
    s_camera();
    ecs_.update();
    frame_++;
}

void Game::render() {
    auto t = cprof::Timer(__PRETTY_FUNCTION__);

    s_render();
    s_render_debug();
}

void Game::load() {
    auto timer = cprof::Timer(__PRETTY_FUNCTION__);

    // Create spells
    spell_manager_.add(Spell{"Fire Aura", 1});

    // Create player
    {
        auto e = ecs_.create();
        ecs_.add<components::Position>(e, 2, 2);
        ecs_.add<components::Render>(e, 25, 0);
        ecs_.add<components::PlayerInput>(e);
        ecs_.add<components::Movement>(e);
        ecs_.add<components::Spellbook>(e);
        ecs_.add<components::Health>(e, 100);
    }

    // Create trees
    {
        const std::pair<int, int> tiles[] = {
            {0, 1},
            {1, 1},
            {2, 1},
            {3, 1},
            {4, 1},
            {5, 1},
            {3, 2},
            {4, 2},
        };
        for (int i = 0; i < 2048; ++i) {
            const int x = rand() % 128 - 64;
            const int y = rand() % 128 - 64;
            const auto t = tiles[rand() % 8];
            auto e = ecs_.create();
            ecs_.add<components::Position>(e, x, y);
            ecs_.add<components::Render>(e, t.first, t.second);
            ecs_.add<components::Health>(e, 10);
            ecs_.add<components::Flammable>(e, false);
        }
    }

    // Create plants
    {
        const std::pair<int, int> tiles[] = {
            {5, 0},
            {6, 0},
            {7, 0},
            {0, 2},
            {1, 2},
            {2, 2},
            {6, 2},
            {7, 2},
        };
        for (int i = 0; i < 1024; ++i) {
            const int x = rand() % 128 - 64;
            const int y = rand() % 128 - 64;
            const auto t = tiles[rand() % 8];
            auto e = ecs_.create();
            ecs_.add<components::Position>(e, x, y);
            ecs_.add<components::Render>(e, t.first, t.second);
            ecs_.add<components::Health>(e, 2);
            ecs_.add<components::Flammable>(e, false);
        }
    }

    // Create rocks
    {
        for (int i = 0; i < 1024; ++i) {
            const int x = rand() % 128 - 64;
            const int y = rand() % 128 - 64;
            auto e = ecs_.create();
            ecs_.add<components::Position>(e, x, y);
            ecs_.add<components::Render>(e, 5, 2);
        }
    }

    // Create Litter
    {
        const std::pair<int, int> tiles[] = {
            {0, 15},
            {1, 15},
            {1, 0},
            {2, 0},
            {3, 0},
            {4, 0},
        };
        for (int i = 0; i < 256; ++i) {
            const int x = rand() % 128 - 64;
            const int y = rand() % 128 - 64;
            const auto t = tiles[rand() % 2];
            auto e = ecs_.create();
            ecs_.add<components::Position>(e, x, y);
            ecs_.add<components::Render>(e, t.first, t.second);
        }
    }
}

void Game::on_key_press(Event &e) {
    step();
}

void Game::on_key_release(Event &e) {
}

void Game::on_window_close(Event &e) {
}

void Game::on_window_resize(Event &e) {
}

void Game::on_event(Event &e) {
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
}
