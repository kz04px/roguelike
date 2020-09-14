#include "texture.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cassert>
#include <clog/clog.hpp>

Texture::Texture(std::shared_ptr<SDL_Renderer> renderer, const std::string &path) {
    assert(renderer);
}

Texture::~Texture() {
    clog::Log::get()->info("Texture destroyed");
    SDL_DestroyTexture(m_texture);
}

SDL_Texture *Texture::get() {
    return m_texture;
}
