#ifndef GAME_SPELL_MANAGER_HPP
#define GAME_SPELL_MANAGER_HPP

#include <string>
#include <vector>

struct Spell {
   public:
    Spell(const std::string &name, const int m) : m_name{name}, m_mana{m} {
    }

    std::string m_name;
    int m_mana;
};

class SpellManager {
   public:
    void add(const Spell &s) {
        m_spells.push_back(s);
    }

   private:
    std::vector<Spell> m_spells;
};

#endif
