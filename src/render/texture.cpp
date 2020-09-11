#include "texture.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <cassert>
#include <clog/clog.hpp>

Texture::Texture(std::shared_ptr<SDL_Renderer> renderer, const std::string &path) {
    assert(renderer);
}

Texture::~Texture() {
    clog::Log::get()->info("Texture destroyed");
    SDL_DestroyTexture(texture_);
}

SDL_Texture *Texture::get() {
    return texture_;
}
