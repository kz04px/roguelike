#include <cprof/profiler.hpp>
#include "../../render/renderer.hpp"
#include "../components/movement.hpp"
#include "../components/player_input.hpp"
#include "../game.hpp"

using namespace components;

void Game::s_movement_input() {
    auto t = cprof::Timer(__PRETTY_FUNCTION__);

    auto entities = m_ecs.entities<Movement, PlayerInput>();
    for (const auto &e : entities) {
        auto &m = m_ecs.get<Movement>(e);
        auto &p = m_ecs.get<PlayerInput>(e);

        m.m_left = p.m_left;
        m.m_right = p.m_right;
        m.m_up = p.m_up;
        m.m_down = p.m_down;
    }
}
