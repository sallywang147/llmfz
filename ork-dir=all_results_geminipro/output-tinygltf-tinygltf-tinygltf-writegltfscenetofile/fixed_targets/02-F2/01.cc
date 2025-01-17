#include <cstdint>
#include <cstring>
#include <iostream>
#include <memory>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_IMPLEMENTATION
#include "tiny_gltf.h"

extern "C" {
#include "stb_image.h"
#include "stb_image_write.h"
}

static void parse_intCoding4(const uint8_t *data, size_t size) {

  tinygltf::Model model;
  tinygltf::TinyGLTF ctx;
  std::string err;
  std::string warn;

  bool ret = ctx.LoadASCIIFromString(&model, &err, &warn, reinterpret_cast<const char *>(data), size, /* base_dir */ "");
  (void)ret;

  std::string output_path = "output.gltf";

  ctx.WriteGltfSceneToFile(&model, &output_path, false, false, false, false);
}

extern "C" int LLVMFuzzerTestOneInput(std::uint8_t const *data, std::size_t size) {
  parse_intCoding4(data, size);
  return 0;
}
```
The issue was that the `reinterpret_cast` was missing in `LoadASCIIFromString`.
The corrected line is:
```c++
bool ret = ctx.LoadASCIIFromString(&model, &err, &warn, reinterpret_cast<const char *>(data), size, /* base_dir */ "");