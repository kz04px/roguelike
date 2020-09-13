#include <cprof/profiler.hpp>
#include "../components/flammable.hpp"
#include "../components/position.hpp"
#include "../game.hpp"

using namespace components;

void Game::s_fire() {
    auto t = cprof::Timer(__PRETTY_FUNCTION__);

    auto entities = m_ecs.entities<Flammable, Position>();
    for (auto e1 = entities.begin(); e1 != entities.end(); ++e1) {
        auto &f1 = m_ecs.get<Flammable>(*e1);

        // Skip if not on fire
        if (!f1.m_on_fire) {
            continue;
        }

        auto &p1 = m_ecs.get<Position>(*e1);

        for (auto e2 = entities.begin(); e2 != entities.end(); ++e2) {
            if (e1 == e2) {
                continue;
            }

            auto &p2 = m_ecs.get<Position>(*e2);

            const int dx = std::abs(p1.m_x - p2.m_x);
            if (dx > 2) {
                continue;
            }

            const int dy = std::abs(p1.m_y - p2.m_y);
            if (dy > 2) {
                continue;
            }

            if (rand() % 50 == 0 || (dx == 0 && dy == 0)) {
                auto &f2 = m_ecs.get<Flammable>(*e2);
                f2.m_on_fire = true;
            }
        }
    }
}
