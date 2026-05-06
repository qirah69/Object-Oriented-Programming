#pragma once
#include "SortedIndexedList.h"
#include <exception>

// DO NOT CHANGE THIS PART
template <typename T> class ListIterator {
  friend class SortedIndexedList<T>;

private:
  const SortedIndexedList<T> &list;
  ListIterator(const SortedIndexedList<T> &list);
  int currentElem;

public:
  void first();
  void next();
  bool valid() const;
  T getCurrent() const;
};

// constructor. time complexity: theta(1)
// initializes iterator to point to the first element (head)
template <typename T>
ListIterator<T>::ListIterator(const SortedIndexedList<T> &list) : list(list) {
  currentElem = list.head;
}

// moves iterator back to the first element. time complexity: theta(1)
template <typename T> void ListIterator<T>::first() { currentElem = list.head; }

// advances iterator to the next element. time complexity: theta(1)
// follows the 'next' index in the array. throws exception if already invalid
template <typename T> void ListIterator<T>::next() {
  if (!valid()) {
    throw std::exception();
  }
  currentElem = list.nodes[currentElem].next;
}

// checks if iterator points to a valid element. time complexity: theta(1)
// valid as long as the current index is not -1
template <typename T> bool ListIterator<T>::valid() const {
  return currentElem != -1;
}

// returns the value of the current element. time complexity: theta(1)
// throws exception if the iterator is out of bounds
template <typename T> T ListIterator<T>::getCurrent() const {
  if (!valid()) {
    throw std::exception();
  }
  return list.nodes[currentElem].info;
}
template <typename T> ListIterator<T> SortedIndexedList<T>::iterator() {
  return ListIterator(*this);
}
