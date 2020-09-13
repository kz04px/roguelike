#include <cprof/profiler.hpp>
#include "../components/position.hpp"
#include "../game.hpp"

using namespace components;

void Game::s_camera() {
    auto t = cprof::Timer(__PRETTY_FUNCTION__);

    auto &p = m_ecs.get<Position>(0);

    const int target_x = p.m_x;
    const int target_y = p.m_y;
    const int leash_x = 5;
    const int leash_y = 5;
    const int dx = m_camera.m_x - target_x;
    const int dy = m_camera.m_y - target_y;

    if (dx < -leash_x) {
        m_camera.m_x++;
    } else if (dx > leash_x) {
        m_camera.m_x--;
    }

    if (dy < -leash_y) {
        m_camera.m_y++;
    } else if (dy > leash_y) {
        m_camera.m_y--;
    }
}
