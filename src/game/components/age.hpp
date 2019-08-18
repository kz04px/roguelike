#ifndef COMPONENTS_AGE_HPP
#define COMPONENTS_AGE_HPP

namespace components {

struct Age {
   public:
    Age(const unsigned int c, const unsigned int m) : current_{c}, max_{m} {
    }

    static const int id;
    unsigned int current_;
    unsigned int max_;
};

}  // namespace components

#endif
