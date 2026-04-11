#include "File.h"
#include <iostream>

File::File(const std::string &name, int size, fileType type)
    : FSComponent(name), size(size), type(type) {}

int File::getSize() const { return size; }

fileType File::getType() const { return type; }
void File::display() {
  std::cout << "File: " << name << ", Size: " << size << " bytes, Type: ";
  if (type == fileType::Image) {
    std::cout << "Image";
  } else if (type == fileType::Text) {
    std::cout << "Text";
  }
  std::cout << std::endl;
}
