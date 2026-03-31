/**
 * @file main.cpp
 * @brief Implementation of a double-ended queue (deque) using a doubly linked
 * list.
 */

#include <iostream>
using namespace std;
class deque {

private:
  /**
   * @brief A struct representing a node in the doubly linked list used to
   * @param store the elements of the deque. Each node contains an integer data,
   * a pointer to the next node, and a pointer to the previous node.
   * @param The constructor initializes the data to 0 and the next and prev
   * pointers to nullptr.
   */
  struct node {
    int data;
    node *next;
    node *prev;

    node() : data(0), next(nullptr), prev(nullptr) {}
  };

  node *head;

  node *tail;

  int size;
  /**
   * @brief Constructs a new deque object.
   */
public:
  deque() : head(nullptr), tail(nullptr), size(0) {}
  /**
   * @brief Destroys the deque object and deallocates memory used by the nodes
   * in the linked list.
   */
  ~deque() {
    while (head != nullptr) {
      node *temp = head;
      head = head->next;
      delete temp;
    }
  }
  /**
   * @brief Copy constructor for the deque class. Creates a new deque object
   * that is a copy of an existing deque object.
   * @param other The deque object to be copied.
   */
  deque(const deque &other) : head(nullptr), tail(nullptr), size(0) {
    node *current = other.head;
    while (current != nullptr) {
      push_back(current->data);
      current = current->next;
    }
  }
  /**
   * @brief Assignment operator for the deque class. Assigns the contents of one
   * deque object to another deque object.
   * @param other The deque object to be assigned.
   * @return A reference to the assigned deque object.
   */
  deque &operator=(const deque &other) {
    if (this == &other) {
      return *this;
    }
    while (head != nullptr) {
      node *temp = head;
      head = head->next;
      delete temp;
    }
    head = tail = nullptr;
    size = 0;
    node *current = other.head;
    while (current != nullptr) {
      push_back(current->data);
      current = current->next;
    }
    return *this;
  }
  /**
   * @brief Pushes an integer value to the head of the deque.
   * @param value The integer value to be added to the head of the deque.
   */
  void push_front(int value) {
    node *new_node = new node();
    new_node->data = value;
    if (head == nullptr) {
      head = tail = new_node;
    } else {
      new_node->next = head;
      head->prev = new_node;
      head = new_node;
    }
    size++;
  }
  /**
   * @brief Pushes an integer value to the tail of the deque.
   * @param value The integer value to be added to the tail of the deque.
   */
  void push_back(int value) {
    node *new_node = new node();
    new_node->data = value;
    if (tail == nullptr) {
      head = tail = new_node;
    } else {
      new_node->prev = tail;
      tail->next = new_node;
      tail = new_node;
    }
    size++;
  }
  /**
   * @brief Removes the element at the head of the deque. If the deque is empty,
   * it prints a message indicating that the deque is empty and returns without
   * doing anything.
   */
  void pop_front() {
    if (head == nullptr) {
      cout << "Deque is empty!" << endl;
      return;
    }
    node *temp = head;
    head = head->next;
    if (head != nullptr) {
      head->prev = nullptr;
    } else {
      tail = nullptr;
    }
    delete temp;
    size--;
  }
  /**
   * @brief Removes the element at the tail of the deque. If the deque is empty,
   * it prints a message indicating that the deque is empty and returns without
   * doing anything.
   */

  void pop_back() {
    if (tail == nullptr) {
      cout << "Deque is empty!" << endl;
      return;
    }
    node *temp = tail;
    tail = tail->prev;
    if (tail != nullptr) {
      tail->next = nullptr;
    } else {
      head = nullptr;
    }
    delete temp;
    size--;
  }
  /**
   * @brief Prints the element at the head of the deque. If the deque is empty,
   * it prints a message indicating that the deque is empty and returns without
   * doing anything.
   */

  void top() {
    if (head == nullptr) {
      cout << "Deque is empty!" << endl;
      return;
    }
    cout << "Head: " << head->data << endl;
  }
  /**
   * @brief Prints the element at the tail of the deque. If the deque is empty,
   * it prints a message indicating that the deque is empty and returns without
   * doing anything.
   */

  void back() {
    if (tail == nullptr) {
      cout << "Deque is empty!" << endl;
      return;
    }
    cout << "Tail: " << tail->data << endl;
  }
  /**
   * @brief Overloads the output stream operator to print the elements of the
   * deque in order from head to tail. If the deque is empty, it will simply
   * print "Deque: " with no elements following it.
   * @param os The output stream to which the elements of the deque will be
   * written.
   * @param deque The deque object whose elements will be written to the output
   * stream.
   * @return An output stream containing the elements in the deque.
   */

