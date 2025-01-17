#include <clocale>
#include <iostream>
#include <string>
#include <vector>

#include "flatbuffers/flatc.h"
#include "flatbuffers/idl.h"
#include "flatbuffers/util.h"

using namespace flatbuffers;

// Define the schema for the FlatBuffer.
struct MySchema {
  static const char *name;
  static const char *file_extension;
  static const char *root_struct_name;
};

const char *MySchema::name = "MySchema";
const char *MySchema::file_extension = "fbs";
const char *MySchema::root_struct_name = "MyRoot";

// Generate the FlatBuffer schema.
int main(int argc, char **argv) {
  // Set the locale to ensure consistent output.
  setlocale(LC_ALL, "");

  // Generate the FlatBuffer schema.
  flatc::FlatCompiler compiler;
  compiler.Parse(argc, argv);
  if (!compiler.GenerateBinary()) {
    std::cerr << "Error generating binary schema." << std::endl;
    return 1;
  }

  // Serialize the FlatBuffer schema.
  flatbuffers::Parser parser;
  parser.Serialize(compiler.GetRootTable());

  return 0;
}