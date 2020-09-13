#ifndef COMPONENTS_TIMER_HPP
#define COMPONENTS_TIMER_HPP

namespace components {

struct Timer {
   public:
    Timer(const int t) : m_time_left{t} {
    }

    static const int id;
    int m_time_left;
};

}  // namespace components

#endif
