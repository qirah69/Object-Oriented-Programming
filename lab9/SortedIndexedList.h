#pragma once
#include "SortedIndexedList.h"
#include <exception>
#include <iostream>

// DO NOT INCLUDE LISTITERATOR

// DO NOT CHANGE THIS PART
template <typename T> class ListIterator;
template <typename T> using Relation = bool (*)(T, T);
template <typename T> class SortedIndexedList {
private:
  friend class ListIterator<T>;

private:
  struct Node {
    T info;
    int next;
    int prev;
  };

  Node *nodes;
  int cap;
  int tail;
  int head;
  int firstEmpty;
  int length;
  Relation<T> rel;
  void resize();
  int allocate();
  void freeNode(int pos);

public:
  // constructor
  SortedIndexedList(Relation<T> r);

  // returns the size of the list
  int size() const;

  // checks if the list is empty
  bool isEmpty() const;

  // returns an element from a position
  // throws exception if the position is not valid
  T getElement(int pos) const;

  // adds an element in the sortedList (to the corresponding position)
  void add(T e);

  // removes an element from a given position
  // returns the removed element
  // throws an exception if the position is not valid
  T remove(int pos);

  // searches for an element and returns the first position where the element
  // appears or -1 if the element is not in the list
  int search(T e) const;

  // returns an iterator set to the first element of the list or invalid if the
  // list is empty
  ListIterator<T> iterator();

  // destructor
  ~SortedIndexedList();
}; // End of class declaration

// ============================================================================
// METHOD IMPLEMENTATIONS
// ============================================================================

// constructor. time complexity: o(cap)
// initializes array and links empty slots to form the free list
template <typename T> SortedIndexedList<T>::SortedIndexedList(Relation<T> r) {
  this->rel = r;
  this->cap = 10;
  this->nodes = new Node[cap];
  this->head = -1;
  this->tail = -1;
  this->firstEmpty = 0;
  this->length = 0;

  for (int i = 0; i < cap - 1; i++) {
    nodes[i].next = i + 1;
    nodes[i].prev = -1;
  }
  nodes[cap - 1].next = -1;
  nodes[cap - 1].prev = -1;
}

// doubles capacity and links new free slots. time complexity: o(n)
template <typename T> void SortedIndexedList<T>::resize() {
  int oldCap = cap;
  cap *= 2;
  Node *newNodes = new Node[cap];

  for (int i = 0; i < oldCap; i++) {
    newNodes[i] = nodes[i];
  }

  for (int i = oldCap; i < cap - 1; i++) {
    newNodes[i].next = i + 1;
    newNodes[i].prev = -1;
  }
  newNodes[cap - 1].next = -1;

  delete[] nodes;
  nodes = newNodes;
  firstEmpty = oldCap;
}

// returns size. time complexity: theta(1)
template <typename T> int SortedIndexedList<T>::size() const { return length; }

// checks if empty. time complexity: theta(1)
template <typename T> bool SortedIndexedList<T>::isEmpty() const {
  return length == 0;
}

// returns element at logical pos i. time complexity: o(n)
template <typename T> T SortedIndexedList<T>::getElement(int i) const {
  if (i < 0 || i >= length) {
    throw std::exception();
  }
  int current = head;
  for (int j = 0; j < i; j++) {
    current = nodes[current].next;
  }
  return nodes[current].info;
}

// removes element at pos i. time complexity: o(n)
// finds the node, unlinks it from neighbors, and returns it to the free list
template <typename T> T SortedIndexedList<T>::remove(int i) {
  if (i < 0 || i >= length)
    throw std::exception();

  int current = head;
  for (int count = 0; count < i; count++) {
    current = nodes[current].next;
  }

  T removedValue = nodes[current].info;

  if (current == head) {
    head = nodes[current].next;
    if (head != -1)
      nodes[head].prev = -1;
    else
      tail = -1;
  } else if (current == tail) {
    tail = nodes[current].prev;
    if (tail != -1)
      nodes[tail].next = -1;
    else
      head = -1;
  } else {
    int p = nodes[current].prev;
    int n = nodes[current].next;
    nodes[p].next = n;
    nodes[n].prev = p;
  }

  nodes[current].next = firstEmpty;
  firstEmpty = current;

  length--;
  return removedValue;
}

// returns first position of e or -1. time complexity: o(n)
template <typename T> int SortedIndexedList<T>::search(T e) const {
  int current = head;
  int pos = 0;
  int safety = 0;

  while (current != -1) {
    if (safety++ > length) {
      std::cout << "error: search failed" << std::endl;
    }
    if (nodes[current].info == e) {
      return pos;
    }
    current = nodes[current].next;
    pos++;
  }
  return -1;
}

// inserts e in sorted order. time complexity: o(n)
// gets a free slot, finds sorted position via relation, and rewires pointers
template <typename T> void SortedIndexedList<T>::add(T e) {
  if (firstEmpty == -1)
    resize();

  int newNode = firstEmpty;
  firstEmpty = nodes[firstEmpty].next;
  nodes[newNode].info = e;

  int safety = 0;
  int current = head;

  while (current != -1 && rel(nodes[current].info, e)) {
    if (safety++ > length) {
      std::cout << "error: add failed" << std::endl;
    }
    current = nodes[current].next;
  }

  if (length == 0) {
    head = tail = newNode;
    nodes[newNode].next = -1;
    nodes[newNode].prev = -1;
  } else if (current == head) {
    nodes[newNode].next = head;
    nodes[newNode].prev = -1;
    nodes[head].prev = newNode;
    head = newNode;
  } else if (current == -1) {
    nodes[newNode].next = -1;
    nodes[newNode].prev = tail;
    nodes[tail].next = newNode;
    tail = newNode;
  } else {
    int previousNode = nodes[current].prev;
    nodes[newNode].next = current;
    nodes[newNode].prev = previousNode;
    nodes[previousNode].next = newNode;
    nodes[current].prev = newNode;
  }
  length++;
}

// returns iterator. time complexity: theta(1)

// destructor. time complexity: theta(1)
template <typename T> SortedIndexedList<T>::~SortedIndexedList() {
  if (nodes != nullptr) {
    delete[] nodes;
  }
}
