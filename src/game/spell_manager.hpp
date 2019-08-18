#ifndef GAME_SPELL_MANAGER_HPP
#define GAME_SPELL_MANAGER_HPP

#include <string>
#include <vector>

struct Spell {
   public:
    Spell(const std::string &name, const int m) : name_{name}, mana_{m} {
    }

    std::string name_;
    int mana_;
};

class SpellManager {
   public:
    void add(const Spell &s) {
        spells_.push_back(s);
    }

   private:
    std::vector<Spell> spells_;
};

#endif
