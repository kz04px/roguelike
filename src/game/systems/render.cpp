#include "../components/render.hpp"
#include <cprof/profiler.hpp>
#include "../../render/renderer.hpp"
#include "../components/flammable.hpp"
#include "../components/position.hpp"
#include "../game.hpp"

using namespace components;

void Game::s_render() {
    auto t = cprof::Timer(__PRETTY_FUNCTION__);

    const int x_offset = m_camera.m_x - m_camera.m_half_w;
    const int y_offset = m_camera.m_y - m_camera.m_half_h;

    // Tiles
    {
        auto t1 = cprof::Timer("Render -- Tiles");
        for (int x = 0; x < m_camera.m_w; ++x) {
            for (int y = 0; y < m_camera.m_h; ++y) {
                const int world_x = x_offset + x;
                const int world_y = y_offset + y;
                const int tile_screen_x = 16 * x;
                const int tile_screen_y = m_renderer->height() - 16 * y;

                switch (m_tile_map.get_tile(world_x, world_y).terrain()) {
                    case Terrain::Dirt:
                        m_renderer->set_colour(96, 64, 31, 255);
                        m_renderer->draw_rect_fill(tile_screen_x, tile_screen_y, 16, 16);
                        // renderer_->draw_rect_tex(
                        //    0, 1, 0, 16 * x, 16 * y, 16, 16);
                        break;
                    case Terrain::Stone:
                        m_renderer->set_colour(51, 26, 0, 255);
                        m_renderer->draw_rect_fill(tile_screen_x, tile_screen_y, 16, 16);
                        // renderer_->draw_rect_tex(
                        //    0, 1, 0, 16 * x, 16 * y, 16, 16);
                        break;
                    case Terrain::Water:
                        m_renderer->set_colour(50, 50, 200, 255);
                        m_renderer->draw_rect_fill(tile_screen_x, tile_screen_y, 16, 16);
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
        auto entities = m_ecs.entities<Render, Position>();
        for (const auto &e : entities) {
            auto &r = m_ecs.get<Render>(e);
            auto &p = m_ecs.get<Position>(e);

            const int dx = p.m_x - x_offset;
            const int dy = p.m_y - y_offset;
            const int tile_screen_x = 16 * dx;
            const int tile_screen_y = m_renderer->height() - 16 * dy;

            if (0 <= dx && dx <= m_camera.m_w && 0 <= dy && dy <= m_camera.m_h) {
                m_renderer->draw_rect_tex(0, r.x(), r.y(), tile_screen_x, tile_screen_y, 16, 16);
            }
        }
    }

    {
        auto t3 = cprof::Timer("Render -- Fire");
        auto entities = m_ecs.entities<Position, Flammable>();
        for (const auto &e : entities) {
            auto &p = m_ecs.get<Position>(e);
            auto &f = m_ecs.get<Flammable>(e);

            if (!f.m_on_fire) {
                continue;
            }

            const int dx = p.m_x - x_offset;
            const int dy = p.m_y - y_offset;
            const int tile_screen_x = 16 * dx;
            const int tile_screen_y = m_renderer->height() - 16 * dy;

            if (0 <= dx && dx <= m_camera.m_w && 0 <= dy && dy <= m_camera.m_h) {
                m_renderer->draw_rect_tex(0, 15, 10, tile_screen_x, tile_screen_y, 16, 16);
            }
        }
    }
}