  friend ostream &operator<<(ostream &os, const deque &deque) {
    node *current = deque.head;
    os << "Deque: ";
    while (current != nullptr) {
      os << current->data << " ";
      current = current->next;
    }
    return os;
  }
  /**
   * @brief Reads integer values from the input stream and adds them to the
   * deque. The user is prompted to enter values until they enter -1 to stop.
   * For each value entered, the user is also prompted to specify whether to add
   * the value to the front or back of the deque.
   * @param is The input stream from which to read the values.
   * @param deque The deque object to which the values will be added.
   * @return An input stream containing the values read from the user and added
   * to the deque.
   */

  friend istream &operator>>(istream &is, deque &deque) {
    int value;
    int pos;
    cout << "Enter values to add to the deque (enter -1 to stop): ";
    while (true) {
      is >> value;
      if (value == -1) {
        break;
      }
      cout << "Where to add the value (1. for front and 2. for back): ";
      is >> pos;
      if (pos == 1) {
        deque.push_front(value);
      } else if (pos == 2) {
        deque.push_back(value);
      } else {
        cout << "Invalid position! Please enter 1 or 2." << endl;
      }
      cout << "Enter next value (or -1 to stop): ";
    }
    return is;
  }
};
/**
 * @brief The main function contains a series of tests to validate the
 * functionality of the deque class. It tests various operations such as pushing
 * and popping elements from both ends of the deque, as well as the copy
 * constructor and assignment operator. The expected output is printed before
 * each test to help verify the correctness of the implementation.
 * @return 0 on successful completion of the tests.
 */
int main() {
  cout << "=== TEST 1: Empty Deque Operations ===" << endl;
  deque d1;
  cout << "Expected: Four 'Deque is empty!' warnings." << endl;
  d1.pop_front();
  d1.pop_back();
  d1.top();
  d1.back();
  cout << d1 << endl; // Expected: Deque:

  cout << "\n=== TEST 2: Push Operations ===" << endl;
  d1.push_front(10); // 10
  d1.push_back(20);  // 10 20
  d1.push_front(5);  // 5 10 20
  d1.push_back(25);  // 5 10 20 25
  cout << "Expected Output: Deque: 5 10 20 25" << endl;
  cout << "Actual Output: " << d1 << endl;

  cout << "Expected Head: 5 | ";
  d1.top();
  cout << "Expected Tail: 25 | ";
  d1.back();

  cout << "\n=== TEST 3: Pop Operations ===" << endl;
  d1.pop_front(); // Removes 5 -> leaves 10 20 25
  d1.pop_back();  // Removes 25 -> leaves 10 20
  cout << "Expected Output after pops: Deque: 10 20" << endl;
  cout << "Actual Output: " << d1 << endl;

  cout << "Popping remaining elements..." << endl;
  d1.pop_front();
  d1.pop_front();
  cout << "Expected: 'Deque is empty!' warning on next pop." << endl;
  d1.pop_front(); // Should trigger empty warning

  cout << "\n=== TEST 4: Copy Constructor ===" << endl;
  deque d2;
  d2.push_back(1);
  d2.push_back(2);
  d2.push_back(3);

  deque d3(d2); // This triggers the Copy Constructor
  cout << "Original d2: " << d2 << endl;
  cout << "Copied d3: " << d3 << endl;

  d2.pop_front(); // Modifying the original to ensure d3 doesn't change
  cout << "\nAfter popping front of d2:" << endl;
  cout << "d2 (Modified): " << d2 << endl; // Should be 2 3
  cout << "d3 (Intact): " << d3 << endl;   // Should still be 1 2 3

  cout << "\n=== TEST 5: Copy Assignment Operator ===" << endl;
  deque d4;
  d4.push_back(99);
  cout << "d4 before assignment: " << d4 << endl;
  d4 = d3; // This triggers the Copy Assignment Operator
  cout << "d4 after (d4 = d3): " << d4 << endl; // Should now be 1 2 3

  cout << "\n=== TEST 6: Self-Assignment ===" << endl;
  d4 = d4; // Testing that our 'this == &other' check prevents deletion
  cout << "d4 after (d4 = d4): " << d4 << endl; // Should still be 1 2 3

  cout << "\n=== TEST 7: Resizing and Memory Cleanup ===" << endl;
  deque d5;
  cout << "Pushing 5 elements, then popping 5 elements..." << endl;
  for (int i = 0; i < 5; i++) {
    d5.push_back(i);
  }
  for (int i = 0; i < 5; i++) {
    d5.pop_front();
  }
  cout << "Expected Output: Deque: " << endl;
  cout << "Actual Output: " << d5 << endl;

  cout << "\n=== TEST 8: Stream Input (Interactive) ===" << endl;
  deque d6;
  cin >> d6;
  cout << "You built: " << d6 << endl;

  cout << "\nAll automated tests completed!" << endl;
  return 0;
}
