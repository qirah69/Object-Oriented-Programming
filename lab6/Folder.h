/**
 * @file Folder.h
 * @brief Defines the Folder class for the File System simulation.
 */

#pragma once
#include "FSComponent.h"
#include <vector>

/**
 * @class Folder
 * @brief A composite class representing a directory in the file system.
 *
 * The Folder class inherits from FSComponent and acts as a composite object.
 * It can contain multiple FSComponent objects, allowing it to store both
 * Files and other sub-Folders. It is also responsible for managing and
 * freeing the memory of the components it owns.
 */
class Folder : public FSComponent {
private:
  /**
   * @brief A polymorphic container storing pointers to the folder's contents.
   */
  std::vector<FSComponent *> components;

public:
  /**
   * @brief Constructs a new Folder object.
   * @param n The name of the folder.
   */
  Folder(const std::string &n);

  /**
   * @brief Destroys the Folder object and cleans up memory.
   *
   * Iterates through the components vector and safely deletes all
   * dynamically allocated FSComponent objects contained within to prevent
   * memory leaks.
   */
  ~Folder() override;

  /**
   * @brief Calculates the total size of the folder.
   *
   * Recursively queries the sizes of all contained files and subfolders
   * and sums them up.
   * @return int The total size of all contents in the folder.
   */
  int getSize() const override;

  /**
   * @brief Displays the folder's details and recursively displays its contents.
   *
   * Prints the folder's name and total size, then calls the display()
   * method on every component stored inside it.
   */
  void display() override;

  /**
   * @brief Adds a new component (File or sub-Folder) to this folder.
   * @param c A pointer to the dynamically allocated FSComponent to be added.
   */
  void addComponent(FSComponent *c);
};
