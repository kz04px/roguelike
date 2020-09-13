#ifndef COMPONENTS_POSITION_HPP
#define COMPONENTS_POSITION_HPP

namespace components {

struct Position {
   public:
    Position(const int x, const int y) : m_x{x}, m_y{y} {
    }

    static const int id;
    int m_x;
    int m_y;
};

}  // namespace components

#endif
