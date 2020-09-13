#ifndef RENDERER_RENDER_HPP
#define RENDERER_RENDER_HPP

#include <map>
#include <memory>
#include "texture.hpp"

#define MAX_TEXTURES 128

struct SDL_Renderer;
struct SDL_Texture;

class Renderer {
   public:
    Renderer(std::shared_ptr<SDL_Renderer> r);

    ~Renderer();

    bool load_texture(const int id, const std::string &path);

    void clear();

    void render();

    void set_size(const int w, const int h);

    void set_colour(const int r, const int g, const int b, const int a);

    // Draw
    void draw_rect_fill(const int x, const int y, const int w, const int h);
    void draw_rect(const int x, const int y, const int w, const int h);
    void draw_rect_tex(const int id,
                       const int tex_x,
                       const int tex_y,
                       const int x,
                       const int y,
                       const int w,
                       const int h);

   private:
    int m_width = 512;
    int m_height = 512;
    std::shared_ptr<SDL_Renderer> m_renderer;
    std::map<int, std::shared_ptr<SDL_Texture>> m_textures;
};

#endif
