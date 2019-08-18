#ifndef COMPONENTS_HEALTH_HPP
#define COMPONENTS_HEALTH_HPP

namespace components {

struct Health {
   public:
    Health(const int h) : current_{h}, initial_{h} {
    }

    static const int id;
    int current_;
    int initial_;
};

}  // namespace components

#endif
