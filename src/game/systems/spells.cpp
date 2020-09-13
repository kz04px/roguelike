#include <cprof/profiler.hpp>
#include "../components/flammable.hpp"
#include "../components/player_input.hpp"
#include "../components/position.hpp"
#include "../components/spellbook.hpp"
#include "../components/timer.hpp"
#include "../game.hpp"

using namespace components;

void Game::s_spells() {
    auto t = cprof::Timer(__PRETTY_FUNCTION__);

    auto entities = m_ecs.entities<Spellbook, Position, PlayerInput>();
    for (const auto &e : entities) {
        auto &s = m_ecs.get<Spellbook>(e);
        auto &p = m_ecs.get<Position>(e);
        auto &pi = m_ecs.get<PlayerInput>(e);

        if (pi.m_use) {
            for (int i = 0; i < 5; ++i) {
                auto new_e = m_ecs.create();
                m_ecs.add<components::Position>(new_e, p.m_x + i + 1, p.m_y);
                m_ecs.add<components::Flammable>(new_e, true);
                m_ecs.add<components::Timer>(new_e, 20);
            }
        }
    }
}
