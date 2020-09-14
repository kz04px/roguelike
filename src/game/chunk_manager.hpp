#ifndef CHUNK_MANAGER_HPP
#define CHUNK_MANAGER_HPP

#include <cassert>
#include <functional>
#include <unordered_map>
#include "chunk.hpp"

template <class T, int W = 16, int H = 16>
class ChunkManager {
   public:
    static_assert(W > 0);
    static_assert(H > 0);

    constexpr ChunkManager(const std::function<T(int, int)> &func) : m_chunk_map{}, m_func{func} {
    }

    ChunkManager(const ChunkManager &) = delete;

    ChunkManager &operator=(ChunkManager const &) = delete;

    [[nodiscard]] constexpr int chunk_width() const noexcept {
        return W;
    }

    [[nodiscard]] constexpr int chunk_height() const noexcept {
        return H;
    }

    [[nodiscard]] constexpr bool has(const int x, const int y) const noexcept {
        return m_chunk_map.find(std::pair<int, int>(x, y)) != m_chunk_map.end();
    }

    [[nodiscard]] constexpr static int tile_chunk_x(const int tile_x) {
        return tile_x >= 0 ? tile_x / W : (tile_x + 1) / W - 1;
    }

    [[nodiscard]] constexpr static int tile_chunk_y(const int tile_y) {
        return tile_y >= 0 ? tile_y / H : (tile_y + 1) / H - 1;
    }

    [[nodiscard]] constexpr static std::pair<int, int> tile_chunk(const int tile_x,
                                                                  const int tile_y) noexcept {
        const auto chunk_x = tile_chunk_x(tile_x);
        const auto chunk_y = tile_chunk_y(tile_y);
        return {chunk_x, chunk_y};
    }

    [[nodiscard]] constexpr static int tile_offset_x(const int tile_x) {
        return tile_x >= 0 ? tile_x % W : (W - 1) - (-(tile_x + 1) % W);
    }

    [[nodiscard]] constexpr static int tile_offset_y(const int tile_y) {
        return tile_y >= 0 ? tile_y % H : (H - 1) - (-(tile_y + 1) % H);
    }

    [[nodiscard]] constexpr static std::pair<int, int> tile_offset(const int tile_x,
                                                                   const int tile_y) noexcept {
        const auto offset_x = tile_offset_x(tile_x);
        const auto offset_y = tile_offset_y(tile_y);
        return {offset_x, offset_y};
    }

    [[nodiscard]] Chunk<T, W, H> &get_chunk(const int x, const int y) noexcept {
        const auto iter = m_chunk_map.find(std::pair<int, int>(x, y));

        if (iter == m_chunk_map.end()) {
            generate(x, y);
        }

        return m_chunk_map.find(std::pair<int, int>(x, y))->second;
    }

    [[nodiscard]] T &get_tile(const int tile_x, const int tile_y) noexcept {
        const auto chunk_x = tile_chunk_x(tile_x);
        const auto chunk_y = tile_chunk_y(tile_y);
        const auto offset_x = tile_offset_x(tile_x);
        const auto offset_y = tile_offset_y(tile_y);

        return get_chunk(chunk_x, chunk_y).get(offset_x, offset_y);
    }

    [[nodiscard]] constexpr auto size() const noexcept {
        return m_chunk_map.size();
    }

    void generate(const int chunk_x, const int chunk_y) noexcept {
        if (has(chunk_x, chunk_y)) {
            return;
        }

        const std::pair<int, int> p{chunk_x, chunk_y};
        Chunk<T, W, H> c{chunk_x, chunk_y, m_func};
        m_chunk_map.emplace(p, c);

        // m_chunk_map.emplace(std::pair<int, int>{x, y}, x, y);
    }

   private:
    class Hasher {
       public:
        [[nodiscard]] constexpr std::size_t operator()(
            const std::pair<int, int> &key) const noexcept {
            return key.first ^ (key.second << 6);
        }
    };

    std::unordered_map<std::pair<int, int>, Chunk<T, W, H>, Hasher> m_chunk_map;
    std::function<T(int, int)> m_func;
};

// What chunk are these tiles in?
static_assert(ChunkManager<Tile, 16, 16>::tile_chunk(0, 0) == std::pair<int, int>{0, 0});
static_assert(ChunkManager<Tile, 16, 16>::tile_chunk(-17, 0) == std::pair<int, int>{-2, 0});
static_assert(ChunkManager<Tile, 16, 16>::tile_chunk(-16, 0) == std::pair<int, int>{-1, 0});
static_assert(ChunkManager<Tile, 16, 16>::tile_chunk(-15, 0) == std::pair<int, int>{-1, 0});
static_assert(ChunkManager<Tile, 16, 16>::tile_chunk(-1, 0) == std::pair<int, int>{-1, 0});
static_assert(ChunkManager<Tile, 16, 16>::tile_chunk(0, -1) == std::pair<int, int>{0, -1});
static_assert(ChunkManager<Tile, 16, 16>::tile_chunk(15, 15) == std::pair<int, int>{0, 0});
static_assert(ChunkManager<Tile, 16, 16>::tile_chunk(16, 15) == std::pair<int, int>{1, 0});
static_assert(ChunkManager<Tile, 16, 16>::tile_chunk(15, 16) == std::pair<int, int>{0, 1});

// What's the offset of these tiles?
// (What are the tile coordinates relative to the chunk)
static_assert(ChunkManager<Tile, 16, 16>::tile_offset(0, 0) == std::pair<int, int>{0, 0});
static_assert(ChunkManager<Tile, 16, 16>::tile_offset(1, 2) == std::pair<int, int>{1, 2});
static_assert(ChunkManager<Tile, 16, 16>::tile_offset(-1, 0) == std::pair<int, int>{15, 0});
static_assert(ChunkManager<Tile, 16, 16>::tile_offset(-15, 0) == std::pair<int, int>{1, 0});
static_assert(ChunkManager<Tile, 16, 16>::tile_offset(-16, 0) == std::pair<int, int>{0, 0});
static_assert(ChunkManager<Tile, 16, 16>::tile_offset(-17, 0) == std::pair<int, int>{15, 0});
static_assert(ChunkManager<Tile, 16, 16>::tile_offset(0, -1) == std::pair<int, int>{0, 15});
static_assert(ChunkManager<Tile, 16, 16>::tile_offset(15, 15) == std::pair<int, int>{15, 15});
static_assert(ChunkManager<Tile, 16, 16>::tile_offset(16, 16) == std::pair<int, int>{0, 0});

#endif
