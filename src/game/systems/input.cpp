#include <cprof/profiler.hpp>
#include "../../inputs.hpp"
#include "../components/player_input.hpp"
#include "../game.hpp"

using namespace components;

void Game::s_input() {
    auto t = cprof::Timer(__PRETTY_FUNCTION__);

    auto entities = m_ecs.entities<PlayerInput>();
    for (const auto &e : entities) {
        auto &i = m_ecs.get<PlayerInput>(e);

        // Movement
        i.m_left = Inputs::get()->get_key(KeyType::Key_A) == KeyState::Down;
        i.m_right = Inputs::get()->get_key(KeyType::Key_D) == KeyState::Down;
        i.m_up = Inputs::get()->get_key(KeyType::Key_W) == KeyState::Down;
        i.m_down = Inputs::get()->get_key(KeyType::Key_S) == KeyState::Down;
        // Other
        i.m_use = Inputs::get()->get_key(KeyType::Key_F) == KeyState::Down;
    }
}
