#ifndef COMPONENTS_TIMER_HPP
#define COMPONENTS_TIMER_HPP

namespace components {

struct Timer {
   public:
    Timer(const int t) : time_left_{t} {
    }

    static const int id;
    int time_left_;
};

}  // namespace components

#endif
