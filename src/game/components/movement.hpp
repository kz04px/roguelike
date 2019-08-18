#ifndef COMPONENTS_MOVEMENT_HPP
#define COMPONENTS_MOVEMENT_HPP

namespace components {

struct Movement {
   public:
    Movement() : left_{false}, right_{false}, up_{false}, down_{false} {
    }

    static const int id;
    bool left_;
    bool right_;
    bool up_;
    bool down_;
};

}  // namespace components

#endif
