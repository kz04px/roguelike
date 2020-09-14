#include "game.hpp"
#include <cassert>
#include <cprof/profiler.hpp>
#include <noise/perlin.hpp>
#include "chunk_manager.hpp"
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

[[nodiscard]] Tile generator(const int x, const int y) {
    auto n = noise::perlin::get(x / 16.0f, y / 16.0f, 0.0);
    if (n > 0.1) {
        return Tile(Terrain::Dirt);
    } else if (n > -0.3) {
        return Tile(Terrain::Stone);
    } else {
        return Tile(Terrain::Water);
    }
}

Game::Game(std::shared_ptr<Renderer> r)
    : m_ecs{},
      m_frame{0},
      m_renderer{r},
      m_tile_map{generator},
      m_spell_manager{},
      m_camera{0, 0, 32, 32} {
    assert(r);
    auto t = cprof::Timer(__PRETTY_FUNCTION__);

    // Register components
    m_ecs.reg<components::Position>();
    m_ecs.reg<components::Render>();
    m_ecs.reg<components::Age>();
    m_ecs.reg<components::PlayerInput>();
    m_ecs.reg<components::Movement>();
    m_ecs.reg<components::Flammable>();
    m_ecs.reg<components::Timer>();
    m_ecs.reg<components::Spellbook>();
    m_ecs.reg<components::Health>();

    // Check components
    assert(m_ecs.registered<components::Position>());
    assert(m_ecs.registered<components::Render>());
    assert(m_ecs.registered<components::Age>());
    assert(m_ecs.registered<components::PlayerInput>());
    assert(m_ecs.registered<components::Movement>());
    assert(m_ecs.registered<components::Flammable>());
    assert(m_ecs.registered<components::Timer>());
    assert(m_ecs.registered<components::Spellbook>());
    assert(m_ecs.registered<components::Health>());
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
    m_ecs.update();
    m_frame++;
}

void Game::render() {
    auto t = cprof::Timer(__PRETTY_FUNCTION__);

    s_render();
    s_render_debug();
}

void Game::load() {
    auto timer = cprof::Timer(__PRETTY_FUNCTION__);

    // Create spells
    m_spell_manager.add(Spell{"Fire Aura", 1});

    // Create player
    {
        auto e = m_ecs.create();
        m_ecs.add<components::Position>(e, 2, 2);
        m_ecs.add<components::Render>(e, 25, 0);
        m_ecs.add<components::PlayerInput>(e);
        m_ecs.add<components::Movement>(e);
        m_ecs.add<components::Spellbook>(e);
        m_ecs.add<components::Health>(e, 100);
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
            auto e = m_ecs.create();
            m_ecs.add<components::Position>(e, x, y);
            m_ecs.add<components::Render>(e, t.first, t.second);
            m_ecs.add<components::Health>(e, 10);
            m_ecs.add<components::Flammable>(e, false);
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
            auto e = m_ecs.create();
            m_ecs.add<components::Position>(e, x, y);
            m_ecs.add<components::Render>(e, t.first, t.second);
            m_ecs.add<components::Health>(e, 2);
            m_ecs.add<components::Flammable>(e, false);
        }
    }

    // Create rocks
    {
        for (int i = 0; i < 1024; ++i) {
            const int x = rand() % 128 - 64;
            const int y = rand() % 128 - 64;
            auto e = m_ecs.create();
            m_ecs.add<components::Position>(e, x, y);
            m_ecs.add<components::Render>(e, 5, 2);
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
            auto e = m_ecs.create();
            m_ecs.add<components::Position>(e, x, y);
            m_ecs.add<components::Render>(e, t.first, t.second);
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
