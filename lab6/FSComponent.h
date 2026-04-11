/**
 * @file FSComponent.h
 * @brief Defines the abstract base class for the File System simulation.
 */

#pragma once
#include <string>

/**
 * @class FSComponent
 * @brief An abstract base class representing a generic component in the file
 * system.
 *
 * This class serves as the foundation for the Composite design pattern.
 * Both File (leaf) and Folder (composite) classes inherit from this base class,
 * allowing them to be treated uniformly through polymorphism.
 */
class FSComponent {
protected:
  /**
   * @brief The name or path of the file system component.
   * * Marked as protected so derived classes (File, Folder) can access
   * it directly without needing a getter method.
   */
  std::string name;

public:
  /**
   * @brief Constructs a new FSComponent object.
   * @param name The name to be assigned to the component.
   */
  FSComponent(const std::string &name) : name(name) {};

  /**
   * @brief Virtual destructor.
   *
   * A virtual destructor is mandatory for abstract base classes to ensure
   * that when a derived object is deleted via a base class pointer,
   * the derived class's destructor is properly invoked.
   */
  virtual ~FSComponent() = default;

  /**
   * @brief Retrieves the size of the component.
   * * This is a pure virtual function, meaning every derived class must
   * provide its own implementation.
   * @return int The size of the component in bytes.
   */
  virtual int getSize() const = 0;

  /**
   * @brief Displays the component's details.
   *
   * This is a pure virtual function. Derived classes will implement this
   * to print their specific information (e.g., file details or folder
   * hierarchy).
   */
  virtual void display() = 0;
};
