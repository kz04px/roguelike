#include <cprof/profiler.hpp>
#include "../../render/renderer.hpp"
#include "../components/flammable.hpp"
#include "../components/position.hpp"
#include "../components/render.hpp"
#include "../game.hpp"

using namespace components;

void Game::s_render_debug() {
    auto t = cprof::Timer(__PRETTY_FUNCTION__);

    const int x_offset = camera_.x_ - camera_.half_w_;
    const int y_offset = camera_.y_ - camera_.half_h_;

    /*
    // Tiles
    for (int x = 0; x < camera_.w_; ++x) {
        for (int y = 0; y < camera_.h_; ++y) {
            renderer_->set_colour(255, 0, 0, 255);
            renderer_->draw_rect(16 * x, 16 * y, 16, 16);
        }
    }
    */

    // Chunks
    {
        /*
        renderer_->set_colour(255, 0, 0, 255);
        const int dx = x_offset % 16;
        const int dy = y_offset % 16;
        for (int x = x_offset; x <= camera_.x_ + camera_.half_w_; x += 16) {
            for (int y = y_offset; y <= camera_.y_ + camera_.half_h_; y += 16) {
                renderer_->draw_rect(
                    16 * 16 * (x - dx), 16 * 16 * (y - dy), 16 * 16, 16 * 16);
            }
        }
        */
    }

    // Camera location
    renderer_->set_colour(0, 0, 255, 255);
    renderer_->draw_rect(16 * camera_.half_w_, 16 * camera_.half_h_, 16, 16);
}
