#include "character.h"
#include <string>

Character::Character(std::string n, int h, int l)
    : name(n), health(h), level(l) {};

void Character::setName(std::string newName) { name = newName; };

void Character::setHealth(unsigned int newHealth) { health = newHealth; };

void Character::setLevel(unsigned int newLevel) { level = newLevel; };

std::string Character::getName() { return name; };

int Character::getHealth() { return health; };

int Character::getLevel() { return level; };
