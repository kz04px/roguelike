#include "../components/timer.hpp"
#include <cprof/profiler.hpp>
#include "../game.hpp"

using namespace components;

void Game::s_timer() {
    auto ti = cprof::Timer(__PRETTY_FUNCTION__);

    auto entities = m_ecs.entities<Timer>();
    for (const auto &e : entities) {
        auto &t = m_ecs.get<Timer>(e);
        t.m_time_left--;

        if (t.m_time_left <= 0) {
            m_ecs.remove(e);
        }
    }
}
