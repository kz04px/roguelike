#include <cprof/profiler.hpp>
#include "../../inputs.hpp"
#include "../components/player_input.hpp"
#include "../game.hpp"

using namespace components;

void Game::s_input() {
    auto t = cprof::Timer(__PRETTY_FUNCTION__);

    auto entities = ecs_.entities<PlayerInput>();
    for (const auto &e : entities) {
        auto &i = ecs_.get<PlayerInput>(e);

        // Movement
        i.left_ = Inputs::get()->get_key(KeyType::Key_A) == KeyState::Down;
        i.right_ = Inputs::get()->get_key(KeyType::Key_D) == KeyState::Down;
        i.up_ = Inputs::get()->get_key(KeyType::Key_W) == KeyState::Down;
        i.down_ = Inputs::get()->get_key(KeyType::Key_S) == KeyState::Down;
        // Other
        i.use_ = Inputs::get()->get_key(KeyType::Key_F) == KeyState::Down;
    }
}
