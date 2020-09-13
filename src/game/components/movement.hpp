#ifndef COMPONENTS_MOVEMENT_HPP
#define COMPONENTS_MOVEMENT_HPP

namespace components {

struct Movement {
   public:
    Movement() : m_left{false}, m_right{false}, m_up{false}, m_down{false} {
    }

    static const int id;
    bool m_left;
    bool m_right;
    bool m_up;
    bool m_down;
};

}  // namespace components

#endif
