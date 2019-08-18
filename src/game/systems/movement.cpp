#include "../components/movement.hpp"
#include <cprof/profiler.hpp>
#include <ecs/ecs.hpp>
#include "../components/position.hpp"
#include "../game.hpp"
#include "../tilemap.hpp"

using namespace components;

void Game::s_movement() {
    auto t = cprof::Timer(__PRETTY_FUNCTION__);

    auto entities = ecs_.entities<Movement, Position>();
    for (const auto &e : entities) {
        auto &m = ecs_.get<Movement>(e);
        auto &p = ecs_.get<Position>(e);

        if (m.left_) {
            if (tile_map_.get_tile(p.x_ - 1, p.y_) != Tile::Water) {
                p.x_--;
            }
        } else if (m.right_) {
            if (tile_map_.get_tile(p.x_ + 1, p.y_) != Tile::Water) {
                p.x_++;
            }
        } else if (m.up_) {
            if (tile_map_.get_tile(p.x_, p.y_ + 1) != Tile::Water) {
                p.y_++;
            }
        } else if (m.down_) {
            if (tile_map_.get_tile(p.x_, p.y_ - 1) != Tile::Water) {
                p.y_--;
            }
        }
    }
}
