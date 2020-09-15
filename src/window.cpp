#include "window.hpp"
#include <SDL2/SDL.h>
#include <cassert>
#include <clog/clog.hpp>
#include <stdexcept>

Window::Window(const std::string &title, const int w, const int h) : m_width(w), m_height(h) {
    if (w <= 0 || h <= 0) {
        throw std::invalid_argument("Size too small");
    }
    clog::Log::get()->info("Window constructor");

    const auto window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
    m_window = std::shared_ptr<SDL_Window>(
        SDL_CreateWindow(
            title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, window_flags),
        SDL_DestroyWindow);
    if (!m_window) {
        throw std::exception();
    }

    m_renderer = std::shared_ptr<SDL_Renderer>(
        SDL_CreateRenderer(m_window.get(), -1, SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer);
    if (!m_renderer) {
        throw std::exception();
    }

    resize(m_width, m_height);
    SDL_SetRenderDrawBlendMode(m_renderer.get(), SDL_BLENDMODE_BLEND);
}

Window::~Window() {
    clog::Log::get()->info("Window destructor");
}

std::shared_ptr<SDL_Renderer> Window::renderer() {
    return m_renderer;
}

void Window::resize(const int w, const int h) {
    assert(m_renderer);

    m_width = w;
    m_height = h;

    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = m_width;
    rect.h = m_height;

    SDL_RenderSetViewport(m_renderer.get(), &rect);
    SDL_RenderSetClipRect(m_renderer.get(), &rect);
}

void Window::swap() {
    SDL_GL_SwapWindow(m_window.get());
}
