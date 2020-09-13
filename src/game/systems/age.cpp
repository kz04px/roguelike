#include "../components/age.hpp"
#include <cprof/profiler.hpp>
#include "../game.hpp"

using namespace components;

void Game::s_age() {
    auto t = cprof::Timer(__PRETTY_FUNCTION__);

    auto entities = m_ecs.entities<Age>();
    for (const auto &e : entities) {
        auto &a = m_ecs.get<Age>(e);
        a.m_current++;

        if (a.m_current >= a.m_max) {
            m_ecs.remove(e);
        }
    }
}
