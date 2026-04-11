/**
 * @file tests.h
 * @brief Static test classes for File System components.
 */

#pragma once
#include "File.h"
#include "Folder.h"
#include <cassert>
#include <iostream>

/**
 * @class FileTest
 * @brief Contains static test methods for the File class.
 */
class FileTest {
public:
  /**
   * @brief Runs all tests for the File class.
   */
  static void runAll() {
    std::cout << "Running File tests..." << std::endl;
    testConstructor();
    testGetSize();
    testGetType();
    std::cout << "All File tests passed!\n" << std::endl;
  }

  static void testConstructor() { File f("test.txt", 100, fileType::Text); }

  static void testGetSize() {
    File f("data.bin", 512, fileType::Image);
    assert(f.getSize() == 512);
  }

  static void testGetType() {
    File f("image.png", 200, fileType::Image);
    assert(f.getType() == fileType::Image);
  }
};

/**
 * @class FolderTest
 * @brief Contains static test methods for the Folder class.
 */
class FolderTest {
public:
  /**
   * @brief Runs all tests for the Folder class.
   */
  static void runAll() {
    std::cout << "Running Folder tests..." << std::endl;
    testEmptyFolder();
    testAddSingleFile();
    testRecursiveSize();
    std::cout << "All Folder tests passed!\n" << std::endl;
  }

  static void testEmptyFolder() {
    Folder f("Empty");
    assert(f.getSize() == 0);
  }

  static void testAddSingleFile() {
    Folder *root = new Folder("Root");
    File *f1 = new File("file.txt", 50, fileType::Text);
    root->addComponent(f1);
    assert(root->getSize() == 50);
    delete root;
  }

  static void testRecursiveSize() {
    Folder *root = new Folder("Root");
    Folder *sub = new Folder("Sub");
    File *f1 = new File("f1.txt", 100, fileType::Text);
    File *f2 = new File("f2.png", 200, fileType::Image);

    sub->addComponent(f1);
    root->addComponent(f2);
    root->addComponent(sub);

    assert(root->getSize() == 300);
    delete root;
  }
};
