#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <memory>

struct SDL_Renderer;
struct SDL_Texture;

class Texture {
   public:
    Texture(std::shared_ptr<SDL_Renderer> renderer, const std::string &path);

    ~Texture();

    SDL_Texture *get();

   private:
    SDL_Texture *m_texture;
};

#endif
