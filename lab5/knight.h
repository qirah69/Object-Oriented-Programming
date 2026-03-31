/**
 * @file knight.h
 * @author Merlusca Stefan-Andrei
 * @brief This file contains the declaration of the Knight class, which inherits
 * from the Character class.
 */

#pragma once
#include "character.h"
#include <string>
/**
 * @class Knight
 * @brief The Knight class represents a character that has armor and can deal
 * damage with a sword.
 * * The Knight class inherits from the Character class and adds additional
 * attributes and methods specific to a knight character.
 */
class Knight : public Character {
private:
  float armor;     ///< The armor value that reduces incoming damage.
  int swordDamage; ///< The damage value that the knight can deal with a sword.

public:
  /**
   * @brief Constructor for the Knight class.
   * @param name The name of the knight character.
   * @param health The health points of the knight character.
   * @param level The level of the knight character.
   * @param inputArmor The armor value that reduces incoming damage for the
   * knight character.
   * @param swordDamage The damage value that the knight can deal with a sword.
   */
  Knight(std::string name, int health, int level, float inputArmor,
         int swordDamage);
  /**
   * @brief Method to calculate the damage taken by the knight character after
   * applying armor reduction.
   * @param damage The initial damage value before applying armor reduction.
   */
  void takeDamage(int damage);
};
