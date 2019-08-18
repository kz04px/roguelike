#include "../components/health.hpp"
#include <cprof/profiler.hpp>
#include "../components/flammable.hpp"
#include "../game.hpp"

using namespace components;

void Game::s_health() {
    auto t = cprof::Timer(__PRETTY_FUNCTION__);

    auto entities = ecs_.entities<Health, Flammable>();
    for (const auto &e : entities) {
        auto &f = ecs_.get<Flammable>(e);

        if (f.on_fire) {
            auto &h = ecs_.get<Health>(e);
            h.current_--;
            if (h.current_ <= 0) {
                ecs_.remove(e);
            }
        }
    }
}
