#include "window.hpp"
#include <SDL.h>
#include <cassert>
#include <clog/clog.hpp>
#include <stdexcept>

Window::Window(const std::string &title, const int w, const int h)
    : width_(w), height_(h) {
    if (w <= 0 || h <= 0) {
        throw std::invalid_argument("Size too small");
    }
    clog::Log::get()->info("Window constructor");

    const auto window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
    window_ =
        std::shared_ptr<SDL_Window>(SDL_CreateWindow(title.c_str(),
                                                     SDL_WINDOWPOS_UNDEFINED,
                                                     SDL_WINDOWPOS_UNDEFINED,
                                                     w,
                                                     h,
                                                     window_flags),
                                    SDL_DestroyWindow);
    if (!window_) {
        throw std::exception();
    }

    renderer_ = std::shared_ptr<SDL_Renderer>(
        SDL_CreateRenderer(window_.get(), -1, SDL_RENDERER_ACCELERATED),
        SDL_DestroyRenderer);
    if (!renderer_) {
        throw std::exception();

        SDL_Rect rect;
        rect.x = 0;
        rect.y = 0;
        rect.w = width_;
        rect.h = height_;
        SDL_RenderSetViewport(renderer_.get(), &rect);
        SDL_RenderSetClipRect(renderer_.get(), &rect);
        SDL_SetRenderDrawColor(renderer_.get(), 255, 255, 255, 255);
        SDL_SetRenderDrawBlendMode(renderer_.get(), SDL_BLENDMODE_BLEND);
    }
}

Window::~Window() {
    clog::Log::get()->info("Window destructor");
}

std::shared_ptr<SDL_Renderer> Window::renderer() {
    return renderer_;
}

void Window::resize(const int w, const int h) {
    assert(renderer_);

    width_ = w;
    height_ = h;

    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = width_;
    rect.h = height_;

    SDL_RenderSetViewport(renderer_.get(), &rect);
    SDL_RenderSetClipRect(renderer_.get(), &rect);
}

void Window::swap() {
    SDL_GL_SwapWindow(window_.get());
}
