#ifndef COMPONENTS_POSITION_HPP
#define COMPONENTS_POSITION_HPP

namespace components {

struct Position {
   public:
    Position(const int x, const int y) : x_{x}, y_{y} {
    }

    static const int id;
    int x_;
    int y_;
};

}  // namespace components

#endif
