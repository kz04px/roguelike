#include "../components/timer.hpp"
#include <cprof/profiler.hpp>
#include "../game.hpp"

using namespace components;

void Game::s_timer() {
    auto ti = cprof::Timer(__PRETTY_FUNCTION__);

    auto entities = ecs_.entities<Timer>();
    for (const auto &e : entities) {
        auto &t = ecs_.get<Timer>(e);
        t.time_left_--;

        if (t.time_left_ <= 0) {
            ecs_.remove(e);
        }
    }
}
