#include "ExtendedTest.h" // Make sure you have this if you want to run professor's tests
#include "ShortTest.h" // Make sure you have this if you want to run professor's tests
#include "SortedIndexedList.h"
#include <iostream>
#include <string>

using namespace std;

// 1. Relation function for Integers (Ascending)
bool ascInt(int a, int b) { return a <= b; }

// 2. Relation function for Floats (Descending)
bool descFloat(float a, float b) { return a >= b; }

// 3. Relation function for Strings (Alphabetical)
bool ascString(std::string a, std::string b) { return a <= b; }

int main() {
  // Optional: Run your professor's tests first
  cout << "Running standard tests..." << endl;
  testAll();
  testAllExtended();
  cout << "Tests passed!\n" << endl;

  cout << "--- Laboratory 9 Requirement: 3 Data Types ---\n" << endl;

  // --- Object 1: Integer List ---
  SortedIndexedList<int> intList(ascInt);
  intList.add(10);
  intList.add(5);
  intList.add(20);
  cout << "Int List created successfully! Size: " << intList.size() << endl;

  // --- Object 2: Float List ---
  SortedIndexedList<float> floatList(descFloat);
  floatList.add(3.14f);
  floatList.add(9.81f);
  floatList.add(1.61f);
  cout << "Float List created successfully! Size: " << floatList.size() << endl;

  // --- Object 3: String List ---
  SortedIndexedList<std::string> stringList(ascString);
  stringList.add("Banana");
  stringList.add("Apple");
  stringList.add("Cherry");
  cout << "String List created successfully! Size: " << stringList.size()
       << endl;

  cout << "\nAll data types compiled and ran successfully!" << endl;

  return 0;
}
