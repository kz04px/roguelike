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
    Key_F1,
    Key_F2,
    Key_F3,
    Key_F4,
    Key_F5,
    Key_F6,
    Key_F7,
    Key_F8,
    Key_F9,
    Key_F10,
    Key_F11,
    Key_F12,
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
        return m_keystates[static_cast<int>(t)];
    }

    void set_key(const KeyType t, const KeyState k) {
        assert(static_cast<int>(t) < 512);
        m_keystates[static_cast<int>(t)] = k;
    }

    void set_key(const int t, const KeyState k) {
        assert(t < 512);
        m_keystates[t] = k;
    }

   private:
    KeyState m_keystates[512];
};

#endif
