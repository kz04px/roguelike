#ifndef TILE_HPP
#define TILE_HPP

enum class Terrain : int
{
    Dirt = 0,
    Stone,
    Water
};

class Tile {
   public:
    constexpr Tile() : m_terrain{Terrain::Dirt} {
    }

    constexpr Tile(const Terrain t) : m_terrain{t} {
    }

    [[nodiscard]] constexpr Terrain terrain() const noexcept {
        return m_terrain;
    }

   private:
    Terrain m_terrain;
};

#endif
