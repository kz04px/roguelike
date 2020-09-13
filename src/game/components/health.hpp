#ifndef COMPONENTS_HEALTH_HPP
#define COMPONENTS_HEALTH_HPP

namespace components {

struct Health {
   public:
    Health(const int h) : m_current{h}, m_initial{h} {
    }

    static const int id;
    int m_current;
    int m_initial;
};

}  // namespace components

#endif
