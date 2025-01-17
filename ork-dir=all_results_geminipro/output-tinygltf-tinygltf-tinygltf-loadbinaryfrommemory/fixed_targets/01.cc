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

  tinygltf::TinyGLTF ctx;
  tinygltf::Model model;
  std::string err;
  std::string warn;

  const char *str = reinterpret_cast<const char *>(data);

  bool ret = ctx.LoadBinaryFromMemory(&ctx, &model, &err, &warn, str, size,
                                     /* base_dir */ "", /* check_redundant_materials */ 0);
  (void)ret;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  parse_intCoding4(data, size);
  return 0;
}
```

The issue is that the `parse_intCoding4` function is not declared as `extern "C"`. This is necessary because the function is called from C code, and the C compiler does not know about C++ function names by default.

To fix the issue, add `extern "C"` before the `parse_intCoding4` function declaration:

```c++
extern "C" static void parse_intCoding4(const uint8_t *data, size_t size) {
```

This will tell the C compiler that the function is a C function, and it will be able to find it when it is called from C code.