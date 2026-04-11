/**
 * @file fileType.h
 * @brief Defines the fileType enumeration for the File System simulation.
 */

#pragma once

/**
 * @enum fileType
 * @brief Represents the specific type of a File component.
 *
 * This strongly-typed enumeration is used by the File class to distinguish
 * between different kinds of files (e.g., Image files vs. Text files) within
 * the simulated file system.
 */
enum class fileType {
  /** * @brief Represents an image file (e.g., .png, .jpg).
   */
  Image,

  /** * @brief Represents a text file (e.g., .txt, .doc).
   */
  Text
};
