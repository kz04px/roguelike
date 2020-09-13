#include "../components/health.hpp"
#include <cprof/profiler.hpp>
#include "../components/flammable.hpp"
#include "../game.hpp"

using namespace components;

void Game::s_health() {
    auto t = cprof::Timer(__PRETTY_FUNCTION__);

    auto entities = m_ecs.entities<Health, Flammable>();
    for (const auto &e : entities) {
        auto &f = m_ecs.get<Flammable>(e);

        if (f.m_on_fire) {
            auto &h = m_ecs.get<Health>(e);
            h.m_current--;
            if (h.m_current <= 0) {
                m_ecs.remove(e);
            }
        }
    }
}
