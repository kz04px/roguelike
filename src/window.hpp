#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <memory>
#include <string>

struct SDL_Window;
struct SDL_Renderer;

class Window {
   public:
    Window() {
    }

    Window(const std::string &title, const int w, const int h);

    ~Window();

    std::shared_ptr<SDL_Renderer> renderer();

    void resize(const int w, const int h);

    void swap();

   private:
    int m_width;
    int m_height;
    std::shared_ptr<SDL_Window> m_window;
    std::shared_ptr<SDL_Renderer> m_renderer;
};

#endif
