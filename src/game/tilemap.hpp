#ifndef GAME_TILEMAP_HPP
#define GAME_TILEMAP_HPP

#include <cassert>
#include <clog/clog.hpp>
#include <cprof/profiler.hpp>
#include <cstdint>
#include <noise/perlin.hpp>
#include <unordered_map>

enum class Tile : std::uint8_t
{
    Dirt = 0,
    Stone,
    Water
};

struct Chunk {
   public:
    Chunk() {
    }

    Chunk(const int x, const int y) : x_{x}, y_{y} {
        auto t = cprof::Timer(__PRETTY_FUNCTION__);

        for (int i = 0; i < 16; ++i) {
            for (int j = 0; j < 16; ++j) {
                // set(i, j, Tile::Dirt);

                const double noise_x = x + (double)i / 16.0;
                const double noise_y = y + (double)j / 16.0;

                auto n = noise::perlin::get(noise_x, noise_y, 0.0);
                if (n > 0.1) {
                    set(i, j, Tile::Dirt);
                } else if (n > -0.3) {
                    set(i, j, Tile::Stone);
                } else {
                    set(i, j, Tile::Water);
                }
            }
        }
        // set(0, 0, Tile::Stone);
        // set(1, 2, Tile::Stone);
        // set(15, 0, Tile::Water);
    }

    void set(const unsigned int x,
             const unsigned int y,
             const Tile t) noexcept {
        assert(x < 16);
        assert(y < 16);
        tiles_[x][y] = t;
    }

    [[nodiscard]] Tile get(const int x, const int y) const noexcept {
        assert(x < 16);
        assert(y < 16);
        return tiles_[x][y];
    }

    /*
    bool operator==(const Chunk &rhs) const {
        return x_ == rhs.x_ && y_ == rhs.y_;
    }
    */
    int x_;
    int y_;
    Tile tiles_[16][16];
};

class Hasher {
   public:
    size_t operator()(const std::pair<int, int> &key) const {
        return key.first ^ (key.second << 6);
    }
};

[[nodiscard]] constexpr int tile_chunk_x(const int tile_x) {
    return tile_x >= 0 ? tile_x / 16 : tile_x / 16 - 1;
}

[[nodiscard]] constexpr int tile_chunk_y(const int tile_y) {
    return tile_y >= 0 ? tile_y / 16 : tile_y / 16 - 1;
}

[[nodiscard]] constexpr int tile_offset_x(const int tile_x) {
    return tile_x >= 0 ? tile_x % 16 : 15 - (-(tile_x + 1) % 16);
}

[[nodiscard]] constexpr int tile_offset_y(const int tile_y) {
    return tile_y >= 0 ? tile_y % 16 : 15 - (-(tile_y + 1) % 16);
}

static_assert(tile_chunk_x(0) == 0);
static_assert(tile_chunk_x(1) == 0);
static_assert(tile_chunk_x(15) == 0);
static_assert(tile_chunk_x(16) == 1);
static_assert(tile_chunk_x(-1) == -1);
static_assert(tile_chunk_x(-15) == -1);
static_assert(tile_chunk_x(-16) == -2);

static_assert(tile_offset_x(0) == 0);
static_assert(tile_offset_x(1) == 1);
static_assert(tile_offset_x(15) == 15);
static_assert(tile_offset_x(16) == 0);
static_assert(tile_offset_x(17) == 1);
static_assert(tile_offset_x(-1) == 15);

class TileMap {
   public:
    TileMap() {
    }

    [[nodiscard]] bool has(const int chunk_x, const int chunk_y) const
        noexcept {
        return chunks_.find(std::pair<int, int>(chunk_x, chunk_y)) !=
               chunks_.end();
    }

    void generate(const int chunk_x, const int chunk_y) {
        auto t = cprof::Timer(__PRETTY_FUNCTION__);

        if (has(chunk_x, chunk_y)) {
            clog::Log::get()->error(
                "Tried to generate chunk that already exists (",
                chunk_x,
                ",",
                chunk_y,
                ")");
            return;
        }
        const std::pair<int, int> p{chunk_x, chunk_y};
        Chunk c{chunk_x, chunk_y};
        chunks_.emplace(p, c);
    }

    void set(const int tile_x, const int tile_y, const Tile t) {
        const int chunk_x = tile_chunk_x(tile_x);
        const int chunk_y = tile_chunk_y(tile_y);
        const int offset_x = tile_offset_x(tile_x);
        const int offset_y = tile_offset_y(tile_y);
        const std::pair<int, int> p{chunk_x, chunk_y};

        // Add the chunk if it doesn't already exist
        if (!has(chunk_x, chunk_y)) {
            generate(chunk_x, chunk_y);
        }

        // Set the tile within the chunk
        auto iter = chunks_.find(p);
        assert(iter != chunks_.end());
        iter->second.set(offset_x, offset_y, t);
    }

    [[nodiscard]] const Chunk *get_chunk(const int chunk_x, const int chunk_y) {
        auto t = cprof::Timer(__PRETTY_FUNCTION__);

        const std::pair<int, int> p{chunk_x, chunk_y};

        // Generate the chunk if it doesn't already exist
        if (!has(chunk_x, chunk_y)) {
            generate(chunk_x, chunk_y);
        }

        // Get the tile within the chunk
        auto iter = chunks_.find(p);
        assert(iter != chunks_.end());
        return &iter->second;
    }

    [[nodiscard]] Tile get_tile(const int tile_x, const int tile_y) {
        auto t = cprof::Timer(__PRETTY_FUNCTION__);

        const int chunk_x = tile_chunk_x(tile_x);
        const int chunk_y = tile_chunk_y(tile_y);
        const int offset_x = tile_offset_x(tile_x);
        const int offset_y = tile_offset_y(tile_y);
        const std::pair<int, int> p{chunk_x, chunk_y};

        // Add the chunk if it doesn't already exist
        if (!has(chunk_x, chunk_y)) {
            generate(chunk_x, chunk_y);
        }

        // Get the tile within the chunk
        auto iter = chunks_.find(p);
        assert(iter != chunks_.end());
        return iter->second.get(offset_x, offset_y);
    }

   private:
    std::unordered_map<std::pair<int, int>, Chunk, Hasher> chunks_;
};

#endif
