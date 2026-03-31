/**
 * @file main.cpp
 * @author Merlusca Stefan-Andrei
 * @brief Main testing suite for the Character, Wizard, and Knight classes.
 */

#include "knight.h"
#include "wizard.h"
#include <iostream>

/**
 * @brief Main function to test the Character, Wizard, and Knight classes.
 * @return int Returns 0 on successful execution.
 */

int main() {
  int choice = 0;
  bool keepRunning = true;

  while (keepRunning) {
    std::cout << "\n===================================\n";
    std::cout << "      CHARACTER TESTING MENU       \n";
    std::cout << "===================================\n";
    std::cout << "1. Test Base Character\n";
    std::cout << "2. Test Wizard\n";
    std::cout << "3. Test Knight\n";
    std::cout << "4. Exit\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    switch (choice) {
    case 1: {
      std::cout << "\n--- Testing Base Character ---\n";
      Character npc("Town Guard", 100, 1);
      std::cout << "Created: " << npc.getName()
                << " | Health: " << npc.getHealth()
                << " | Level: " << npc.getLevel() << "\n";

      std::cout << "Testing setter (taking 20 damage)...\n";
      npc.setHealth(80);
      std::cout << "New Health: " << npc.getHealth() << "\n";
      break;
    }
    case 2: {
      std::cout << "\n--- Testing Wizard ---\n";
      Wizard w("Gandalf", 80, 10, 50, 20);

      std::cout << "Created Wizard: " << w.getName() << "\n";

      std::cout << "Attempting to cast 'Fireball' (Doesn't know it yet):\n";
      bool success = w.castSpell("Fireball");
      std::cout << "Result: "
                << (success ? "Success!" : "Failed (Not known or no mana)")
                << "\n";
      std::cout << "Adding 'Fireball' to known spells...\n";
      w.addSpell("Fireball");
      if (w.castSpell("Fireball"))
        std::cout << "Successfully cast Fireball after adding it!\n";
      else
        std::cout << "Failed to cast Fireball!\n";
      std::cout << "Casting the spell 4 times (wizard runs out of mana)\n";
      for (int i = 0; i < 4; i++) {
        if (w.castSpell("Fireball"))
          std::cout << "Successfully cast Fireball after adding it!\n";
        else
          std::cout << "Failed to cast Fireball!\n";
      }
      break;
    }
    case 3: {
      std::cout << "\n--- Testing Knight ---\n";

      std::cout << "\nTest A: Valid Armor (0.8)\n";
      Knight k1("Arthur", 120, 5, 0.8f, 25);
      std::cout << "Created Knight: " << k1.getName()
                << " | Health: " << k1.getHealth() << "\n";

      std::cout << "\nTest B: Invalid Armor (1.5)\n";
      Knight k2("Lancelot", 120, 5, 1.5f, 25);

      std::cout << "\nTest C: takeDamage Function\n";
      std::cout << k1.getName()
                << " is taking 5 damage (Armor drops below 0!)...\n";
      k1.takeDamage(5);
      std::cout << k1.getName() << "'s Health is now: " << k1.getHealth()
                << " (Should be 0)\n";
      break;
    }
    case 4: {
      std::cout << "Exiting test suite. Good luck with the submission!\n";
      keepRunning = false;
      break;
    }
    default: {
      std::cout << "Invalid choice. Please enter a number between 1 and 4.\n";
      break;
    }
    }
  }

  return 0;
}
