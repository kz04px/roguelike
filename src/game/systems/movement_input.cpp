#include <cprof/profiler.hpp>
#include "../../render/renderer.hpp"
#include "../components/movement.hpp"
#include "../components/player_input.hpp"
#include "../game.hpp"

using namespace components;

void Game::s_movement_input() {
    auto t = cprof::Timer(__PRETTY_FUNCTION__);

    auto entities = ecs_.entities<Movement, PlayerInput>();
    for (const auto &e : entities) {
        auto &m = ecs_.get<Movement>(e);
        auto &p = ecs_.get<PlayerInput>(e);

        m.left_ = p.left_;
        m.right_ = p.right_;
        m.up_ = p.up_;
        m.down_ = p.down_;
    }
}
