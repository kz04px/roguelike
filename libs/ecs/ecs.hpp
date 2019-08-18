#ifndef ECS_HPP
#define ECS_HPP

#include <cassert>
#include <cstdint>
#include <iomanip>  // std::setprecision
#include <iostream>
#include <memory>
#include <set>
#include <stack>
#include <unordered_map>
#include <vector>
#include "entity.hpp"
#include "store.hpp"

class ECS {
   public:
    // Create a new entity
    Entity create() {
        /*
        if (!reuse_.empty()) {
            Entity e = reuse_.top();
            reuse_.pop();
            entities_.insert(e);
            return e;
        }
        */
        entities_.insert(next_);
        return next_++;
    }

    // Flag an entity for removal
    void remove(const Entity e) {
        remove_.push_back(e);
    }

    // Add a component to an entity
    template <typename T, typename... Args>
    void add(const Entity e, Args &&... args) {
        assert(registered<T>());
        auto &store = static_cast<Store<T> &>(*stores_[T::id]);
        store.add(e, T(args...));
    }

    // Register a component
    template <typename T>
    void reg() {
        assert(!registered<T>());
        stores_[T::id].reset(static_cast<StoreBase *>(new Store<T>()));
    }

    // Check if registered
    template <typename T>
    bool registered() {
        return stores_.find(T::id) != stores_.end();
    }

    // Get the entity's specified component
    template <typename T>
    T &get(const Entity e) {
        assert(registered<T>());
        auto &store = static_cast<Store<T> &>(*stores_[T::id]);
        return store.get(e);
    }

    // Does the component have the entity?
    template <typename T>
    bool asd(const Entity e) {
        auto &store = static_cast<Store<T> &>(*stores_[T::id]);
        return store.has(e);
    }

    // Who even knows what this is tbh fam
    template <typename A>
    bool thing(const Entity e) {
        return asd<A>(e);
    }

    // Who even knows what this is tbh fam
    template <typename A, typename B>
    bool thing(const Entity e) {
        return asd<A>(e) && asd<B>(e);
    }

    // Who even knows what this is tbh fam
    template <typename A, typename B, typename C>
    bool thing(const Entity e) {
        return asd<A>(e) && asd<B>(e) && asd<C>(e);
    }

    // Get the entities with the specified components
    template <typename... Args>
    std::vector<Entity> entities() {
        std::vector<Entity> list;

        for (const auto e : entities_) {
            const bool all = thing<Args...>(e);
            if (all) {
                list.push_back(e);
            }
        }

        return list;
    }

    // Get the entities with the specified components
    template <typename... Args, typename T>
    T filter(const T &list) {
        T nlist;
        for (const auto e : entities_) {
            const bool all = thing<Args...>(e);
            if (all) {
                nlist.insert(e);
            }
        }

        return nlist;
    }

    // Is this entity to be removed?
    bool removing(const Entity e) {
        for (const auto ent : remove_) {
            if (ent == e) {
                return true;
            }
        }
        return false;
    }

    // Housekeeping
    void update() {
        for (const auto e : remove_) {
            for (const auto &[key, val] : stores_) {
                if ((*val).has(e)) {
                    (*val).remove(e);
                }
            }
            entities_.erase(e);
        }

        remove_.clear();
    }

    // Print details
    void print() const {
        std::uint64_t total = 0ULL;
        std::cout << "Component Types:" << std::endl;
        for (const auto &[key, val] : stores_) {
            total += (*val).size();
            std::cout << "<id:" << key << "> "
                      << "<size:" << (*val).size() << ">" << std::endl;
        }
        std::cout << "Entities: " << entities_.size() << std::endl;
        std::cout << "Components: " << total << std::endl;
        std::cout << "Avg. components: " << std::setprecision(2)
                  << (float)total / entities_.size() << std::endl;
    }

   private:
    // Entities
    std::set<Entity> entities_;
    std::vector<Entity> remove_;
    Entity next_ = 0;
    // Components
    std::unordered_map<int, std::unique_ptr<StoreBase>> stores_;
};

#endif
