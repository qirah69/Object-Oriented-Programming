/**
 *@file main.cpp
 *@brief This program defines a BankAccount class with basic functionalities
 * such as deposit and withdraw. It also overloads the << operator to display
 * account information.
 */
#include <iostream>
#include <ostream>

class BankAccount {
private:
  /**
   * @brief Store the name of the account holder, the account ID, and the
   * current balance.
   *
   * @param name The name of the account holder.
   * @param id The unique identifier for the account.
   * @param balance The current balance of the account.
   *
   */

  std::string name;
  unsigned int id;
  double balance;

public:
  /**
   * @brief Constructor to initialize a BankAccount object with the account
   * holder's name, ID, and initial balance.
   *
   * @param PersonName The name of the account holder.
   * @param UserID The unique identifier for the account.
   * @param InitialBalance The initial balance of the account.
   *
   * @returns A BankAccount object initialized with the provided parameters.
   */
  BankAccount(std::string PersonName, unsigned int UserID,
              double InitialBalance)
      : name(PersonName), id(UserID), balance(InitialBalance) {}

  /**
   * @brief Method to deposit a specified amount into the account.
   *
   * @param amount The amount to be deposited into the account.
   *
   * @returns void. The method updates the balance of the account by adding the
   * deposited amount.
   */

  void deposit(double amount) { balance += amount; }
  /**
   *@brief Method to withdraw a specified amount from the account.
   *
   * @param amount The amount to be withdrawn from the account.
   *
   * @returns void. The method checks if the withdrawal amount is greater than
   * the current balance. If it is, it prints an error message and does not
   * update the balance. Otherwise, it subtracts the withdrawal amount from the
   * balance.
   */
  void withdraw(double amount) {
    if (amount > balance) {
      std::cout << "Insufficient funds" << std::endl;
      return;
    }
    balance -= amount;
  }
  /**
   * @brief Overloaded << operator to display the account information in a
   * formatted manner.
   *
   * @param os The output stream to which the account information will be sent.
   * @param account The BankAccount object whose information is to be displayed.
   *
   * @returns A reference to the output stream after inserting the account
   * information into it. The account information includes the name, ID, and
   * balance of the account holder.
   */

  friend std::ostream &operator<<(std::ostream &os, const BankAccount &account);
};

std::ostream &operator<<(std::ostream &os, const BankAccount &account) {
  os << "Name: " << account.name << ", ID: " << account.id << ", Balance: $"
     << account.balance;
  return os;
}
