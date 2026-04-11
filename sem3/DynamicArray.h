#pragma once
#include <iostream>

class DynamicArray {
private:
  float *data;
  unsigned int length;
  unsigned int capacity;

public:
  DynamicArray(unsigned int capacity);
  ~DynamicArray();
  DynamicArray(const DynamicArray &other);
  DynamicArray &operator=(const DynamicArray &other);
  void push_back(float value);
  float &operator[](unsigned int index);
  void setLength(unsigned int newLength);
  void setCapacity(unsigned int newCapacity);
  unsigned int getLength() const;
  unsigned int getCapacity() const;
  friend std::ostream &operator<<(std::ostream &os, const DynamicArray &arr);
};
