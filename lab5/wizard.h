/**
 * @file wizard.h
 * @author Merlusca Stefan-Andrei
 * @brief This file contains the declaration of the Wizard class, which inherits
 * from Character.
 */

#pragma once
#include "character.h"
#include <vector>

/**
 * @class Wizard
 * @brief The Wizard class represents a magical character with the ability to
 * cast spells. It inherits from the Character class and adds attributes and
 * methods specific to a wizard, such as mana, spell power, and a list of known
 * spells.
 */

class Wizard : public Character {
private:
  int mana; ///< The amount of magical energy the wizard has, which is consumed
            ///< when casting spells.
  std::vector<std::string>
      spells; ///< The list of spells known by the wizard, which can be cast if
              ///< the wizard has enough mana.
  int spellPower; ///< The strength of the wizard's spells, which can affect the
                  ///< damage dealt to enemies or the effectiveness of the
                  ///< spell.

  bool knowSpell(
      const std::string
          &spell); ///< This private method checks if the wizard knows a
                   ///< specific spell, returning true if the spell is in the
                   ///< wizard's list of known spells and false otherwise.

public:
  /**
   * @brief Constructs a new Wizard object with the specified name, health,
   * level, mana, and spell power. The constructor initializes the wizard's
   * attributes and prepares it for use in the game.
   * @param name The name of the wizard, which is passed to the base Character
   * class constructor
   * @param health The health points of the wizard, which is passed to the base
   * Character class constructor
   * @param level The level of the wizard, which is passed to the base Character
   * class constructor
   * @param mana The amount of magical energy the wizard has, which is specific
   * to the Wizard class
   * @param spellPower The strength of the wizard's spells, which is specific to
   * the Wizard class
   */

  Wizard(std::string name, int health, int level, int mana, int spellPower);

  /**
   * @brief Casts a spell if the wizard knows it and has enough mana. This
   * method checks if the specified spell is in the wizard's list of known
   * spells and if the wizard has sufficient mana to cast it. If both conditions
   * are met, the spell is cast successfully, and the method returns true.
   * Otherwise, it returns false, indicating that the spell could not be cast
   * due to either lack of knowledge or insufficient mana.
   * @param spell The name of the spell to be cast, which is checked against the
   * wizard
   * @returns true if the spell is successfully cast, false otherwise
   */

  bool castSpell(const std::string &spell);

  /**
   * @brief Adds a new spell to the wizard's list of known spells. This method
   * allows the wizard to learn new spells by adding the specified spell name to
   * the wizard's collection of known spells. Once a spell is added, the wizard
   * can attempt to cast it using the castSpell method, provided they have
   * enough mana.
   * @param spell The name of the spell to be added to the wizard's list of
   * known
   */

  void addSpell(const std::string &spell);
};
