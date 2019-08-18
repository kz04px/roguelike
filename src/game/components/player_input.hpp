#ifndef COMPONENTS_PLAYER_INPUT_HPP
#define COMPONENTS_PLAYER_INPUT_HPP

namespace components {

struct PlayerInput {
   public:
    PlayerInput()
        : left_{false}, right_{false}, up_{false}, down_{false}, use_{false} {
    }

    static const int id;
    bool left_;
    bool right_;
    bool up_;
    bool down_;
    bool use_;
};

}  // namespace components

#endif
