/**
 * @file main.cpp
 * @brief Entry point for the File System simulation.
 *
 * This file contains the execution logic which demonstrates the usage of the
 * composite pattern implemented in the File System architecture. It creates
 * a hierarchical structure of folders and files, displays them, and
 * safely cleans up the allocated memory.
 */

#include "File.h"
#include "Folder.h"
#include "tests.h"
#include <iostream>

/**
 * @brief The main execution function.
 * * Demonstrates the core capabilities of the file system: adding files
 * and folders, displaying their contents recursively, reporting the total
 * size of the directory tree, and verifying memory management.
 * * @return int Returns 0 upon successful execution.
 */
int main() {
  FileTest::runAll();
  FolderTest::runAll();

  std::cout << "--- Starting File System Simulation ---\n" << std::endl;

  // 1. Create a root folder
  Folder *root = new Folder("Root_Directory");

  // 2. Create some files
  File *text1 = new File("notes.txt", 15, fileType::Text);
  File *img1 = new File("vacation.png", 2500, fileType::Image);

  // 3. Add files to the root
  root->addComponent(text1);
  root->addComponent(img1);

  // 4. Create a subfolder and put a file in it
  Folder *subFolder = new Folder("Secret_Docs");
  File *secretText = new File("passwords.txt", 5, fileType::Text);
  subFolder->addComponent(secretText);

  // 5. Add the subfolder to the root
  root->addComponent(subFolder);

  // 6. Display everything
  root->display();

  // 7. Clean up memory
  delete root;

  std::cout << "\n--- Simulation Ended Safely ---" << std::endl;
  return 0;
}
