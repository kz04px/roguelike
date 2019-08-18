#ifndef INPUTS_HPP
#define INPUTS_HPP

#include <cassert>

enum KeyType
{
    Key_A = 0,
    Key_B,
    Key_C,
    Key_D,
    Key_E,
    Key_F,
    Key_G,
    Key_H,
    Key_I,
    Key_J,
    Key_K,
    Key_L,
    Key_M,
    Key_N,
    Key_O,
    Key_P,
    Key_Q,
    Key_R,
    Key_S,
    Key_T,
    Key_U,
    Key_V,
    Key_W,
    Key_X,
    Key_Y,
    Key_Z,
    Key_ESC,
};

enum class KeyState
{
    Down = 0,
    Up
};

class Inputs {
   public:
    Inputs() {
        for (int i = 0; i < 26; ++i) {
            set_key(static_cast<KeyType>(i), KeyState::Up);
        }
    }

    static Inputs *get() {
        static Inputs i;
        return &i;
    }

    [[nodiscard]] KeyState get_key(const KeyType t) const noexcept {
        assert(static_cast<int>(t) < 512);
        return keystates_[static_cast<int>(t)];
    }

    void set_key(const KeyType t, const KeyState k) {
        assert(static_cast<int>(t) < 512);
        keystates_[static_cast<int>(t)] = k;
    }

    void set_key(const int t, const KeyState k) {
        assert(t < 512);
        keystates_[t] = k;
    }

   private:
    KeyState keystates_[512];
};

#endif
