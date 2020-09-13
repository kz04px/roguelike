#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <memory>
#include "game/game.hpp"

class Event;
class KeyPressEvent;
class KeyReleaseEvent;
class WindowCloseEvent;
class WindowResizeEvent;
class Window;
class Renderer;

class Application {
   public:
    Application();

    ~Application();

    // Events
    void on_event(Event &e);
    void on_key_press(KeyPressEvent &e);
    void on_key_release(KeyReleaseEvent &e);
    void on_window_close(WindowCloseEvent &e);
    void on_window_resize(WindowResizeEvent &e);

    void run();

   private:
    std::unique_ptr<Window> m_window;
    std::shared_ptr<Renderer> m_renderer;
    std::unique_ptr<Game> m_game;
    bool m_quit;
};

#endif
