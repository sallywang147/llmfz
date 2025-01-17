#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include "tiny_obj_loader.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string matId = stream.ConsumeRandomLengthString();
  std::vector<tinyobj::material_t> materials;
  std::map<std::string, int> matMap;
  std::string warn;
  std::string err;

  tinyobj::MaterialFileReader reader(matId);
  bool ret = reader(&matId, &materials, &matMap, &warn, &err);

  return 0;
}