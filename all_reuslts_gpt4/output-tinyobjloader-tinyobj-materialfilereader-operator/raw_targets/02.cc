#include <fuzzer/FuzzedDataProvider.h>
#include <tiny_obj_loader.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>
#include <map>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string matId = stream.ConsumeRandomLengthString();
  std::vector<tinyobj::material_t> materials;
  std::map<std::string, int> matMap;
  std::string warn;
  std::string err;

  tinyobj::MaterialFileReader materialFileReader(matId);

  materialFileReader(&matId, &materials, &matMap, &warn, &err);

  return 0;
}