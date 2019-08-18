#ifndef STORE_HPP
#define STORE_HPP

#include <cassert>
#include <unordered_map>
#include "entity.hpp"

class StoreBase {
   public:
    // virtual ~StoreBase() = default;
    virtual bool has(const Entity e) const noexcept = 0;
    virtual void remove(const Entity e) = 0;
    virtual int size() const noexcept = 0;
};

template <typename T>
class Store : public StoreBase {
   public:
    // Add an entity to the store
    void add(const Entity e, T t) {
        components_.insert({e, t});
    }

    // Count the number of entities
    int size() const noexcept {
        return components_.size();
    }

    // Remove an entity from the store
    void remove(const Entity e) {
        components_.erase(e);
    }

    // Has entity
    bool has(const Entity e) const noexcept {
        return components_.find(e) != components_.end();
    }

    // Get an entity's component
    T &get(const Entity e) {
        assert(has(e));
        return components_.find(e)->second;
    }

   private:
    std::unordered_map<Entity, T> components_;
};

#endif
