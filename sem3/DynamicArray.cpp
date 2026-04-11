#include "DynamicArray.h"
#include <stdexcept>
DynamicArray::DynamicArray(unsigned int capacity)
    : length(0), capacity(capacity) {
  this->data = new float[this->capacity];
}

DynamicArray::~DynamicArray() {
  delete[] this->data;
  data = nullptr;
}

DynamicArray::DynamicArray(const DynamicArray &other)
    : length(other.length), capacity(other.capacity) {
  this->data = new float[this->capacity];
  for (unsigned int i = 0; i < this->length; i++) {
    this->data[i] = other.data[i];
  }
}

DynamicArray &DynamicArray::operator=(const DynamicArray &other) {
  if (this == &other) {
    return *this;
  }
  delete[] this->data;
  this->length = other.length;
  this->capacity = other.capacity;
  this->data = new float[this->capacity];
  for (unsigned int i = 0; i < this->length; i++) {
    this->data[i] = other.data[i];
  }
  return *this;
}

void resize(float *&data, unsigned int dataLength, unsigned int newCapacity) {
  float *newData = new float[newCapacity];

  for (unsigned int i = 0; i < dataLength; i++) {
    newData[i] = data[i];
  }
  delete[] data;
  data = newData;
}

void DynamicArray::push_back(float value) {
  if (this->length >= this->capacity) {
    resize(this->data, this->length, this->capacity * 2);
    this->capacity *= 2;
  }
  this->data[this->length] = value;
  this->length++;
}

float &DynamicArray::operator[](unsigned int index) {
  if (index >= this->length) {
    throw std::out_of_range("Index out of range");
  }
  return this->data[index];
}

void DynamicArray::setLength(unsigned int newLength) {
  if (newLength > this->capacity) {
    resize(this->data, this->length, newLength);
    this->capacity = newLength;
  }
  this->length = newLength;
}
void DynamicArray::setCapacity(unsigned int newCapacity) {
  if (newCapacity < this->length) {
    throw std::invalid_argument(
        "New capacity cannot be less than current length");
  }
  resize(this->data, this->length, newCapacity);
  this->capacity = newCapacity;
}

unsigned int DynamicArray::getLength() const { return this->length; }
unsigned int DynamicArray::getCapacity() const { return this->capacity; }

std::ostream &operator<<(std::ostream &os, const DynamicArray &arr) {
  for (unsigned int i = 0; i < arr.length; i++) {
    os << arr.data[i] << "\n";
  }
  return os;
}
