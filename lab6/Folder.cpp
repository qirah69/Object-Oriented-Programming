#include "Folder.h"
#include <iostream>

Folder::Folder(const std::string &name) : FSComponent(name) {}

Folder::~Folder() {
  for (FSComponent *component : components) {
    delete component;
  }
}

int Folder::getSize() const {
  int totalSize = 0;
  for (const FSComponent *component : components) {
    totalSize += component->getSize();
  }
  return totalSize;
}

void Folder::display() {
  std::cout << "Folder: " << name << ", Total Size: " << getSize() << " bytes"
            << std::endl;
  for (FSComponent *component : components) {
    component->display();
  }
}

void Folder::addComponent(FSComponent *component) {
  if (component != nullptr) {
    components.push_back(component);
  }
}
