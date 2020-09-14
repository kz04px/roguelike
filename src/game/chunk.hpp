#ifndef CHUNK_HPP
#define CHUNK_HPP

#include "tile.hpp"

template <class T, int W, int H>
struct Chunk {
   public:
    constexpr Chunk() : m_x{}, m_y{}, m_tiles{} {
    }

    constexpr Chunk(const int chunk_x, const int chunk_y, const std::function<T(int, int)> &func)
        : m_x{chunk_x}, m_y{chunk_y}, m_tiles{} {
        for (int y = 0; y < H; ++y) {
            for (int x = 0; x < W; ++x) {
                const int tile_x = chunk_x * W + x;
                const int tile_y = chunk_y * H + y;
                m_tiles[x][y] = func(tile_x, tile_y);
            }
        }
    }

    constexpr void set(const unsigned int x, const unsigned int y, const T t) noexcept {
        assert(x < W);
        assert(y < H);
        m_tiles[x][y] = t;
    }

    [[nodiscard]] constexpr T &get(const int x, const int y) noexcept {
        assert(x < W);
        assert(y < H);
        return m_tiles[x][y];
    }

   private:
    int m_x;
    int m_y;
    T m_tiles[W][H];
};

#endif
