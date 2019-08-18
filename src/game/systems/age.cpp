#include "../components/age.hpp"
#include <cprof/profiler.hpp>
#include "../game.hpp"

using namespace components;

void Game::s_age() {
    auto t = cprof::Timer(__PRETTY_FUNCTION__);

    auto entities = ecs_.entities<Age>();
    for (const auto &e : entities) {
        auto &a = ecs_.get<Age>(e);
        a.current_++;

        if (a.current_ >= a.max_) {
            ecs_.remove(e);
        }
    }
}
