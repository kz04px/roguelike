#ifndef GAME_GAME_HPP
#define GAME_GAME_HPP

#include <cstdint>
#include <ecs/ecs.hpp>
#include <ecs/entity.hpp>
#include <memory>
#include "camera.hpp"
#include "chunk_manager.hpp"
#include "spell_manager.hpp"

class Event;
class KeyPressEvent;
class KeyReleaseEvent;
class WindowCloseEvent;
class WindowResizeEvent;
class Renderer;

class Game {
   public:
    Game(std::shared_ptr<Renderer> r);

    void step();

    void render();

    void load();

    // Events
    void on_event(Event &e);
    void on_key_press(KeyPressEvent &e);
    void on_key_release(KeyReleaseEvent &e);
    void on_window_close(WindowCloseEvent &e);
    void on_window_resize(WindowResizeEvent &e);

    // Systems -- Game logic
    void s_age();
    void s_fire();
    void s_input();
    void s_movement_input();
    void s_movement();
    void s_camera();
    void s_timer();
    void s_spells();
    void s_health();

    // Systems -- Rendering
    void s_render();
    void s_render_debug();

   private:
    ECS m_ecs;
    std::uint64_t m_frame;
    std::shared_ptr<Renderer> m_renderer;
    ChunkManager<Tile> m_tile_map;
    SpellManager m_spell_manager;
    Camera m_camera;
};

#endif
