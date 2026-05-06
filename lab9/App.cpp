#include "ExtendedTest.h"
#include "ShortTest.h"
#include "SortedIndexedList.h"
#include <exception>
#include <iostream>
#include <string>

using namespace std;

bool ascInt(int a, int b) { return a <= b; }

bool descFloat(float a, float b) { return a >= b; }

bool ascString(std::string a, std::string b) { return a <= b; }

int main() {
  cout << "Running standard tests..." << endl;
  testAll();
  testAllExtended();
  cout << "Tests passed!\n" << endl;

  cout << "--- Laboratory 9 Requirement: 3 Data Types ---\n" << endl;

  SortedIndexedList<int> intList(ascInt);
  intList.add(10);
  intList.add(5);
  intList.add(20);
  cout << "Int List created successfully! Size: " << intList.size() << endl;

  SortedIndexedList<float> floatList(descFloat);
  floatList.add(3.14f);
  floatList.add(9.81f);
  cout << "Float List created successfully! Size: " << floatList.size() << endl;

  SortedIndexedList<std::string> stringList(ascString);
  stringList.add("Banana");
  stringList.add("Apple");
  cout << "String List created successfully! Size: " << stringList.size()
       << endl;

  cout << "\n--- Laboratory 9 Requirement: Exception Handling ---\n" << endl;

  try {
    cout << "Attempting to get an element at an invalid position (index 100)..."
         << endl;
    int invalidElement = intList.getElement(100);
    cout << "Element is: " << invalidElement << endl;
  } catch (const std::exception &e) {
    cout << "Exception caught! You tried to access an invalid position."
         << endl;
  }

  cout << "\nProgram finished executing normally." << endl;

  return 0;
}
