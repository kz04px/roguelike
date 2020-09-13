#include "../components/movement.hpp"
#include <cprof/profiler.hpp>
#include <ecs/ecs.hpp>
#include "../components/position.hpp"
#include "../game.hpp"
#include "../tilemap.hpp"

using namespace components;

void Game::s_movement() {
    auto t = cprof::Timer(__PRETTY_FUNCTION__);

    auto entities = m_ecs.entities<Movement, Position>();
    for (const auto &e : entities) {
        auto &m = m_ecs.get<Movement>(e);
        auto &p = m_ecs.get<Position>(e);

        if (m.m_left) {
            if (m_tile_map.get_tile(p.m_x - 1, p.m_y) != Tile::Water) {
                p.m_x--;
            }
        } else if (m.m_right) {
            if (m_tile_map.get_tile(p.m_x + 1, p.m_y) != Tile::Water) {
                p.m_x++;
            }
        } else if (m.m_up) {
            if (m_tile_map.get_tile(p.m_x, p.m_y + 1) != Tile::Water) {
                p.m_y++;
            }
        } else if (m.m_down) {
            if (m_tile_map.get_tile(p.m_x, p.m_y - 1) != Tile::Water) {
                p.m_y--;
            }
        }
    }
}
