#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "tiny_obj_loader.h"

extern "C" {
#include "llvm/Support/CommandLine.h"
}

using namespace llvm;

static cl::opt<std::string> InputFile(cl::Positional, cl::desc("<input .obj file>"), cl::Required);

extern "C" void LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  std::string warn;
  std::string err;

  std::string obj_text(reinterpret_cast<const char *>(Data), Size);
  bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, nullptr, nullptr, false, false);
  if (!ret) {
    fprintf(stderr, "Failed to load OBJ file: %s\n", err.c_str());
  }
}

int main(int argc, char **argv) {
  cl::ParseCommandLineOptions(argc, argv);

  FILE *fp = fopen(InputFile.c_str(), "rb");
  if (!fp) {
    fprintf(stderr, "Failed to open input file: %s\n", InputFile.c_str());
    return 1;
  }

  fseek(fp, 0, SEEK_END);
  long size = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  uint8_t *data = new uint8_t[size];
  fread(data, 1, size, fp);
  fclose(fp);

  LLVMFuzzerTestOneInput(data, size);

  delete[] data;

  return 0;
}