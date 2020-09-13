#ifndef COMPONENTS_RENDER_HPP
#define COMPONENTS_RENDER_HPP

namespace components {

struct Render {
   public:
    Render(const int x, const int y) : m_x{x}, m_y{y} {
    }

    [[nodiscard]] int x() const noexcept {
        return m_x;
    }

    [[nodiscard]] int y() const noexcept {
        return m_y;
    }

    static const int id;

   private:
    int m_x;
    int m_y;
};

}  // namespace components

#endif
