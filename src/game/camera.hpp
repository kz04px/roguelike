#ifndef CAMERA_HPP
#define CAMERA_HPP

class Camera {
   public:
    Camera(const int x, const int y, const int w, const int h)
        : x_{x}, y_{y}, w_{w}, h_{h}, half_w_{w / 2}, half_h_{h / 2} {
    }

    [[nodiscard]] int x() const noexcept {
        return x_;
    }

    [[nodiscard]] int y() const noexcept {
        return y_;
    }

    [[nodiscard]] int w() const noexcept {
        return w_;
    }

    [[nodiscard]] int h() const noexcept {
        return h_;
    }

    int x_;
    int y_;
    int w_;
    int h_;
    int half_w_;
    int half_h_;

   private:
};

#endif
