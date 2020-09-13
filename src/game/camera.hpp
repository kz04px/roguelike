#ifndef CAMERA_HPP
#define CAMERA_HPP

class Camera {
   public:
    Camera(const int x, const int y, const int w, const int h)
        : m_x{x}, m_y{y}, m_w{w}, m_h{h}, m_half_w{w / 2}, m_half_h{h / 2} {
    }

    [[nodiscard]] int x() const noexcept {
        return m_x;
    }

    [[nodiscard]] int y() const noexcept {
        return m_y;
    }

    [[nodiscard]] int w() const noexcept {
        return m_w;
    }

    [[nodiscard]] int h() const noexcept {
        return m_h;
    }

    int m_x;
    int m_y;
    int m_w;
    int m_h;
    int m_half_w;
    int m_half_h;

   private:
};

#endif
