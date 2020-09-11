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
    int width_;
    int height_;
    std::shared_ptr<SDL_Window> window_;
    std::shared_ptr<SDL_Renderer> renderer_;
};

#endif
