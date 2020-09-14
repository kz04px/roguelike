#include <game/chunk_manager.hpp>
#include "catch.hpp"

class TestTile {
   public:
    constexpr TestTile() : m_n{0} {
    }

    constexpr TestTile(const int n) : m_n{n} {
    }

    [[nodiscard]] constexpr auto n() const noexcept {
        return m_n;
    }

   private:
    int m_n;
};

TEST_CASE("ChunkManager") {
    const int chunk_height = 16;
    const int chunk_width = 16;
    const auto gen = [](const int x, const int y) { return TestTile(x > 4 && y > 4); };
    ChunkManager<TestTile> cm(gen);

    REQUIRE(cm.size() == 0);
    REQUIRE(cm.chunk_height() == chunk_height);
    REQUIRE(cm.chunk_width() == chunk_width);

    cm.generate(0, 0);

    REQUIRE(cm.size() == 1);
    REQUIRE(cm.get_tile(4, 4).n() == 0);
    REQUIRE(cm.get_tile(5, 4).n() == 0);
    REQUIRE(cm.get_tile(4, 5).n() == 0);
    REQUIRE(cm.get_tile(5, 5).n() == 1);

    // Get tiles from a chunk that doesn't exist yet
    // This is going to generate a new chunk for us
    REQUIRE(cm.get_tile(20, 4).n() == 0);
    REQUIRE(cm.get_tile(20, 5).n() == 1);

    REQUIRE(cm.size() == 2);
}

TEST_CASE("ChunkManager::get_tile() 1") {
    const auto gen = [](const int x, const int y) { return TestTile(x); };
    ChunkManager<TestTile> cm(gen);

    for (int i = -100; i <= 100; ++i) {
        REQUIRE(cm.get_tile(i, 0).n() == gen(i, 0).n());
    }
}

TEST_CASE("ChunkManager::get_tile() 2") {
    const auto gen = [](const int x, const int y) { return TestTile(y); };
    ChunkManager<TestTile> cm(gen);

    for (int i = -100; i <= 100; ++i) {
        REQUIRE(cm.get_tile(0, i).n() == gen(0, i).n());
    }
}
