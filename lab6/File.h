/**
 * @file File.h
 * @brief Defines the File class for the File System simulation.
 */

#pragma once
#include "FSComponent.h"
#include "fileType.h"

/**
 * @class File
 * @brief A concrete class representing an individual file in the file system.
 *
 * The File class inherits from FSComponent and acts as a "leaf" node
 * in the composite pattern. Unlike a Folder, a File cannot contain
 * other components. It stores its own specific size and file type.
 */
class File : public FSComponent {
private:
  /**
   * @brief The size of the file in bytes (or abstract units).
   */
  int size;

  /**
   * @brief The specific type of the file (e.g., Image, Text).
   */
  fileType type;

public:
  /**
   * @brief Constructs a new File object.
   * @param name The name of the file (passed up to the FSComponent base class).
   * @param size The size of the file.
   * @param type The type of the file, based on the fileType enumeration.
   */
  File(const std::string &name, int size, fileType type);

  /**
   * @brief Retrieves the size of this specific file.
   * @return int The size attribute of the file.
   */
  int getSize() const override;

  /**
   * @brief Displays the file's details.
   *
   * Prints the file's name, size, and type to the standard output.
   */
  void display() override;

  /**
   * @brief Retrieves the specific type of the file.
   * @return fileType The enumeration value representing this file's type.
   */
  fileType getType() const;
};
