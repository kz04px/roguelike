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

    auto entities = ecs_.entities<Spellbook, Position, PlayerInput>();
    for (const auto &e : entities) {
        auto &s = ecs_.get<Spellbook>(e);
        auto &p = ecs_.get<Position>(e);
        auto &pi = ecs_.get<PlayerInput>(e);

        if (pi.use_) {
            for (int i = 0; i < 5; ++i) {
                auto new_e = ecs_.create();
                ecs_.add<components::Position>(new_e, p.x_ + i + 1, p.y_);
                ecs_.add<components::Flammable>(new_e, true);
                ecs_.add<components::Timer>(new_e, 20);
            }
        }
    }
}
