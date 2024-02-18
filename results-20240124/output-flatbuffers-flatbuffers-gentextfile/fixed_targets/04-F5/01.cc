#include <iostream>
#include <fstream>

extern "C" {
#include "GenTextFile.h"
}

using namespace std;

int main() {
  // Create a GenTextFile object
  GenTextFile file("test.txt");

  // Write some text to the file
  file.write("Hello, world!");

  // Close the file
  file.close();

  return 0;
}