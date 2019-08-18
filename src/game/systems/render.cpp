#include "../components/render.hpp"
#include <cprof/profiler.hpp>
#include "../../render/renderer.hpp"
#include "../components/flammable.hpp"
#include "../components/position.hpp"
#include "../game.hpp"

using namespace components;

void Game::s_render() {
    auto t = cprof::Timer(__PRETTY_FUNCTION__);

    const int x_offset = camera_.x_ - camera_.half_w_;
    const int y_offset = camera_.y_ - camera_.half_h_;

    // Tiles
    {
        auto t1 = cprof::Timer("Render -- Tiles");
        for (int x = 0; x < camera_.w_; ++x) {
            for (int y = 0; y < camera_.h_; ++y) {
                const int world_x = x_offset + x;
                const int world_y = y_offset + y;

                switch (tile_map_.get_tile(world_x, world_y)) {
                    case Tile::Dirt:
                        renderer_->set_colour(96, 64, 31, 255);
                        renderer_->draw_rect_fill(16 * x, 16 * y, 16, 16);
                        // renderer_->draw_rect_tex(
                        //    0, 1, 0, 16 * x, 16 * y, 16, 16);
                        break;
                    case Tile::Stone:
                        renderer_->set_colour(51, 26, 0, 255);
                        renderer_->draw_rect_fill(16 * x, 16 * y, 16, 16);
                        // renderer_->draw_rect_tex(
                        //    0, 1, 0, 16 * x, 16 * y, 16, 16);
                        break;
                    case Tile::Water:
                        renderer_->set_colour(50, 50, 200, 255);
                        renderer_->draw_rect_fill(16 * x, 16 * y, 16, 16);
                        break;
                    default:
                        break;
                }
            }
        }
    }

    // Entities
    {
        auto t2 = cprof::Timer("Render -- Entities");
        auto entities = ecs_.entities<Render, Position>();
        for (const auto &e : entities) {
            auto &r = ecs_.get<Render>(e);
            auto &p = ecs_.get<Position>(e);

            const int dx = p.x_ - x_offset;
            const int dy = p.y_ - y_offset;

            if (0 <= dx && dx <= camera_.w_ && 0 <= dy && dy <= camera_.h_) {
                renderer_->draw_rect_tex(
                    0, r.x(), r.y(), 16 * dx, 16 * dy, 16, 16);
            }
        }
    }

    {
        auto t3 = cprof::Timer("Render -- Fire");
        auto entities = ecs_.entities<Position, Flammable>();
        for (const auto &e : entities) {
            auto &p = ecs_.get<Position>(e);
            auto &f = ecs_.get<Flammable>(e);

            if (!f.on_fire) {
                continue;
            }

            const int dx = p.x_ - x_offset;
            const int dy = p.y_ - y_offset;

            if (0 <= dx && dx <= camera_.w_ && 0 <= dy && dy <= camera_.h_) {
                renderer_->draw_rect_tex(0, 15, 10, 16 * dx, 16 * dy, 16, 16);
            }
        }
    }
}
