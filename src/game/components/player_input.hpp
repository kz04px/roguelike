#ifndef COMPONENTS_PLAYER_INPUT_HPP
#define COMPONENTS_PLAYER_INPUT_HPP

namespace components {

struct PlayerInput {
   public:
    PlayerInput() : m_left{false}, m_right{false}, m_up{false}, m_down{false}, m_use{false} {
    }

    static const int id;
    bool m_left;
    bool m_right;
    bool m_up;
    bool m_down;
    bool m_use;
};

}  // namespace components

#endif
