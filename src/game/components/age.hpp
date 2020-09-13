#ifndef COMPONENTS_AGE_HPP
#define COMPONENTS_AGE_HPP

namespace components {

struct Age {
   public:
    Age(const unsigned int c, const unsigned int m) : m_current{c}, m_max{m} {
    }

    static const int id;
    unsigned int m_current;
    unsigned int m_max;
};

}  // namespace components

#endif
