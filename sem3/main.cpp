#include "DynamicArray.h"
#include <iostream>
int main() {
  DynamicArray arr;
  for (int i = 0; i < 10; i++) {
    arr.push_back(i * 1.5f);
  }
  std::cout << "Array length: " << arr.getLength() << std::endl;
  std::cout << "Array capacity: " << arr.getLength() << std::endl;
  std::cout << "Array contents: ";
  for (int i = 0; i < 10; i++) {
    std::cout << arr[i] << " ";
  }
  std::cout << arr << std::endl;

  arr.push_back(15.0f);
  arr.push_back(20.0f);
  std::cout << "After adding more elements:" << std::endl;
  std::cout << "Array length: " << arr.getLength() << std::endl;
  std::cout << "Array capacity: " << arr.getCapacity() << std::endl;
  std::cout << "Array contents: " << std::endl;
  std::cout << arr << std::endl;
  return 0;
}
