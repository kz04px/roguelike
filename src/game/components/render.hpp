#ifndef COMPONENTS_RENDER_HPP
#define COMPONENTS_RENDER_HPP

namespace components {

struct Render {
   public:
    Render(const int x, const int y) : x_{x}, y_{y} {
    }

    [[nodiscard]] int x() const noexcept {
        return x_;
    }

    [[nodiscard]] int y() const noexcept {
        return y_;
    }

    static const int id;

   private:
    int x_;
    int y_;
};

}  // namespace components

#endif
