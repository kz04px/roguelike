#ifndef COMPONENTS_FLAMMABLE_HPP
#define COMPONENTS_FLAMMABLE_HPP

namespace components {

struct Flammable {
   public:
    Flammable(const bool f) : on_fire{f} {
    }

    static const int id;
    bool on_fire;
};

}  // namespace components

#endif
