#include "knight.h"
#include "character.h"
#include <iostream>

Knight::Knight(std::string name, int health, int level, float inputArmor,
               int swordDamage)
    : Character(name, health, level), swordDamage(swordDamage) {
  if (inputArmor < 0.0 || inputArmor > 1.0) {
    std::cout << "Invalid armor value. Setting armor to 0." << std::endl;
    armor = 0;
  } else {
    armor = inputArmor;
  }
}

void Knight::takeDamage(int damage) {
  if (damage <= 0) {
    return;
  }

  if (armor > 0 && getHealth() > 0) {
    armor -= damage;
    if (armor <= 0) {
      setHealth(0);
    }
  } else {
    std::cout << "The knight has no armor and no health left." << std::endl;
  }
};
