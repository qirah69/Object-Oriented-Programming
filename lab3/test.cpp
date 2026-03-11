/**
 * @file test.cpp
 * @brief Test program for BankAccount class
 */

#include "main.cpp"
#include <iostream>

// --- Test Implementation ---
/**
 * @brief Main function to test the BankAccount class
 *
 * @params None
 *
 * @returns 0 on successful execution
 */

int main() {
  std::cout << "\n\n\n--- Creating Account ---\n";
  BankAccount myAccount("Alex", 98765, 250.00);
  std::cout << myAccount << std::endl;

  std::cout << "\n\n\n--- Depositing $50.00 ---\n";
  myAccount.deposit(50.00);
  std::cout << myAccount << std::endl;

  std::cout << "\n\n\n--- Withdrawing $100.00 ---\n";
  myAccount.withdraw(100.00);
  std::cout << myAccount << std::endl;

  std::cout << "\n\n\n--- Attempting to Withdraw $500.00 ---\n";
  myAccount.withdraw(
      500.00); // This should trigger the insufficient funds message
  std::cout << myAccount << std::endl;

  return 0;
}
