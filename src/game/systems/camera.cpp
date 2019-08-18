#include <cprof/profiler.hpp>
#include "../components/position.hpp"
#include "../game.hpp"

using namespace components;

void Game::s_camera() {
    auto t = cprof::Timer(__PRETTY_FUNCTION__);

    auto &p = ecs_.get<Position>(0);

    const int target_x = p.x_;
    const int target_y = p.y_;
    const int leash_x = 5;
    const int leash_y = 5;
    const int dx = camera_.x_ - target_x;
    const int dy = camera_.y_ - target_y;

    if (dx < -leash_x) {
        camera_.x_++;
    } else if (dx > leash_x) {
        camera_.x_--;
    }

    if (dy < -leash_y) {
        camera_.y_++;
    } else if (dy > leash_y) {
        camera_.y_--;
    }
}
