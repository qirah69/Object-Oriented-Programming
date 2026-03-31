/**
 * @file character.h
 * @author Merlusca Stefan-Andrei
 * @brief This file contains the declaration of the Character class, which
 * represents a character in a game with attributes such as name, health, and
 * level.
 */

#pragma once
#include <string>

/**
 * @class Character
 * @brief Represents a character in a game with attributes such as name, health,
 * and level.
 */

class Character {
private:
  std::string name;    ///< The name of the character.
  unsigned int health; ///< The health points of the character.
  unsigned int level;  ///< The level of the character.

public:
  /**
   * @brief Constructs a new Character object with the given name, health, and
   * level.
   * @param name The name of the character.
   * @param health The health points of the character.
   * @param level The level of the character.
   */

  Character(std::string name, int health, int level);

  /**
   * @brief Sets the name of the character.
   * @param name The new name of the character.
   */

  void setName(std::string name);

  /**
   * @brief Sets the health points of the character.
   * @param health The new health points of the character.
   */

  void setHealth(unsigned int health);

  /**
   * @brief Sets the level of the character.
   * @param level The new level of the character.
   */

  void setLevel(unsigned int level);

  /**
   * @brief Gets the name of the character.
   * @return The name of the character.
   */

  std::string getName();

  /**
   * @brief Gets the health points of the character.
   * @return The health points of the character.
   */

  int getHealth();

  /**
   * @brief Gets the level of the character.
   * @return The level of the character.
   */

  int getLevel();
};
