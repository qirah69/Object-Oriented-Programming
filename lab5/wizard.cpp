#include "wizard.h"
#include "character.h"
#include <iostream>
#include <vector>

Wizard::Wizard(std::string name, int health, int level, int mana,
               int spellPower)
    : Character(name, health, level), mana(mana), spellPower(spellPower) {}

bool Wizard::knowSpell(const std::string &spell) {
  for (size_t i = 0; i < spells.size(); ++i) {
    if (spells[i] == spell) {
      return true;
    }
  }
  return false;
}

bool Wizard::castSpell(const std::string &spell) {

  std::string wizName = getName();

  if (spells.empty()) {
    std::cout << wizName << " has no spells to cast." << std::endl;
    return false;
  }

  if (!knowSpell(spell)) {
    std::cout << wizName << " does not know the spell " << spell << "."
              << std::endl;
    return false;
  }

  if (mana >= spellPower) {
    mana -= 10;
    std::cout << wizName << " casts " << spell << "!" << std::endl;
    return true;
  } else {
    std::cout << wizName << " does not have enough mana to cast " << spell
              << "." << std::endl;
    return false;
  }
}

void Wizard::addSpell(const std::string &spell) { spells.push_back(spell); }
