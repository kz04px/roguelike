#include "renderer.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cassert>
#include <clog/clog.hpp>
#include <cprof/profiler.hpp>
#include <string>

Renderer::Renderer(std::shared_ptr<SDL_Renderer> r) : m_renderer{r} {
    assert(r);
    clog::Log::get()->info("Renderer constructor");
    set_size(512, 512);
}

Renderer::~Renderer() {
    clog::Log::get()->info("Renderer destructor");
}

bool Renderer::load_texture(const int id, const std::string &path) {
    auto t = cprof::Timer(__PRETTY_FUNCTION__);

    // Texture already loaded
    if (m_textures.find(id) != m_textures.end()) {
        clog::Log::get()->error("Texture already loaded: ", path);
        return false;
    }

    // Max textures already loaded
    /*
    if (count_ >= MAX_TEXTURES) {
        clog::Log::get()->error("Max textures reached: ", MAX_TEXTURES);
        return false;
    }
    */

    // Load image at specified path
    SDL_Surface *loaded_surface = IMG_Load(path.c_str());
    if (!loaded_surface) {
        clog::Log::get()->error("IMG_Load failure: ", IMG_GetError());
        return false;
    }

    // Create texture from surface pixels
    SDL_Texture *tex = SDL_CreateTextureFromSurface(m_renderer.get(), loaded_surface);

    // Get rid of old loaded surface
    SDL_FreeSurface(loaded_surface);

    if (!tex) {
        clog::Log::get()->error(
            "SDL_CreateTextureFromSurface failure: ", SDL_GetError(), ", ", path);
        return false;
    }

    clog::Log::get()->info("Texture loaded: ", path);
    m_textures.emplace(id, std::shared_ptr<SDL_Texture>(tex, SDL_DestroyTexture));
    return true;
}

void Renderer::clear() {
    SDL_SetRenderDrawColor(m_renderer.get(), 0, 0, 0, 255);
    SDL_RenderClear(m_renderer.get());
}

void Renderer::render() {
    SDL_RenderPresent(m_renderer.get());
}

void Renderer::set_size(const int w, const int h) {
    assert(w >= 0);
    assert(h >= 0);
    m_width = w;
    m_height = h;
    SDL_RenderSetLogicalSize(m_renderer.get(), w, h);
}

void Renderer::set_colour(const int r, const int g, const int b, const int a) {
    SDL_SetRenderDrawColor(m_renderer.get(), r, g, b, a);
}

// Render a filled rectangle
void Renderer::draw_rect_fill(const int x, const int y, const int w, const int h) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = m_height - y - h;
    rect.w = w;
    rect.h = h;
    SDL_RenderFillRect(m_renderer.get(), &rect);
}

// Render an unfilled rectangle
void Renderer::draw_rect(const int x, const int y, const int w, const int h) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = m_height - y - h;
    rect.w = w;
    rect.h = h;
    SDL_RenderDrawRect(m_renderer.get(), &rect);
}

// Render a texture
void Renderer::draw_rect_tex(const int id,
                             const int tex_x,
                             const int tex_y,
                             const int x,
                             const int y,
                             const int w,
                             const int h) {
    assert(m_textures.find(id) != m_textures.end());
    assert(m_textures.find(id)->second.get());

    // Texture rect
    SDL_Rect src;
    src.x = 16 * tex_x + tex_x;
    src.y = 16 * tex_y + tex_y;
    src.w = 16;
    src.h = 16;

    // Screen rect
    SDL_Rect dst;
    dst.x = x;
    dst.y = m_height - y - h;
    dst.w = w;
    dst.h = h;

    SDL_RenderCopy(m_renderer.get(), m_textures.find(id)->second.get(), &src, &dst);
}
